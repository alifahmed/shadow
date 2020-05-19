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
#include "pin.H"

using namespace std;

/*******************************************************************************
 * Knobs for configuring the instrumentation
 ******************************************************************************/
// Name of the function to profile
KNOB<string> knobFunctionName(KNOB_MODE_WRITEONCE, "pintool", "func", "main",
    "Function to be profiled.");

// Max log items per thread
KNOB<UINT64> knobMaxLog(KNOB_MODE_WRITEONCE, "pintool", "lim", "1000000",
    "Max number of read/writes to log per thread.");

// Output file name
KNOB<string> knobOutFile(KNOB_MODE_WRITEONCE, "pintool", "out", "mem_trace.csv",
    "Output file name.");

// Max threads
KNOB<UINT64> knobMaxThreads(KNOB_MODE_WRITEONCE, "pintool", "threads", "10000",
    "Upper limit of the number of threads that can be used by the program \
        being profiled.");

// Stack based access logging (1: enable, 0: disable)
KNOB<bool> knobStack(KNOB_MODE_WRITEONCE, "pintool", "stack", "0",
    "Stack based access logging \
        [1: enable, 0: disable (default)].");

// Instruction pointer relative access logging (1: enable, 0: disable)
KNOB<bool> knobIP(KNOB_MODE_WRITEONCE, "pintool", "ip", "1",
    "IP relative access logging \
        [1: enable (default), 0: disable].");

// Read logging (1: enable, 0: disable)
KNOB<bool> knobRead(KNOB_MODE_WRITEONCE, "pintool", "read", "1",
    "Read logging \
        [1: enable (default), 0: disable].");

// Write logging (1: enable, 0: disable)
KNOB<bool> knobWrite(KNOB_MODE_WRITEONCE, "pintool", "write", "1",
    "Write \
        logging [1: enable (default), 0: disable].");

/*******************************************************************************
 * Structs
 ******************************************************************************/
struct InsBase;

typedef struct InstInfo{
  string dis;
  UINT64 totalSz = 0;
  UINT64 cnt = 0;
  ADDRINT lastEA = -1;
  INT64 lastStride = -1;
  UINT64 sameStrideCnt = 0;
  INT64 totalStride = 0;
  ADDRINT startAddr = -1;
  ADDRINT endAddr = 0;
  ADDRINT instAddr = -1;
} InstInfo;

typedef struct InsLoop {
  UINT64 loopCnt = 0;
  vector<InsBase*> ins;
}InsLoop;

typedef struct InsBlock{
  UINT64 id = -1;
  bool isTop = false;
  map<InsBlock*, UINT64> outEdges;   //successors and count
  //map<InsBlock*, UINT64> inEdges;    //predecessors and count
  set<InsBlock*> inEdges;
  vector<InsBase*> ins;
  //vector<InstInfo*> ins;
} InsBlock;

typedef enum {InsTypeInvalid, InsTypeNormal, InsTypeLoop} InsType;

typedef struct InsBase{
  InsType type = InsTypeInvalid;
  //InstInfo* insNormal = NULL;
  string insNormal = "";
  InsLoop* insLoop = NULL;
}InsBase;

map<ADDRINT, InsBlock*> insAddrToBlk;
vector<ADDRINT> insTrace;
vector<InsLoop*> loops;
vector<InsBase*> bases;

typedef map<ADDRINT, InstInfo*> InfoMap;

InfoMap rInfo;
InfoMap wInfo;

// Limit of buffer entry. Maps to knobMaxLog.
UINT64 buf_log_lim;

// Current count of log entry.
UINT64 buf_log_cnt;

// Name of the function that is being profiled. Maps to knobFunctionName.
string rtn_name;

// Lock for synchronizing thread access to 'info' array.
PIN_LOCK lock;

// Read logging is enabled if true. Maps to knobRead.
bool read_log_en = true;

// Write logging is enabled if true. Maps to knobWrite.
bool write_log_en = true;

static UINT64 rtnEntryCnt = 0;

/*******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * Prints usage message. This function is called if any argument is invalid.
 */
INT32 Usage() {
  cerr << "This tool profiles a function\'s memory access pattern." << endl;
  cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
  return -1;
}

/**
 * Function for recording read access.
 */
void record(InstInfo* info, ADDRINT ea, UINT32 sz) {
  if(rtnEntryCnt <= 0)  return;
  info->totalSz += sz;
  if(info->cnt){
    INT64 stride = (ea - info->lastEA);
    info->totalStride += stride;
    if(stride == info->lastStride){
      info->sameStrideCnt++;
    }
    info->lastStride = stride;
  }
  if(ea < info->startAddr){
    info->startAddr = ea;
  }
  if(ea > info->endAddr){
    info->endAddr = ea;
  }
  info->lastEA = ea;
  info->cnt++;
  insTrace.push_back(info->instAddr);
}

InstInfo* checkIns(INS &ins, InfoMap &im) {
  ADDRINT addr = INS_Address(ins);
  if (im.find(addr) == im.end()) {
    //does not exists
    InstInfo* info = new InstInfo();
    //info->ins = ins;
    info->dis = INS_Disassemble(ins);
    info->instAddr = INS_Address(ins);
    im[addr] = info;
    if(insAddrToBlk.find(addr) == insAddrToBlk.end()){
      static UINT64 id = 2;
      InsBlock* ib = new InsBlock();
      InsBase* base = new InsBase();
      ib->id = id++;
      base->type = InsType::InsTypeNormal;
      base->insNormal = info->dis;
      //ib->ins.push_back(base);
      ib->ins.push_back(base);
      bases.push_back(base);
      insAddrToBlk[addr] = ib;
    }
  }
  return im[addr];
}

static UINT64 memInstCnt = 0;

/**
 * Instruments instructions having read or write accesses.
 */
VOID Instruction(INS ins, VOID *v) {
  // Get the memory operand count of the current instruction.
  UINT32 memOperands = INS_MemoryOperandCount(ins);

  if (memOperands == 0) return;
  memInstCnt++;

  // Iterate over each memory operand of the instruction.
  for (UINT32 memOp = 0; memOp < memOperands; memOp++) {
    if (INS_MemoryOperandIsRead(ins, memOp) && read_log_en) {
      InstInfo* info = checkIns(ins, rInfo);
      // Operand is read by this instruction.
      INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record,
          IARG_PTR, info, IARG_MEMORYOP_EA, memOp, IARG_UINT32, INS_MemoryOperandSize(ins, memOp), IARG_END);
    }

    if (INS_MemoryOperandIsWritten(ins, memOp) && write_log_en) {
      InstInfo* info = checkIns(ins, wInfo);
      // Operand is written by this instruction.
      INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record,
          IARG_PTR, info, IARG_MEMORYOP_EA, memOp, IARG_UINT32, INS_MemoryOperandSize(ins, memOp), IARG_END);
    }
  }
}

/**
 * Keeps track of the function entry.
 */
VOID RtnEntry(THREADID tid) {
  //tdata[tid].rtnEntryCnt++;
  rtnEntryCnt++;
}

/**
 * Keeps track of the function exit.
 */
VOID RtnLeave(THREADID tid) {
  //tdata[tid].rtnEntryCnt--;
  rtnEntryCnt--;
}


typedef struct BblInfo {
  UINT64 id = -1;
  //UINT64 count = 0;
  bool isUsing = true;
  bool entered = false;
  map<BblInfo*, UINT64> outEdges;   //successors and count
  map<BblInfo*, UINT64> inEdges;    //predecessors and count
  map<ADDRINT, bool> insMap;
} BblInfo;

map<ADDRINT, UINT64>  bblAddrIdMap;
map<UINT64, BblInfo*> bblIdInfoMap;
vector<UINT64> bblTrace;
vector<UINT64> bblTraceTop;

VOID BblEntry(UINT64 bi) {
  if(rtnEntryCnt > 0){
    bblTrace.push_back(bi);
  }
}

UINT64 getBBLId(BBL bbl){
  static UINT64 id = 1;
  ADDRINT addr = BBL_Address(bbl);
  if(bblAddrIdMap.find(addr) == bblAddrIdMap.end()){
    //create new object
    BblInfo* bi = new BblInfo();
    bi->id = id++;
    bblAddrIdMap[addr] = bi->id;
    bblIdInfoMap[id] = bi;
    for(INS ins = BBL_InsHead(bbl); ins != BBL_InsTail(bbl); ins = INS_Next(ins)){
      if(INS_Valid(ins)){
        bi->insMap[INS_Address(ins)] = true;
      }
    }
    bi->insMap[INS_Address(BBL_InsTail(bbl))] = true;
    assert(bi->insMap.size() == BBL_NumIns(bbl));
  }
  return bblAddrIdMap[addr];
}

VOID TrcCallback(TRACE trace, VOID *arg){
  for( BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl) ){
    UINT64 bi = getBBLId(bbl);
    BBL_InsertCall(bbl, IPOINT_BEFORE, (AFUNPTR) BblEntry, IARG_UINT64, bi, IARG_END);
  }
}


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
        loops.push_back(loop);
        InsBase* base = new InsBase();
        bases.push_back(base);

        loop->loopCnt = loopCnt;
        loop->ins = in->ins;    //copy
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

bool firstLine = true;

void printInsLabel(ofstream &out, const vector<InsBase*> &insts, UINT32 indent){
  for(InsBase* it : insts){
    if(!firstLine){
      out << "<br />";
    }
    firstLine = false;
    for(UINT32 i = 0; i < indent; i++){
      out << " &nbsp; &nbsp; ";
    }
    if(it->type == InsType::InsTypeNormal){
      out << it->insNormal;
      //out << "\\n";
    }
    else if(it->type == InsType::InsTypeLoop){
      InsLoop* loop = it->insLoop;
      out << "Loop: " << loop->loopCnt;
      //out << "\\n";
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
      out << "\tB" << ib->id << " [shape=plain, label=< <table>";
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

void generateInst(ofstream &out, InsBlock* ins){

}

void generateCode(set<InsBlock*> &cfg, const char* fname){
  //find root node
  InsBlock* root = NULL;
  for(InsBlock* ins : cfg){
    if(ins->id == 0){
      root = ins;
      break;
    }
  }
  assert(root != NULL);

  //open output file
  ofstream out(fname);

  //write headers

  //write code blocks
  generateInst(out, root);

  //write footer

}

set<InsBlock*> createDCFGfromInstTrace(vector<ADDRINT> &trace){
  /*for(auto it : insAddrToBlk){
    it.second->entered = false;
    it.second->inEdges.clear();
    it.second->outEdges.clear();
  }*/

  //generate edges and edge count for each top instructions
  set<InsBlock*> topInsBlocks;
  InsBlock* prev = NULL;
  UINT64 ttCnt = 0;
  for(ADDRINT addr : trace){
    InsBlock* ib = insAddrToBlk[addr];
    if(ib->isTop){
      topInsBlocks.insert(ib);
      ttCnt++;
      if(prev != NULL){
        //add bi as the successor of prev
        //ib->inEdges[prev]++;
        ib->inEdges.insert(prev);
        prev->outEdges[ib]++;
      }
      prev = ib;
    }
  }
  cout << "Top trace size: " << ttCnt << endl;
  printDot(topInsBlocks, "dcfgBC.gv");

  compressDCFG(topInsBlocks);
  printDot(topInsBlocks, "dcfgAC.gv");

  mergeAllLoops(topInsBlocks);
  printDot(topInsBlocks, "dcfgLC.gv");

  return topInsBlocks;
}

/**
 * Finds and instruments the requested routine.
 */
VOID ImgCallback(IMG img, VOID *arg) {
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
          RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) RtnEntry, IARG_THREAD_ID,
              IARG_END);
          RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) RtnLeave, IARG_THREAD_ID,
              IARG_END);
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
          RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) RtnEntry, IARG_THREAD_ID,
              IARG_END);
          RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) RtnLeave, IARG_THREAD_ID,
              IARG_END);
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

#define CNT_TH    100

void deleteZeroAccesses(InfoMap &mp){
  for(auto it = mp.begin(); it != mp.end();){
    if(it->second->cnt == 0){
      mp.erase(it++);
    }
    else{
      it++;
    }
  }
}

void deleteConstAccess(InfoMap &mp){
  for(auto it = mp.begin(); it != mp.end();){
    //double sameStrideCnt = (double)(it->second->sameStrideCnt);
    double cnt = (double)(it->second->cnt);
    //double sameStrideRatio = sameStrideCnt / cnt;
    double AvgStride = (double)(it->second->totalStride) / cnt;

    if(abs(AvgStride) < 0.1){   //over 90% with same stride, and average stride is very low.
      mp.erase(it++);
    }
    else{
      it++;
    }

    //bool isSameStride = (sameStrideRatio > 0.9) || (sameStrideCnt == (cnt - 1));


  }
}

UINT64 getTotalAccessSz(InfoMap &mp){
  UINT64 sz = 0;
  for(auto ptr : mp){
    sz += ptr.second->totalSz;
  }
  return sz;
}

void printInfo(const vector<InstInfo*> &res){
  for(InstInfo* i : res){
    cout << setw(20) << hex << i->instAddr << dec << "\t";
    cout << setw(50) << dec << i->dis;
    //cout << setw(20) << "TotalSz: " << i->totalSz << "\t\t";
    cout << setw(20) << "Count: " << i->cnt << "\t";
    cout << setw(20) << "AvgStride: " << (double)(i->totalStride) / (double)(i->cnt) << "\t";
    cout << setw(20) << "Same Stride Cnt: " << i->sameStrideCnt << "\t";
    cout << setw(20) << "Start Addr: " << hex << i->startAddr << "\t";
    cout << setw(20) << "End Addr: " << hex << i->endAddr << "\t";
    cout << dec << endl;
    delete i;
  }
}

vector<InstInfo*> keepTop(InfoMap &mp, double perc){
  UINT64 sz = getTotalAccessSz(mp);
  cout << "Before pruning. NumInst: " << mp.size() << "\t\tAccessSz: " << sz << endl;
  UINT64 szAfter = sz * perc / 100.0;
  vector<InstInfo*> top, res;
  top.reserve(mp.size());
  top.reserve(mp.size());

  //copy
  for(auto ptr : mp){
    top.push_back(ptr.second);
  }

  //sort
  sort(top.begin(), top.end(), [](const InstInfo* lhs, const InstInfo* rhs) {
      return lhs->totalSz > rhs->totalSz;
  });

  sz = 0;
  for(InstInfo* it : top){
    res.push_back(it);
    insAddrToBlk[it->instAddr]->isTop = true;
    sz += it->totalSz;
    if(sz > szAfter)  break;
  }

  sz = 0;
  for(InstInfo* it: res){
    sz += it->totalSz;
  }
  cout << "After pruning. NumInst: " << res.size() << "\t\tAccessSz: " << sz << endl;
  return res;
}

void deleteInfoMap(InfoMap &mp){
  for(auto it : mp){
    delete it.second;
  }
}

void deleteBblMap(){
  for(auto it : bblIdInfoMap){
    delete it.second;
  }
}

void deleteInsBlockMap(){
  for(auto it : insAddrToBlk){
    delete it.second;
  }
}

void deleteLoops(){
  for(InsLoop* i : loops){
    delete i;
  }
}

void deleteBases(){
  for(InsBase* i : bases){
    delete i;
  }
}

void printBblInfo(UINT64 id){
  BblInfo* bi = bblIdInfoMap[id];
  cout << "id: " << id;
  cout << "\tisUsing: " << bi->isUsing;
  cout << "\tentered: " << bi->entered << endl;
  for(auto it : bi->insMap){
    cout << "\t" << hex << it.first << dec << endl;
    if(rInfo.find(it.first) != rInfo.end()){
      cout << "\t" << rInfo[it.first]->dis << endl;
    }
    if(wInfo.find(it.first) != wInfo.end()){
      cout << "\t" << wInfo[it.first]->dis << endl;
    }
  }
}


VOID Fini(INT32 code, VOID *v) {
  // add finish trace to insTrace
  InsBlock* end = new InsBlock();
  end->id = 1;
  end->isTop = true;
  insTrace.push_back(1);
  insAddrToBlk[1] = end;

  // 0. Filter zero  (or very low) cnt instructions
  deleteZeroAccesses(rInfo);
  deleteZeroAccesses(wInfo);

  // 1. Delete constant access instructions
  deleteConstAccess(rInfo);
  deleteConstAccess(wInfo);

  // 2. Calculate total reads / writes
  //UINT64 rdSz = getTotalAccessSz(rInfo);
  //UINT64 wrSz = getTotalAccessSz(wInfo);
  //cout << "Read size: " << rdSz << endl;
  //cout << "Write size: " << wrSz << endl;

  //createDCFGfromTrace(bblTrace);

  // 3. Only take instructions that represents 90% of reads/writes
  auto rRes = keepTop(rInfo, 95);
  auto wRes = keepTop(wInfo, 95);

  //mark BBL
  /*for(auto it : bblIdInfoMap){
    BblInfo* bi = it.second;
    bi->isUsing = false;
    for(InstInfo* rr : rRes){
      ADDRINT addr = rr->instAddr;
      if(bi->insMap.find(addr) != bi->insMap.end()){
        bi->isUsing = true;
        break;
      }
    }
    if(bi->isUsing == false){
      for(InstInfo* ww : wRes){
        ADDRINT addr = ww->instAddr;
        if(bi->insMap.find(addr) != bi->insMap.end()){
          bi->isUsing = true;
          break;
        }
      }
    }
  }*/

  //copy top trace
  /*bblTraceTop.clear();
  for(UINT64 id : bblTrace){
    BblInfo* bi = bblIdInfoMap[id];
    if(bi->isUsing){
      bblTraceTop.push_back(id);
    }
  }*/
  //cout << "Orig Trace size: " << bblTrace.size() << endl;
  //cout << "Top trace size: " << bblTraceTop.size() << endl;

  //createDCFGfromTrace(bblTrace);

  cout << endl << "============================================ READS ==============================================" << endl;
  //printInfoAndDelete(rInfo);
  printInfo(rRes);

  cout << endl << "============================================ WRITES =============================================" << endl;
  //printInfoAndDelete(wInfo);
  printInfo(wRes);

  cout << "Inst Trace size: " << insTrace.size() << endl;
  /*vector<ADDRINT> topTrace;
  topTrace.reserve(insTrace.size());
  for(ADDRINT addr : insTrace){
    if(insAddrToBlk[addr]->isTop){
      topTrace.push_back(addr);
    }
  }
  cout << "Top Trace size: " << topTrace.size() << endl;*/

  set<InsBlock*> cfg = createDCFGfromInstTrace(insTrace);

  generateCode(cfg, "code.ii");

  deleteInfoMap(rInfo);
  deleteInfoMap(wInfo);
  deleteInsBlockMap();
  deleteLoops();
  deleteBases();
  //deleteBblMap();
}

/**
 * Entry point
 */
int main(int argc, char *argv[]) {
  if (PIN_Init(argc, argv)) {
    return Usage();
  }

  // Initializations
  PIN_InitLock(&lock);
  PIN_InitSymbolsAlt(IFUNC_SYMBOLS);

  rtn_name = knobFunctionName.Value();
  read_log_en = knobRead.Value();
  write_log_en = knobWrite.Value();

  insTrace.reserve(40000000);

  InsBlock* begin = new InsBlock();
  begin->id = 0;
  begin->isTop = true;
  insTrace.push_back(0);
  insAddrToBlk[0] = begin;

  //bblTrace.reserve(1000000);
  //BblInfo* begin = new BblInfo();
  //begin->id = 0;
  //begin->entered = true;
  //bblTrace.push_back(0);
  //bblAddrIdMap[-1] = 0;
  //bblIdInfoMap[0] = begin;

  IMG_AddInstrumentFunction(ImgCallback, NULL);
  INS_AddInstrumentFunction(Instruction, NULL);
  //TRACE_AddInstrumentFunction(TrcCallback, NULL);
  PIN_AddFiniFunction(Fini, NULL);

  // Start the program, never returns
  PIN_StartProgram();

  return 0;
}

