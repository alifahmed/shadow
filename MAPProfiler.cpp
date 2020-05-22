/*******************************************************************************
 *
 * File: MAPProfiler.cpp
 * Description: Pin tool for tracing memory accesses.
 * 
 * Author:  Alif Ahmed
 * Email:   alifahmed@virginia.edu
 * Updated: Aug 06, 2019
 *
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <string>
#include <cmath>
#include <iosfwd>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>
#include <cassert>
#include <sstream>
#include <immintrin.h>
#include "pin.H"

using namespace std;

/*******************************************************************************
 * Knobs for configuring the instrumentation
 ******************************************************************************/
// Name of the function to profile
KNOB<string> knobFunctionName(KNOB_MODE_WRITEONCE, "pintool", "func", "main",
    "Function to be profiled.");

// Output file name
KNOB<string> knobOutFile(KNOB_MODE_WRITEONCE, "pintool", "out", "mem_trace.csv",
    "Output file name.");

// Max threads
KNOB<UINT64> knobMaxThreads(KNOB_MODE_WRITEONCE, "pintool", "threads", "10000",
    "Upper limit of the number of threads that can be used by the program \
        being profiled.");

// Read logging (1: enable, 0: disable)
KNOB<bool> knobRead(KNOB_MODE_WRITEONCE, "pintool", "read", "1",
    "Read logging \
        [1: enable (default), 0: disable].");

// Write logging (1: enable, 0: disable)
KNOB<bool> knobWrite(KNOB_MODE_WRITEONCE, "pintool", "write", "1",
    "Write \
        logging [1: enable (default), 0: disable].");


/*******************************************************************************
 * Forward declarations
 ******************************************************************************/
typedef enum {InsTypeInvalid, InsTypeNormal, InsTypeLoop} InsType;
typedef enum {AccessTypeInvalid, AccessTypeRead, AccessTypeWrite} AccessType;
typedef enum {PatTypeInvalid, PatTypeSeq, PatTypeRand} PatType;
struct InsBase;
struct InsNormal;
struct InsAbnormal;
struct InsLoop;
struct InsBlock;
struct Interval;

void deriveAccessPattern(const vector<InsNormal*> &insList);
InsNormal* createInsNormal(AccessType type, UINT32 accSz, string dis);

/*******************************************************************************
 * Data structures
 ******************************************************************************/
typedef map<ADDRINT, InsNormal*> InfoMap;

typedef struct Interval {
  ADDRINT s = -1;
  ADDRINT e = 0;
} Interval;

typedef struct InsAbnormal{
  string dis;
  UINT64 accSz;
  AccessType accType = AccessTypeInvalid;
  map<ADDRINT, InsNormal*> insMap;
} InsAbnormal;

typedef struct InsNormal{
  UINT64 id = -1;
  string dis;
  AccessType accType = AccessTypeInvalid;
  UINT64 accSz;
  UINT64 totalSz = 0;
  UINT64 cnt = 0;
  ADDRINT lastEA = -1;
  map<INT64, UINT64>  strideDist;
  Interval addr;
  bool isTop = false;
  InsBlock* block = NULL;
  PatType pType = PatTypeInvalid;
  INT64 stride = -1;
  string strStart;
  string strEnd;
  string strCurr;
  string strType;
} InstInfo;

typedef struct InsLoop {
  UINT64 id = -1;
  UINT64 loopCnt = 0;
  vector<InsBase*> ins;
}InsLoop;

typedef struct InsBlock{
  UINT64 id = -1;
  map<InsBlock*, UINT64> outEdges;   //successors and count
  set<InsBlock*> inEdges;
  vector<InsBase*> ins;
} InsBlock;

typedef struct InsBase{
  InsType type = InsTypeInvalid;
  InsNormal* insNormal = NULL;
  InsLoop* insLoop = NULL;
}InsBase;


/*******************************************************************************
 * Defines
 ******************************************************************************/
#define ACCESS_KEEP_PERC    95
#define MAX_STRIDE_BUCKETS  10
#define MIN_CNT             500
#define HASH_INIT_VALUE     (0xABCDEF94ED70BA3EULL)
#define _tab(x)             setw(x*4) << " "


/*******************************************************************************
 * Global variables
 ******************************************************************************/
static string rtn_name;
static PIN_LOCK lock;
static bool read_log_en = true;
static bool write_log_en = true;
static UINT64 rtnEntryCnt = 0;
bool firstLine = true;

static vector<InsNormal*> insNormalList;
static vector<InsAbnormal*> insAbnormalList;
static vector<InsBlock*> blockList;
static vector<InsBase*> baseList;
static vector<InsLoop*> loopList;

static vector<InsNormal*> insTrace;
static stack<ADDRINT> callStack;
static ADDRINT callHash = HASH_INIT_VALUE;

static ADDRINT globalMinAddr = -1;
static ADDRINT globalMaxAddr = 0;

static map<UINT64, string> accTypeMap;
static map<UINT64, char> movSuffixMap;
static map<UINT64, string> regNameMap;


/*******************************************************************************
 * Functions
 ******************************************************************************/

bool compressDCFG(set<InsBlock*> &cfg){
  bool isChanged = false;
  bool merged;
  do{
    merged = false;
    for(InsBlock* in : cfg){
      if(in->id == 0) continue;   //skip begin block
      if(in->outEdges.size() == 1){
        InsBlock* out = in->outEdges.begin()->first;
        if(out->id == 1) continue;
        if(out->inEdges.size() == 1){
          //merge in with out
          //assert(out->inEdges.begin()->first == in);

          //replace out edges
          in->outEdges = out->outEdges;

          //copy instructions
          in->ins.insert(in->ins.end(), out->ins.begin(), out->ins.end());

          //mark to be deleted
          merged = true;
          isChanged = true;
          cfg.erase(out);
          break;
        }
      }
    }
  } while(merged);
  return isChanged;
}

bool compressLoop(set<InsBlock*> &cfg){
  bool isChanged = false;
  bool merged;
  do{
    merged = false;
    for(InsBlock* in : cfg){
      //check conditions for inferring as a loop
      map<InsBlock*, UINT64>::iterator ed = in->outEdges.find(in);
      if(ed != in->outEdges.end()){
        //most probably found a loop

        //get loop count
        UINT64 m = ed->second;
        UINT64 total = 0;
        for(auto e : in->outEdges){
          total += e.second;
        }
        UINT64 k = total - m;
        if(total % k) continue;   //skip if not divisible
        UINT64 loopCnt = total / k;
        //remove outgoing loop edge
        in->outEdges.erase(ed);
        //remove incoming loop edge (just removing any edge is fine for now, since we are not using exact edges, just counts)
        in->inEdges.erase(in->inEdges.begin());

        InsLoop* loop = new InsLoop();
        loopList.push_back(loop);
        InsBase* base = new InsBase();
        baseList.push_back(base);

        static UINT64 loopId = 0;
        loop->loopCnt = loopCnt;
        loop->ins = in->ins;    //copy
        loop->id = loopId++;
        in->ins.clear();

        base->type = InsType::InsTypeLoop;
        base->insLoop = loop;
        in->ins.push_back(base);

        //mark
        merged = true;
        isChanged = true;
        break;
      }
    }
  } while(merged);
  return isChanged;
}

void mergeAllLoops(set<InsBlock*> &cfg){
  bool isChanged;
  do{
    compressDCFG(cfg);
    isChanged = compressLoop(cfg);
  } while(isChanged);
}

void printInsLabel(ofstream &out, const vector<InsBase*> &insts, UINT32 indent){
  for(InsBase* it : insts){
    if(!firstLine){
      out << "<br />";
    }
    firstLine = false;
    for(UINT32 i = 0; i < indent; i++){
      out << "  ";
    }
    if(it->type == InsType::InsTypeNormal){
      InsNormal* ins = it->insNormal;
      out << setw(4) << ins->id << ":";
      if(ins->accType == AccessType::AccessTypeRead){
        out << "RD ";
      }
      else if(ins->accType == AccessType::AccessTypeWrite){
        out << "WR ";
      }
      if(ins->pType == PatType::PatTypeSeq){
        out << "SEQ S" << ins->stride;
      }
      else if(ins->pType == PatType::PatTypeRand){
        out << "RAND ";
      }
      out << " A" << ins->accSz << " [" << ins->addr.s << ":" << ins->addr.e << ")";
    }
    else if(it->type == InsType::InsTypeLoop){
      InsLoop* loop = it->insLoop;
      out << "loop" << loop->id << ": " << loop->loopCnt;
      printInsLabel(out, loop->ins, indent+1);
    }
  }
}

void printDot(const set<InsBlock*> &cfg, const char* fname){
  ofstream out(fname);
  cout << "Printing " << fname << "...\n";

  out << "digraph DCFG {\n";

  out << "\tB0 [label=\"START\",fillcolor=yellow,style=filled];\n";
  out << "\tB1 [label=\"END\",fillcolor=yellow,style=filled];\n";

  for(InsBlock* ib : cfg){
    if(ib->id >= 2){
      out << "\tB" << ib->id << " [shape=plain, fontname=\"Courier\", label=< <table>";
      out << "<TR><TD balign=\"left\" border=\"0\">";
      firstLine = true;
      printInsLabel(out, ib->ins, 0);
      out << "</TD></TR> </table> >];\n";
    }
    for(auto it : ib->outEdges){
      InsBlock* o = it.first;
      out << "\tB" << ib->id;// << ":o" << cnt;
      out << " -> B" << o->id;// << ":i";
      out << " [label=\"" << it.second << "\"];\n";
    }
  }

  out << "}\n";
}

void generateCodeInst(ofstream &out, InsNormal* ins, int indent){
  if(ins->pType == PatType::PatTypeSeq){
    out << _tab(indent) << "__asm__ __volatile__ (\"leaq (%1,%2,1), %0\\n\\t\" : \"=r\"(addr) : \"r\"(gm), \"r\"(" << ins->strCurr << ") : );\n";
    if(ins->accType == AccessType::AccessTypeRead){
      out << _tab(indent) << "__asm__ __volatile__ (\"mov" << movSuffixMap[ins->accSz] << " (%0), %%" << regNameMap[ins->accSz]
          << "\" : : \"r\"(addr) : \"" << regNameMap[ins->accSz] << "\" );\n";
    }
    else if(ins->accType == AccessType::AccessTypeWrite){
      out << _tab(indent) << "__asm__ __volatile__ (\"mov" << movSuffixMap[ins->accSz] << " %%" << regNameMap[ins->accSz] << ", (%0)"
          << "\" : \"=r\"(addr) : : );\n";
    }
    out << _tab(indent) << ins->strCurr << " += " << ins->stride << ";\n";
    out << _tab(indent) << "if(" << ins->strCurr << " >= " << ins->addr.e << ") " << ins->strCurr << " = " << ins->addr.s << ";\n";
  }
  else if(ins->pType == PatType::PatTypeRand){
    //first, generate random address within range, and without accessing memory
    out << _tab(indent) << "hash = _mm_crc32_u64(hash, " << (((uint64_t)rand() << 32) | rand()) << "ULL);\n";
    out << _tab(indent) << "offset = (hash % " << ins->addr.e - ins->addr.s << ") + " << ins->addr.s << ";\n";
    out << _tab(indent) << "addr = gm + (offset & ~7ULL);\n";

    if(ins->accType == AccessType::AccessTypeRead){
      out << _tab(indent) << "__asm__ __volatile__ (\"mov" << movSuffixMap[ins->accSz] << " (%0), %%" << regNameMap[ins->accSz]
                << "\" : : \"r\"(addr) : \"" << regNameMap[ins->accSz] << "\" );\n";
    }
    else if(ins->accType == AccessType::AccessTypeWrite){
      out << _tab(indent) << "__asm__ __volatile__ (\"mov" << movSuffixMap[ins->accSz] << " %%" << regNameMap[ins->accSz] << ", (%0)"
                << "\" : \"=r\"(addr) : : );\n";
    }
  }
  out << "\n";
}

void generateCodeLoop(ofstream &out, InsLoop* loop, int indent){
  out << _tab(indent) << "for(uint64_t loop" << loop->id << " = 0; loop" << loop->id << " < " << loop->loopCnt << "ULL; loop" << loop->id << "++){\n";
  for(InsBase* base : loop->ins){
    if(base->type == InsType::InsTypeLoop){
      generateCodeLoop(out, base->insLoop, indent + 1);
    }
    else if(base->type == InsType::InsTypeNormal){
      generateCodeInst(out, base->insNormal, indent + 1);
    }
  }
  out << _tab(indent) << "}\n";
}

void generateCodeHeader(ofstream &out, vector<InsNormal*> &insList){
  out << "#include <cstdlib>\n";
  out << "#include <cstdint>\n";
  out << "#include <cstdio>\n";
  out << "#include \"immintrin.h\"\n";
  out << "\n";
  out << "int main(){\n";
  out << _tab(1) << "volatile uint8_t* addr = NULL;\n";
  out << _tab(1) << "uint64_t offset;\n";
  out << _tab(1) << "uint64_t hash = 0xC32ED012FEA8B4D3ULL;\n";
  out << _tab(1) << "uint64_t allocSize = " << globalMaxAddr - globalMinAddr << "ULL;\n";
  out << _tab(1) << "volatile uint8_t* gm = (volatile uint8_t*)malloc(allocSize);\n";
  out << _tab(1) << "if(gm == NULL) {\n";
  out << _tab(2) << "fprintf(stderr, \"Cannot allocate memory\\n\");\n";
  out << _tab(2) << "exit(-1);\n";
  out << _tab(1) << "}\n";
  out << "\n";
  for(InsNormal* ins : insList){
    stringstream ss;
    ins->strType = accTypeMap[ins->accSz];
    ss << "ins_" << ins->id;
    ins->strCurr = ss.str();
    ss.str("");
    ss << "ins_" << ins->id << "_start";
    ins->strStart = ss.str();
    ss.str("");
    ss << "ins_" << ins->id << "_end";
    ins->strEnd = ss.str();
    ss.str("");
    if(ins->pType == PatTypeSeq){
      out << _tab(1) << "uint64_t " << ins->strCurr << " = " << ins->addr.s << ";\n";
    }
  }
  out << "\n";
}

void generateCodeBlock(ofstream &out, InsBlock* blk, int indent){
  for(InsBase* base : blk->ins){
    if(base->type == InsType::InsTypeLoop){
      generateCodeLoop(out, base->insLoop, indent);
    }
    else if(base->type == InsType::InsTypeNormal){
      generateCodeInst(out, base->insNormal, indent);
    }
    else{
      cerr << "Unable to generate code: Invalid instruction type" << endl;
      PIN_ExitProcess(11);
    }
  }
}

void generateCodeFooter(ofstream &out){
  out << _tab(1) << "return 0;\n";
  out << "}\n";
}

void generateCode(vector<InsNormal*> &insList, const set<InsBlock*> &cfg, const char* fname){
  //find root node
  InsBlock* root = NULL;
  for(InsBlock* ins : cfg){
    if(ins->id == 0){
      root = ins;
      break;
    }
  }
  assert(root->outEdges.size() == 1);
  root = root->outEdges.begin()->first;
  assert(root != NULL);

  cout << "Generating code in: " << fname << "...\n";

  //open output file
  ofstream out(fname);

  //write headers
  generateCodeHeader(out, insList);

  //write code blocks: For now, only one block
  generateCodeBlock(out, root, 1);

  //write footer
  generateCodeFooter(out);

}

set<InsBlock*> cfgFromTrace(vector<InsNormal*> &trace){
  static UINT64 blockId = 2;
  set<InsBlock*> topInsBlocks;

  InsBlock* prev = new InsBlock();    //begin block
  prev->id = 0;
  topInsBlocks.insert(prev);

  UINT64 ttCnt = 0;
  for(InsNormal* ins : trace){
    if(ins->isTop){
      InsBlock* ib = ins->block;
      if(ib == NULL){
        //create new block
        ib = new InsBlock();
        ins->block = ib;
        blockList.push_back(ib);
        ib->id = blockId++;

        InsBase* base = new InsBase();
        baseList.push_back(base);
        base->type = InsType::InsTypeNormal;
        base->insNormal = ins;

        ib->ins.push_back(base);
        topInsBlocks.insert(ib);
      }
      ttCnt++;
      //add ib as the successor of prev
      ib->inEdges.insert(prev);
      prev->outEdges[ib]++;
      prev = ib;
    }
  }

  //add end block
  InsBlock* ib = new InsBlock();
  ib->id = 1;
  topInsBlocks.insert(ib);
  ib->inEdges.insert(prev);
  prev->outEdges[ib]++;

  cout << "Top trace size: " << ttCnt << endl;
  return topInsBlocks;
}

set<InsBlock*> createDCFGfromInstTrace(vector<InsNormal*> &trace){
  set<InsBlock*> topInsBlocks = cfgFromTrace(trace);
  printDot(topInsBlocks, "dcfgBC.gv");

  compressDCFG(topInsBlocks);
  printDot(topInsBlocks, "dcfgAC.gv");

  mergeAllLoops(topInsBlocks);
  printDot(topInsBlocks, "dcfgLC.gv");

  return topInsBlocks;
}

void printInfo(const vector<InsNormal*> &res){
  for(InsNormal* i : res){
    cout << "  " << setw(10) << dec << i->id << ": ";
    if(i->accType == AccessType::AccessTypeRead){
      cout << "READ  : ";
    } else if(i->accType == AccessType::AccessTypeWrite){
      cout << "WRITE : ";
    } else{
      cout << "INVALID: ";
    }
    cout << setw(40) << i->dis;


    cout << setw(20) << "TotalSz: " << i->totalSz;
    cout << setw(20) << "Count: " << i->cnt;
    cout << setw(20) << "Pattern: ";
    if(i->pType == PatType::PatTypeSeq){
      cout << "Seq : " << i->stride << "\t";
    }
    else if(i->pType == PatType::PatTypeRand){
      cout << "Rand\t";
    }
    else{
      cout << "Invalid\t";
    }
    cout << setw(10) << "[" << setw(10) << i->addr.s << " : " << setw(10) << i->addr.e << "]\t";
    cout << setw(10);
    for(auto s : i->strideDist){
      cout << "{" << s.first << ":" << s.second << "} ";
    }

    cout << dec << endl;
  }
}


UINT64 getTotalAccessSz(const vector<InsNormal*> &insList){
  UINT64 sz = 0;
  for(InsNormal* it : insList){
    sz += it->totalSz;
  }
  return sz;
}


vector<InsNormal*> keepTop(vector<InsNormal*> &insList, double perc){
  UINT64 sz = getTotalAccessSz(insList);
  cout << "Before pruning. NumInst: " << insList.size() << "\t\tAccessSz: " << sz << endl;
  UINT64 szAfter = sz * perc / 100.0;

  //sort using total accessed size
  sort(insList.begin(), insList.end(), [](const InsNormal* lhs, const InsNormal* rhs) {
      return lhs->totalSz > rhs->totalSz;
  });

  vector<InsNormal*> out;
  sz = 0;
  for(InsNormal* it : insList){
    out.push_back(it);
    sz += it->totalSz;
    if(sz > szAfter)  break;
  }

  sz = 0;
  for(InsNormal* it: out){
    sz += it->totalSz;
  }
  cout << "After pruning. NumInst: " << out.size() << "\t\tAccessSz: " << sz << endl;
  return out;
}


vector<InsNormal*> deleteConstAccess(const vector<InsNormal*> &insList){
  vector<InsNormal*> out;
  out.reserve(insList.size());
  for(InsNormal* it : insList){
    if((it->pType == PatType::PatTypeSeq) && (it->stride == 0)){
      continue;
    }
    out.push_back(it);
  }
  return out;
}


vector<InsNormal*> deleteZeroAccesses(const vector<InsNormal*> &insList){
  vector<InsNormal*> out;
  out.reserve(insList.size());
  for(InsNormal* it : insList){
    if(it->cnt > MIN_CNT){
      out.push_back(it);
    }
  }
  return out;
}

void deriveAccessPattern(const vector<InsNormal*> &insList){
  for(InsNormal* it : insList){
    if(it->strideDist.size() >= MAX_STRIDE_BUCKETS){
      it->pType = PatType::PatTypeRand;
    }
    else {
      double totCnt = 0;
      double maxCnt = 0;
      INT64 maxStride = 0;
      for(auto s : it->strideDist){
        totCnt += s.second;
        if(s.second > maxCnt){
          maxCnt = s.second;
          maxStride = s.first;
        }
      }
      if(maxCnt / totCnt > 0.9){
        //sequential
        it->pType = PatType::PatTypeSeq;
        it->stride = maxStride;
      }
    }
  }
}

void markTopAndProcessInfo(vector<InsNormal*> &insList){
  for(InsNormal* it : insList){
    it->isTop = true;         //mark as top instruction
    it->addr.e += it->accSz;  //fix end address
  }

  //sort using min address
  sort(insList.begin(), insList.end(), [](const InsNormal* lhs, const InsNormal* rhs) {
      if(lhs->addr.s == rhs->addr.s){
        return lhs->addr.e < rhs->addr.e;
      }
      return lhs->addr.s < rhs->addr.s;
  });

  //update address space to remove gaps
  ADDRINT gmax = 0;
  ADDRINT gap = 0;
  for(InsNormal* it : insList){
    if(it->addr.s > gmax){
      //found a gap in address space
      gap += it->addr.s - gmax;
    }
    if(it->addr.e > gmax){
      //update max address if needed
      gmax = it->addr.e;
    }
    it->addr.s -= gap;
    it->addr.e -= gap;

    //update global min and max addresses
    if(it->addr.s < globalMinAddr){
      globalMinAddr = it->addr.s;
    }
    if(it->addr.e > globalMaxAddr){
      globalMaxAddr = it->addr.e;
    }
  }
  cout << "Global min address: " << globalMinAddr << endl;
  cout << "Global max address: " << globalMaxAddr << endl;
}

VOID Fini(INT32 code, VOID *v) {
  // 0. Filter zero  (or very low) cnt instructions
  vector<InsNormal*> filteredInsList;
  filteredInsList = deleteZeroAccesses(insNormalList);

  deriveAccessPattern(filteredInsList);   //needed for next step
  // 1. filter constant access instructions
  filteredInsList = deleteConstAccess(filteredInsList);

  // 2. Only take instructions that represents ACCESS_KEEP_PERC of reads/writes
  filteredInsList = keepTop(filteredInsList, ACCESS_KEEP_PERC);
  markTopAndProcessInfo(filteredInsList);

  printInfo(filteredInsList);

  cout << "Inst Trace size: " << insTrace.size() << endl;
  set<InsBlock*> cfg = createDCFGfromInstTrace(insTrace);

  generateCode(filteredInsList, cfg, "genCode.cpp");

  cout << "Call stack size: " << callStack.size() << endl;
  //assert(callHash == HASH_INIT_VALUE);
  for(InsNormal* it : insNormalList){ delete it; }    //delete allocated instructions
  for(InsAbnormal* it : insAbnormalList){ delete it; }    //delete allocated instructions
  for(InsBlock* it : blockList){ delete it; }         //delete allocated blocks
  for(InsBase* it : baseList){ delete it; }           //delete allocated base instructions
  for(InsLoop* it : loopList){ delete it; }           //delete allocated loops
}


/*******************************************************************************
 * IMG Instrumentation
 ******************************************************************************/
VOID RtnEntry(THREADID tid) {
  //tdata[tid].rtnEntryCnt++;
  rtnEntryCnt++;
}

VOID RtnLeave(THREADID tid) {
  //tdata[tid].rtnEntryCnt--;
  rtnEntryCnt--;
}

void ImgCallback(IMG img, VOID *arg) {
  if (!IMG_IsMainExecutable(img))
    return;

  int match_count = 0;
  cout << "Tagging functions with \"" << rtn_name << "\"..." << endl;

  //First try for exact match of function
  for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)) {
    if (SEC_Name(sec) == ".text") {
      for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn)) {
        string name = PIN_UndecorateSymbolName(RTN_Name(rtn),
            UNDECORATION_NAME_ONLY);
        // add suffix for openmp functions
        string rtn_name_omp = rtn_name + "._omp_fn.";

        // Try exact name match
        if ((name == rtn_name) || (name.find(rtn_name_omp) != string::npos)) {
          // Match found!
          match_count++;
          cout << "    Tagged function \"" << name << "\"" << endl;

          // Instrument function entry and exit
          RTN_Open(rtn);
          RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) RtnEntry, IARG_THREAD_ID, IARG_END);
          RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) RtnLeave, IARG_THREAD_ID, IARG_END);
          RTN_Close(rtn);
        }
      }
    }
  }
  if (match_count)
    return;

  //Exact match not found. Try to find a function containing the given function name.
  cout << "Exact match not found! Tagging all functions containing \""
      << rtn_name << "\"..." << endl;
  for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)) {
    if (SEC_Name(sec) == ".text") {
      for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn)) {
        string name = PIN_UndecorateSymbolName(RTN_Name(rtn),
            UNDECORATION_NAME_ONLY);

        // Check if the current routine contains the requested routine name
        if (name.find(rtn_name) != string::npos) {
          // Match found!
          match_count++;
          cout << "    Tagged function \"" << name << "\"" << endl;

          // Instrument function entry and exit
          RTN_Open(rtn);
          RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) RtnEntry, IARG_THREAD_ID, IARG_END);
          RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) RtnLeave, IARG_THREAD_ID, IARG_END);
          RTN_Close(rtn);
        }
      }
    }
  }

  //Not found
  if (!match_count) {
    cout << "Unable to find any function containing \"" << rtn_name
        << "\"... Quitting..." << endl;
    PIN_ExitProcess(11);
  }
}


/*******************************************************************************
 * INS Instrumentation
 ******************************************************************************/
VOID anyCallEntry(ADDRINT ptr){
  callStack.push(ptr);
  callHash ^= ptr;
}

VOID anyCallRet(){
  ADDRINT lastAddr = callStack.top();
  callHash ^= lastAddr;
  callStack.pop();
}

void record(InsAbnormal* ins, ADDRINT ea) {
  if(rtnEntryCnt <= 0)  return;
  InsNormal* info = NULL;
  if(ins->insMap.find(callHash) == ins->insMap.end()){
    //Instruction info data not present in the current context. Create new.
    info = createInsNormal(ins->accType, ins->accSz, ins->dis);
    ins->insMap[callHash] = info;
  }
  info = ins->insMap[callHash];
  info->totalSz += info->accSz;
  if(info->cnt && (info->strideDist.size() < MAX_STRIDE_BUCKETS)){
    INT64 stride = ea - info->lastEA;
    info->strideDist[stride]++;
  }
  if(ea < info->addr.s){
    info->addr.s = ea;
  }
  if(ea > info->addr.e){
    info->addr.e = ea;
  }
  info->lastEA = ea;
  info->cnt++;
  insTrace.push_back(info);
}


InsNormal* createInsNormal(AccessType type, UINT32 accSz, string dis){
  static UINT64 id = 0;
  InsNormal* info = new InsNormal();
  info->dis = dis;
  info->id = id++;
  info->accType = type;
  info->accSz = accSz;
  insNormalList.push_back(info);
  return info;
}

InsAbnormal* createInsAbnormal(AccessType type, UINT32 accSz, string dis){
  InsAbnormal* info = new InsAbnormal();
  info->dis = dis;
  info->accType = type;
  info->accSz = accSz;
  insAbnormalList.push_back(info);
  return info;
}

void Instruction(INS ins, VOID *v) {
  static set<ADDRINT> processedIns;   //set of already processed instructions

  // do some filtering
  if (INS_IsLea(ins)) return;
  // Add other instructions if needed

  if(INS_IsCall(ins)){
    INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) anyCallEntry, IARG_INST_PTR, IARG_END);
    return;
  }

  if(INS_IsRet(ins)){
    INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) anyCallRet, IARG_END);
    return;
  }

  // Get the memory operand count of the current instruction.
  UINT32 memOperands = INS_MemoryOperandCount(ins);

  // check if memory instruction
  if (memOperands == 0) return;

  // check if already processed or not
  ADDRINT addr = INS_Address(ins);
  if (processedIns.find(addr) != processedIns.end()) {
    return;   //already processed
  }
  processedIns.insert(addr); //mark as processed

  // Iterate over each memory operand of the instruction.
  for (UINT32 memOp = 0; memOp < memOperands; memOp++) {
    if (INS_MemoryOperandIsRead(ins, memOp) && read_log_en) {
      InsAbnormal* info = createInsAbnormal(AccessType::AccessTypeRead, INS_MemoryOperandSize(ins, memOp), INS_Disassemble(ins));
      INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record, IARG_PTR, info, IARG_MEMORYOP_EA, memOp, IARG_END);
    }

    if (INS_MemoryOperandIsWritten(ins, memOp) && write_log_en) {
      InsAbnormal* info = createInsAbnormal(AccessType::AccessTypeWrite, INS_MemoryOperandSize(ins, memOp), INS_Disassemble(ins));
      INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record, IARG_PTR, info, IARG_MEMORYOP_EA, memOp, IARG_END);
    }
  }
}


/*******************************************************************************
 * PIN Entry
 ******************************************************************************/
int main(int argc, char *argv[]) {
  if (PIN_Init(argc, argv)) {
    return -1;
  }

  // Initializations
  PIN_InitLock(&lock);
  PIN_InitSymbolsAlt(IFUNC_SYMBOLS);

  rtn_name = knobFunctionName.Value();
  read_log_en = knobRead.Value();
  write_log_en = knobWrite.Value();

  insNormalList.reserve(100000);
  baseList.reserve(100000);
  loopList.reserve(100000);
  insTrace.reserve(40000000);

  accTypeMap[1] = "uint8_t";
  accTypeMap[2] = "uint16_t";
  accTypeMap[4] = "uint32_t";
  accTypeMap[8] = "uint64_t";

  movSuffixMap[1] = 'b';
  movSuffixMap[2] = 'w';
  movSuffixMap[4] = 'l';
  movSuffixMap[8] = 'q';

  regNameMap[1] = "al";
  regNameMap[2] = "ax";
  regNameMap[4] = "eax";
  regNameMap[8] = "rax";


  IMG_AddInstrumentFunction(ImgCallback, NULL);
  INS_AddInstrumentFunction(Instruction, NULL);
  PIN_AddFiniFunction(Fini, NULL);

  // Start the program, never returns
  PIN_StartProgram();

  return 0;
}

