/*******************************************************************************
 *
 * File: MAPProfiler.cpp
 * Description: Pin tool for tracing memory accesses.
 * 
 * Author:  Alif Ahmed
 * Email:   alifahmed@virginia.edu
 * Updated: Oct 09, 2020
 *
 ******************************************************************************/
#include "types.h"
#include "InsBase.h"
#include "InsNormal.h"
#include "InsHashedRoot.h"
#include "InsRoot.h"
#include "InsLoopBase.h"
#include "InsSingleLoop.h"
#include "PatternInfo.h"
#include "InsBlock.h"
#include "InsMultiLoop.h"
#include "InsBlock.h"
#include "PatternBase.h"
#include "PatternLoopIndexed.h"
#include "PatternInvalid.h"
#include "PatternRandom.h"
#include "PatternSmallTile.h"
#include "PatternConst.h"
#include "PatternDominant.h"

using namespace std;


/*******************************************************************************
 * Knobs for configuring the instrumentation
 ******************************************************************************/
// Name of the function to profile
KNOB<string> knobFunctionName(KNOB_MODE_WRITEONCE, "pintool", "func", "main",
    "Function to be profiled.");

// Output file name
KNOB<string> knobOutFile(KNOB_MODE_WRITEONCE, "pintool", "out", "genCode.cpp",
    "Output file name.");

// Enable Log
KNOB<bool> knobLogEn(KNOB_MODE_WRITEONCE, "pintool", "log", "0",
    "Enable logging \
        [1: enable, 0: disable (default)].");

// Keep percentage
KNOB<float> knobTopPerc(KNOB_MODE_WRITEONCE, "pintool", "top", "95",
    "Top instruction percentage.");

// Max threads
KNOB<UINT64> knobMaxThreads(KNOB_MODE_WRITEONCE, "pintool", "threads", "10000",
    "Upper limit of the number of threads that can be used by the program \
        being profiled.");

/*******************************************************************************
 * Forward declarations
 ******************************************************************************/

//void deriveAccessPattern(const vector<InsNormal*> &insList);
void derivePattern(const vector<InsNormal*> &insList);
void shiftAddressSpace(InsNormal* ins, INT64 offset);
bool isRepeat(const vector<ADDRINT> &addr, size_t sz, size_t rep, INT64 &m);
void compressCFG(set<InsBlock*> &cfg);
void generateCodeBlock(ofstream &out, InsBlock* blk, int indent);
void printDotCFG(ofstream &out, const set<InsBlock*> &cfg);

/*******************************************************************************
 * Global variables
 ******************************************************************************/
static string rtn_name;
static PIN_LOCK lock;
static bool log_en = false;
static float top_perc;
static string out_file_name;
static UINT64 rtnEntryCnt = 0;
static UINT64 __blockId = 2;

static vector<InsRoot*> insRootList;
static vector<InsHashedRoot*> insHashedRootList;

static vector<PatternInfo*> patternList;
static vector<InsBlock*> blockList;

static vector<InsNormal*> insTrace;   //td
static vector<ADDRINT> addrTrace;

static stack<ADDRINT> callStack;
static ADDRINT callHash = HASH_INIT_VALUE;

static ADDRINT globalMaxAddr = 0;

static map<UINT64, string> accTypeMap;
static map<UINT64, string> regNameMap;



/*******************************************************************************
 * Pattern Classes
 ******************************************************************************/
bool isRepeat(const vector<ADDRINT> &addr, size_t sz, size_t rep, INT64 &m){
  if(sz == 0) return false;
  if(rep == 0) return false;
  if(rep == 1) return false;
  if(sz % rep) return false;

  size_t elems = sz / rep;
  m = addr[elems] - addr[0];

  for(size_t i = 0; i < elems; i++){
    ADDRINT ref = addr[i];
    for(size_t j = 1; j < rep; j++){
      size_t idx = elems * j + i;
      if(addr[idx] != (ref + j*m)){
        return false;
      }
    }
  }

  return true;
}

void deriveLoopInfo(InsNormal* ins){
  stack<InsLoopBase*> loops;
  InsLoopBase* lp = ins->parentLoop;
  while(lp){
    loops.push(lp);
    lp = lp->parentLoop;
  }
  if(loops.size() == 0){
    return; //not inside any loops
  }

  vector<LoopInfo> _info;
  size_t sz = ins->patInfo->addr.size();
  while(loops.size()){
    lp = loops.top();
    loops.pop();
    INT64 m;
    if(isRepeat(ins->patInfo->addr, sz, lp->loopCnt, m)){
      sz = sz / lp->loopCnt;
      _info.push_back({lp, m});
    }
    else{
      _info.push_back({nullptr, 0});
    }
  }

  ins->patInfo->loops = _info;
}



/*******************************************************************************
 * Functions
 ******************************************************************************/
bool findCFGStartEnd(const set<InsBlock*> &cfg, InsBlock** s, InsBlock** e){
  *s = nullptr;
  *e = nullptr;
  for(InsBlock* blk : cfg){
    if(blk->inEdges.size() == 0){
      if(*s){ //already assigned
        return false;
      }
      *s = blk;
    }
    if(blk->outEdges.size() == 0){
      if(*e){ //already assigned
        return false;
      }
      *e = blk;
    }
  }
  return true;
}

void colorCFG(InsBlock* blk, set<InsBlock*> &visited){
  if(visited.find(blk) == visited.end()){
    visited.insert(blk);
    for(InsBlock* out : blk->outEdges){
      colorCFG(out, visited);
    }
  }
}



vector< pair<InsBlock*, UINT64> > mergeEdgeStack(vector< pair<InsBlock*, UINT64> > in){
  vector< pair<InsBlock*, UINT64> > out;
  for(auto it : in){
    if(out.empty()){
      out.push_back(it);
    }
    else{ //not the first element
      auto last = out.back();
      if(last.first == it.first){
        //same, just change count
        out.back().second += it.second;
      }
      else{
        //different, insert
        out.push_back(it);
      }
    }
  }
  return out;
}

//check if one block creates a loop
bool isSelfLoop(InsBlock* blk){
  if(blk->outEdges.find(blk) == blk->outEdges.end()){
    return false;   //does not have any self edge
  }

  //Has self edge
  //Find potential loop count
  UINT64 loopCnt = 0;
  for(auto it : blk->outEdgesStack){
    if(it.first == blk){
      loopCnt = it.second;
      break;
    }
  }
  assert(loopCnt);

  for(auto it : blk->outEdgesStack){
    if(it.first == blk){
      if(loopCnt != it.second){
        return false;
      }
    }
  }

  loopCnt++;

  // Found a loop
  // 1. Create loop inst
  InsSingleLoop* lp = new InsSingleLoop();
  lp->loopCnt = loopCnt;
  lp->ins = blk->ins;

  // 2. Fix current block
  blk->inEdges.erase(blk);
  blk->outEdges.erase(blk);
  vector< pair<InsBlock*, UINT64> > newOutEdgeStack;
  for(auto it : blk->outEdgesStack){
    if(it.first != blk){
      //only include non-self edges
      newOutEdgeStack.push_back({it.first, it.second});
    }
  }
  newOutEdgeStack = mergeEdgeStack(newOutEdgeStack);
  blk->outEdgesStack = newOutEdgeStack;
  blk->ins.clear(); //remove current instructions
  blk->ins.push_back(lp); //insert loop instruction

  return true;
}

bool isMultiLoop(set<InsBlock*> &cfg, InsBlock* root, InsBlock* a, InsBlock* b){
  if(a == b){
    return false;
  }

  if(b->outEdges.find(a) == b->outEdges.end()){
    return false;
  }

  //check if consistent loopCnt
  UINT64 loopCnt = 0;
  for(auto it : b->outEdgesStack){
    if(it.first == a){
      loopCnt = it.second;
      break;
    }
  }
  assert(loopCnt);

  for(auto it : b->outEdgesStack){
    if(it.first == a){
      if(loopCnt != it.second){
        return false;
      }
    }
  }

  //a --> b => a
  //check if Loop CFG is exclusive
  set<InsBlock*> visitedByRoot;
  set<InsBlock*> visitedByA;

  //color from root
  visitedByRoot.insert(a);
  colorCFG(root, visitedByRoot);
  colorCFG(b, visitedByRoot);
  visitedByRoot.erase(a);
  visitedByRoot.erase(b);

  //color from a
  visitedByA.insert(b);
  colorCFG(a, visitedByA);

  vector<InsBlock*> overlap;
  overlap.reserve(max(visitedByA.size(), visitedByRoot.size()));
  vector<InsBlock*>::iterator oit;
  oit = set_intersection(visitedByA.begin(), visitedByA.end(), visitedByRoot.begin(), visitedByRoot.end(), overlap.begin());
  if(oit != overlap.begin()){ //has overlap
    return false;
  }

  //create a loop inst
  InsMultiLoop* lp = new InsMultiLoop();
  lp->loopCnt = loopCnt+1;
  lp->cfg = visitedByA;
  lp->sBlk = a;
  lp->eBlk = b;

  //passed all checks! congrats!!
  //create replacement node
  InsBlock* r = new InsBlock();
  blockList.push_back(r);
  r->id = __blockId++;
  r->outEdgesStack = b->outEdgesStack;
  r->outEdges = b->outEdges;
  r->inEdges = a->inEdges;
  r->ins.push_back(lp);

  //fix edges of r
  r->inEdges.erase(b);
  r->outEdges.erase(a);

  vector< pair<InsBlock*, UINT64> > newOutEdgeStack;
  for(auto it : r->outEdgesStack){
    if(it.first != a){
      //only include non-self edges
      newOutEdgeStack.push_back({it.first, it.second});
    }
  }
  newOutEdgeStack = mergeEdgeStack(newOutEdgeStack);
  r->outEdgesStack = newOutEdgeStack;
  for(InsBlock* blk : r->outEdges){
    blk->inEdges.erase(b);
    blk->inEdges.insert(r);
  }
  for(InsBlock* blk : r->inEdges){
    blk->outEdges.erase(a);
    blk->outEdges.insert(r);
    for(size_t i = 0; i < blk->outEdgesStack.size(); i++){
      if(blk->outEdgesStack[i].first == a){
        blk->outEdgesStack[i].first = r;
      }
    }
  }


  a->inEdges.clear();
  b->outEdges.clear();
  b->outEdgesStack.clear();

  cfg = visitedByRoot;
  cfg.insert(r);

  compressCFG(lp->cfg);

  return true;
}

void mergeLoops(set<InsBlock*> &cfg){
  bool isChanged = false;

  //first, check for self loops
  for(InsBlock* blk : cfg){
    if(isSelfLoop(blk)){
      isChanged = true;
      break;
    }
  }

  InsBlock* s;
  InsBlock* e;
  if(!findCFGStartEnd(cfg, &s, &e)){
    cerr << "Cannot detect start/end block of a CFG" << endl;
    assert(0);
  }

  for(InsBlock* a : cfg){
    set<InsBlock*> vis;
    colorCFG(a, vis);   //visit all nodes reachable starting from a
    vis.erase(a);
    for(InsBlock* b : vis){
      if(isMultiLoop(cfg, s, a, b)){
        isChanged = true;
        break;
      }
    }
    if(isChanged){
      break;
    }
  }

  /*InsBlock* root = nullptr;
  set<InsBlock*> startBlks;
  for(InsBlock* blk : cfg){
    if(blk->inEdges.size() == 0){
      root = blk;
    }
    else if(blk->inEdges.size() == 2){
      startBlks.insert(blk);
    }
  }
  if(root == nullptr){
    cerr << "Cannot find CFG root" << endl;
    exit(-1);
  }

  bool isChanged = false;
  for(InsBlock* a : startBlks){
    for(InsBlock* b : a->inEdges){
      if(isConvLoop(cfg, root, a, b)){
        isChanged = true;
        break;
      }
    }
    if(isChanged){
      break;
    }
  }*/

  if(isChanged){
    compressCFG(cfg);
  }
}

void mergeBlocks(set<InsBlock*> &cfg){
  bool isChanged = false;
  for(InsBlock* in : cfg){
    if(in->id == 0) continue;   //skip begin block
    if(in->outEdgesStack.size() == 1){
      InsBlock* out = in->outEdgesStack[0].first;
      if(out->id == 1) continue;
      if(out->inEdges.size() == 1){
        //update the in edges of neighbors
        for(auto it : out->outEdges){
          it->inEdges.erase(out);
          it->inEdges.insert(in);
        }

        //replace out edges
        in->outEdgesStack = out->outEdgesStack;
        in->outEdges = out->outEdges;

        //copy instructions
        in->ins.insert(in->ins.end(), out->ins.begin(), out->ins.end());

        isChanged = true;
        cfg.erase(out);
        out->isUsed = false;
        break;
      }
    }
  }

  if(isChanged){
    compressCFG(cfg);
  }
}

void compressCFG(set<InsBlock*> &cfg){
  mergeBlocks(cfg);
  mergeLoops(cfg);
}




void printDotFile(const char* fname){
  ofstream out(fname);
  cout << "Printing " << fname << "...\n";


  out << "digraph DCFG {\n";
  for(InsBlock* blk : blockList){
    if(blk->isUsed){
      out << blk->printDot(0);
    }
  }

  out << "}\n";
}

void generateCodeHeader(ofstream &out, vector<InsNormal*> &insList){
  out << "#include <cstdlib>\n";
  out << "#include <cstdint>\n";
  out << "#include <cstdio>\n";
  out << "#include \"immintrin.h\"\n";
  out << "\n";
  out << "volatile uint8_t* gm;\n\n";
  out << "int main(){\n";
  //out << _tab(1) << "volatile uint8_t* addr = NULL;\n";
  out << _tab(1) << "uint64_t addr;\n";
  out << _tab(1) << "uint64_t hash = 0xC32ED012FEA8B4D3ULL;\n";
  out << _tab(1) << "uint64_t tmpRnd;\n";
  out << _tab(1) << "uint8_t tmpb;\n";
  out << _tab(1) << "uint16_t tmpw;\n";
  out << _tab(1) << "uint32_t tmpl;\n";
  out << _tab(1) << "uint64_t tmpq;\n";
  out << _tab(1) << "uint64_t allocSize = " << globalMaxAddr << "ULL;\n";
  out << _tab(1) << "gm = (volatile uint8_t*)malloc(allocSize);\n";
  out << _tab(1) << "if(gm == NULL) {\n";
  out << _tab(2) << "fprintf(stderr, \"Cannot allocate memory\\n\");\n";
  out << _tab(2) << "exit(-1);\n";
  out << _tab(1) << "}\n";
  out << "\n";

  /*for(InsNormal* ins : insList){
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
  }*/
  for(InsNormal* ins : insList){
    out << ins->patInfo->pat->genHeader(1);
  }
  out << "\n";
  out << _tab(1) << "goto block0;\n";
  out << "\n";
}

bool isRegularSeq(const vector<Interval> &seq){
  if (seq.size() < 3){
    return true;
  }

  UINT64 range = seq[0].e - seq[0].s;

  //check if all intervals have same range
  for(const Interval &it : seq){
    if((it.e - it.s) != range)
      return false;
  }

  //check if two consecutive intervals have same difference
  UINT64 diff = seq[1].s - seq[0].s;
  for(UINT64 i = 1; i < seq.size(); i++){
    if((seq[i].s - seq[i-1].s) != diff){
      return false;
    }
  }

  return true;
}

void generateCodeBlock(ofstream &out, InsBlock* blk, int indent){
  out << "block" << blk->id << ":\n";
  for(InsBase* base : blk->ins){
    out << base->printCodeBody(indent);
  }

  if(blk->outEdges.size() == 0){
    return;
  }

  // simple if just one edge
  if(blk->outEdgesStack.size() == 1){
    out << _tab(indent) << "goto block" << blk->outEdgesStack[0].first->id << ";\n\n";
    return;
  }


  // small number number of transitions. No need to find patterns
  if (blk->outEdgesStack.size() < 10){
    out << _tab(indent) << "//Few edges. Don't bother optimizing\n";

    out << _tab(indent) << "static uint64_t out_" << blk->id << " = 0;\n";
    out << _tab(indent) << "out_" << blk->id << "++;\n";
    UINT64 total = 0;
    UINT64 sz = blk->outEdgesStack.size();
    for(UINT64 i = 0; i < sz; i++){
      total += blk->outEdgesStack[i].second;
      out << _tab(indent);
      if(i){
        out << "else ";
      }
      if(i != (sz - 1)){
        out << "if (out_" << blk->id << " <= " << total << ") ";
      }
      out << "goto block" << blk->outEdgesStack[i].first->id << ";\n";
    }
    out << "\n\n";
    return;
  }


  //too many edges.. for now, skip...
  out << _tab(indent) << "//Many edges... print first few...\n";
  for (int i = 0; i < 10; i++){
    out << _tab(indent) << "blk_" << blk->outEdgesStack[i].first->id << " : " << blk->outEdgesStack[i].second << "\n";
  }
  out << endl;
  return;

  //remove last edge
  InsBlock* endBlock = blk->outEdgesStack.back().first;
  blk->outEdgesStack.pop_back();



  typedef struct{
    float total = 0;
    float cnt = 0;
    vector< pair<const InsBlock*, UINT64> > nextBlks;
  } BlkInfo;

  vector<const InsBlock*> jumpSeq;
  set<const InsBlock*> seenOut;

  //get count of each out block
  //also, get jump sequence
  const InsBlock* lastBlock = NULL;
  map<const InsBlock*,  BlkInfo> outInfo;
  for(const auto it : blk->outEdgesStack){
    const InsBlock* ob = it.first;
    outInfo[ob].total += it.second;
    outInfo[ob].cnt++;

    if(lastBlock){
      if(outInfo[lastBlock].nextBlks.size() == 0){
        outInfo[lastBlock].nextBlks.push_back({ob, it.second});
      }
      else if(outInfo[lastBlock].nextBlks.back().first != ob){
        outInfo[lastBlock].nextBlks.push_back({ob, it.second});
      }
      else{
        outInfo[lastBlock].nextBlks.back().second += it.second;
      }
    }
    lastBlock = ob;

    if(seenOut.find(ob) == seenOut.end()){
      jumpSeq.push_back(ob);
      seenOut.insert(ob);
    }

  }


  for(const InsBlock* it : jumpSeq){
    BlkInfo tmp = outInfo[it];
    out << _tab(indent) << "//block" << it->id << " tol: " << tmp.total << "   cnt: " << tmp.cnt << "    avg: " << tmp.total / tmp.cnt << "  ";
    for(auto s : tmp.nextBlks){
      out << ", {" << s.first->id << ": " << s.second << "}";
    }
    out << "\n";
  }

  if (jumpSeq.size() == 2){
    //special case

  }



  out << _tab(indent) << "static uint64_t out_" << blk->id << " = 0;\n";
  out << _tab(indent) << "out_" << blk->id << "++;\n";
  UINT64 total = 0;
  UINT64 sz = blk->outEdgesStack.size();
  for(UINT64 i = 0; i < sz; i++){
    total += blk->outEdgesStack[i].second;
    out << _tab(indent);
    if(i){
      out << "else ";
    }
    if(i != (sz - 1)){
      out << "if (out_" << blk->id << " <= " << total << ") ";
    }
    out << "goto block" << blk->outEdgesStack[i].first->id << ";\n";
  }
  out << _tab(indent) << "goto block" << endBlock->id << "\n\n";

}

void generateCodeFooter(ofstream &out){
  out << "block1:\n";
  out << _tab(1) << "free((void*)gm);\n";
  out << _tab(1) << "return 0;\n";
  out << "}\n";
}

void generateCode(vector<InsNormal*> &insList, const set<InsBlock*> &cfg, const char* fname){
  cout << "Generating code in: " << fname << "...\n";

  //open output file
  ofstream out(fname);

  //write headers
  generateCodeHeader(out, insList);

  //write code blocks
  for(InsBlock* blk : cfg){
    if(blk->id != 1){   //skip end block. Handled in footer
      generateCodeBlock(out, blk, 1);
    }
  }

  //write footer
  generateCodeFooter(out);

}

set<InsBlock*> cfgFromTrace(vector<InsNormal*> &trace){
  set<InsBlock*> topInsBlocks;

  InsBlock* prev = new InsBlock();    //begin block
  blockList.push_back(prev);
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
        ib->id = __blockId++;

        //InsBase* base = new InsBase();
        //baseList.push_back(base);
        //base->type = InsType::InsTypeNormal;
        //base->insNormal = ins;

        ib->ins.push_back(ins);
        topInsBlocks.insert(ib);
      }
      ttCnt++;
      //add ib as the successor of prev
      ib->inEdges.insert(prev);
      prev->outEdges.insert(ib);
      if(prev->outEdgesStack.empty()){
        //no out edge yet. add.
        prev->outEdgesStack.push_back({ib,1});
      } else if(prev->outEdgesStack.back().first == ib){
        //same as last one. increment count.
        prev->outEdgesStack.back().second++;
      } else{
        //not same as last one. add.
        prev->outEdgesStack.push_back({ib,1});
//        if(prev->outEdges.size() > 10){
//          cerr << "[ERROR]: Out edge stack size over 10. Check pattern." << endl;
//          prev = ib;
//          break;
//        }
      }
      prev = ib;
    }
  }

  //add end block
  InsBlock* ib = new InsBlock();
  blockList.push_back(ib);
  ib->id = 1;
  topInsBlocks.insert(ib);
  ib->inEdges.insert(prev);
  prev->outEdges.insert(ib);
  prev->outEdgesStack.push_back({ib,1});

  cout << "Top trace size: " << ttCnt << endl;
  return topInsBlocks;
}

set<InsBlock*> createDCFGfromInstTrace(vector<InsNormal*> &trace){
  set<InsBlock*> topInsBlocks = cfgFromTrace(trace);
  printDotFile("dcfgBC.gv");

  //compressDCFG(topInsBlocks);
  //printDot(topInsBlocks, "dcfgAC.gv");

  //mergeAllLoops(topInsBlocks);
  //markAllConvLoops(topInsBlocks);
  compressCFG(topInsBlocks);
  printDotFile("dcfgLC.gv");

  return topInsBlocks;
}

void printInfo(vector<InsNormal*> &res){
  //sort using total accessed size
  sort(res.begin(), res.end(), [](const InsNormal* lhs, const InsNormal* rhs) {
      return lhs->patInfo->totalSz > rhs->patInfo->totalSz;
  });

/*  ft_table_t *table = ft_create_table();
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

  ft_write_ln(table, "N", "Driver", "Time", "Avg Speed");

  cout << ft_to_string(table);
  ft_destroy_table(table);*/

  for(InsNormal* i : res){
    cout << "  " << setw(12) << dec << i->id << " ";
    if(i->accType == AccessType::AccessTypeRead){
      cout << "READ  : " << i->accSz;
    } else if(i->accType == AccessType::AccessTypeWrite){
      cout << "WRITE : " << i->accSz;
    } else if(i->accType == AccessType::AccessTypeRMW){
      cout << "RMW   : " << i->accSz;
    } else{
      cout << "INVALID: ";
    }
    //cout << setw(40) << i->hashedRoot->root->dis;

    cout << setw(20) << "TotalSz: " << i->patInfo->totalSz;
    cout << setw(20) << i->patInfo->pat->printPattern();
    cout << setw(10) << "[" << setw(10) << i->patInfo->addrRange.s << " : " << setw(10) << i->patInfo->addrRange.e << "]\t";
    cout << setw(10);
    for(auto s : i->patInfo->strideDist){
      cout << "{" << s.first << ":" << s.second << "} ";
    }
    cout << "\t" << i->hashedRoot->root->srcLine << "\t\t" << i->patInfo->addr.size() <<"\t";
    InsLoopBase* lp = i->parentLoop;
    //InsLoop* ol = nullptr;
    while(lp){
      //ol = lp;
      cout << lp->loopCnt << ",";
      lp = lp->parentLoop;
    }
    //if(ol != nullptr){
    //  cout << isRepeat(i->patInfo->addr, i->patInfo->addr.size(), ol->loopCnt);
    //}
    cout << dec << endl;
  }
}


UINT64 getTotalAccessSz(const vector<InsNormal*> &insList){
  UINT64 sz = 0;
  for(InsNormal* it : insList){
    sz += it->patInfo->totalSz;
  }
  return sz;
}


vector<InsNormal*> keepTop(vector<InsNormal*> &insList, double perc){
  UINT64 sz = getTotalAccessSz(insList);
  cout << "Before pruning. NumInst: " << insList.size() << "\t\tAccessSz: " << sz << endl;
  UINT64 szAfter = sz * perc / 100.0;

  //sort using total accessed size
  sort(insList.begin(), insList.end(), [](const InsNormal* lhs, const InsNormal* rhs) {
      return lhs->patInfo->totalSz > rhs->patInfo->totalSz;
  });

  vector<InsNormal*> out;
  sz = 0;
  for(InsNormal* it : insList){
    out.push_back(it);
    sz += it->patInfo->totalSz;
    if(sz > szAfter)  break;
  }

  sz = 0;
  for(InsNormal* it: out){
    sz += it->patInfo->totalSz;
  }
  cout << "After pruning. NumInst: " << out.size() << "\t\tAccessSz: " << sz << endl;
  return out;
}


vector<InsNormal*> deleteConstAccess(const vector<InsNormal*> &insList){
  vector<InsNormal*> out;
  out.reserve(insList.size());
  for(InsNormal* it : insList){
    if(it->patInfo->pat){
      if(it->patInfo->pat->type == PatType::PatTypeConst){
        continue;
      }
    }
    out.push_back(it);
  }
  return out;
}


vector<InsNormal*> deleteZeroAccesses(const vector<InsBase*> &insList){
  vector<InsNormal*> out;
  out.reserve(insList.size());
  for(InsBase* it : insList){
    if(it->type == InsTypeNormal){
      InsNormal* ins = static_cast<InsNormal*>(it);
      PatternInfo* pat = ins->patInfo;
      pat->totalSz = ins->accSz * pat->addr.size();
      if(pat->totalSz >= MIN_SZ){
        out.push_back(ins);
      }
    }
  }
  return out;
}

void shiftAddressSpace(InsNormal* ins, INT64 offset){
  PatternInfo *pat = ins->patInfo;
  pat->addrRange.s += offset;
  pat->addrRange.e += offset;
  const UINT64 cnt = pat->addr.size();
  for(UINT64 i = 0; i < cnt; i++){
    pat->addr[i] += offset;
  }
  //pat->pat->shiftAddress(offset);
  for(auto &it : pat->strideAddr){
    for(ADDRINT ea : it.second){
      it.second.erase(ea);
      it.second.insert(ea + offset);
    }
  }
  map<ADDRINT, set<INT64>> nm;
  for(auto &it : pat->addrStrideMap){
    nm[it.first + offset] = it.second;
  }
  pat->addrStrideMap = nm;
}

void derivePatternInitial(const vector<InsNormal*> &insList){
  for(InsNormal* it : insList){
    PatternInfo* pat = it->patInfo;
    bool isRandom = false;
    pat->totalSz = pat->addr.size() * it->accSz;
    ADDRINT min = 0xFFFFFFFFFFFFFFFFULL;
    ADDRINT max = 0;
    UINT64 cnt = pat->addr.size();
    INT64 lastStride = 0xDEADBEEF;
    for(UINT64 i = 0; i < (cnt - 1); i++){
      ADDRINT currAddr = pat->addr[i];
      ADDRINT nextAddr = pat->addr[i+1];

      if(currAddr > max){
        max = currAddr;
      }
      if(currAddr < min){
        min = currAddr;
      }

      if(isRandom == false){
        INT64 stride = nextAddr - currAddr;
        pat->strideDist[stride]++;
        if(stride != lastStride){
          //stride change point!
          pat->strideAddr[stride].insert(currAddr);
          pat->strideRef[stride].insert(i);
          pat->addrStrideMap[currAddr].insert(stride);
          if(pat->strideAddr.size() > MAX_STRIDE_BUCKETS){
            isRandom = true;
          }
        }
        lastStride = stride;
      }
    }
    ADDRINT lastAddr =pat->addr[cnt-1];
    if(lastAddr > max){
      max = lastAddr;
    }
    if(lastAddr < min){
      min = lastAddr;
    }
    pat->addrRange.s = min;
    pat->addrRange.e = max + it->accSz;

    //only go further if pattern type is not random
    if(isRandom){
      //create random
      it->patInfo->pat = PatternRandom::create(it);
      continue;
    }

    //check if constant/zero stride access
    if((it->patInfo->pat = PatternConst::create(it))){
      continue;
    }
  }
}

void derivePattern(const vector<InsNormal*> &insList){
  for(InsNormal* it : insList){
    //check if already assigned a pattern
    if(it->patInfo->pat){
      continue;
    }

    //check for repeats in loops
    deriveLoopInfo(it);

    //check if loop indexed
    if((it->patInfo->pat = PatternLoopIndexed::create(it))){
      continue;
    }

    //check if small tiled access
    if((it->patInfo->pat = PatternSmallTile::create(it))){
      continue;
    }

    //check if tiled access
    //if((it->patInfo->pat = PatternTile::create(it))){
    //  continue;
    //}

    //check if boundary access
    //if((it->patInfo->pat = PatternRefs::create(it))){
    //  continue;
    //}


    //check if irregular dominant stride access
    if((it->patInfo->pat = PatternDominant::create(it))){
      continue;
    }

    //check if tiled access
    //if((it->patInfo->pat = PatternTile::create(it))){
    //  continue;
    //}

    //check if boundary access
    //if((it->patInfo->pat = PatternRefs::create(it))){
    //  continue;
    //}

    //nothing matches, assign invalid
    it->patInfo->pat = PatternInvalid::create(it);
  }
}

ADDRINT getMask(ADDRINT addr){
  ADDRINT cnt = 0;
  while(!(addr & 1) && (cnt < 12)){
    cnt++;
    addr = (addr >> 1);
  }
  return ~((1ULL << cnt) - 1);
}

void markTopAndProcessInfo(vector<InsNormal*> &insList){
  for(InsNormal* it : insList){
    it->isTop = true;         //mark as top instruction
  }
}

void updateAddressSpace(vector<InsNormal*> &insList){
  //sort using min address
  sort(insList.begin(), insList.end(), [](const InsNormal* lhs, const InsNormal* rhs) {
      if(lhs->patInfo->addrRange.s == rhs->patInfo->addrRange.s){
        return lhs->patInfo->addrRange.e < rhs->patInfo->addrRange.e;
      }
      return lhs->patInfo->addrRange.s < rhs->patInfo->addrRange.s;
  });

  //update address space to remove gaps
  ADDRINT gmax = 0;
  ADDRINT gap = 0;
  for(InsNormal* it : insList){
    if(it->patInfo->addrRange.s > gmax){
      //found a gap in the address space
      gap += it->patInfo->addrRange.s - gmax;

      //ensure alignment of the original address
      gap &= getMask(it->patInfo->addrRange.s);
    }
    if(it->patInfo->addrRange.e > gmax){
      //update max address if needed
      gmax = it->patInfo->addrRange.e;
    }
    shiftAddressSpace(it, -gap);

    //update global max addresses
    if(it->patInfo->addrRange.e > globalMaxAddr){
      globalMaxAddr = it->patInfo->addrRange.e;
    }
  }
  cout << "Global max address: " << globalMaxAddr << endl;
}

void printMaxEdgeStack(const set<InsBlock*> &cfg){
  uint64_t maxEdgeStack = 0;
  uint64_t maxOutBlocks = 0;
  for(InsBlock* blk : cfg){
    if(blk->outEdges.size() > maxOutBlocks){
      maxOutBlocks = blk->outEdges.size();
    }
    if(blk->outEdgesStack.size() > maxEdgeStack){
      maxEdgeStack = blk->outEdgesStack.size();
    }
  }
  cout << "Max edge stack size: " << maxEdgeStack << endl;
  cout << "Max outgoing blocks: " << maxOutBlocks << endl;
}

void writeLog(const char* logFile){
  ofstream log(logFile);
  log << "ins,addr,r0w1\n";
  for(size_t i = 0; i < insTrace.size(); i++){
    InsNormal* ins = insTrace[i];
    if(ins->isTop){
      ADDRINT ea = ins->patInfo->addr[ins->cnt];
      ins->cnt++;
      log << ins->id << "," << ea << ",";
      if(ins->accType == AccessTypeRead){
        log << "0\n";
      }
      else if(ins->accType == AccessTypeWrite){
        log << "1\n";
      }
    }
  }
}

void printStrideAddr(const vector<InsNormal*> &insList, UINT64 id){
  cout << "Printing Stride Address for " << id << endl;
  for(InsNormal* ins : insList){
    if(ins->id == id){
      PatternInfo* pat = ins->patInfo;
      for(auto &it : pat->strideAddr){
        cout << setw(10) << it.first << ": ";
        for(ADDRINT addr : it.second){
          cout << addr << ", ";
        }
        cout << endl;
      }
      return;
    }
  }
}

void printStrideRef(const vector<InsNormal*> &insList, UINT64 id){
  cout << "Printing Stride Refs for " << id << endl;
  for(InsNormal* ins : insList){
    if(ins->id == id){
      PatternInfo* pat = ins->patInfo;
      for(auto &it : pat->strideRef){
        cout << setw(10) << it.first << ": ";
        for(ADDRINT addr : it.second){
          cout << addr << ", ";
        }
        cout << endl;
      }
      return;
    }
  }
}

VOID Fini(INT32 code, VOID *v) {
  cout << "AT FINI" << endl;
  // 0. Filter zero  (or very low) cnt instructions
  vector<InsNormal*> filteredInsList;
  cout << "Static memory instructions: Before any filtering " << InsBase::insList.size() << endl;

 
  filteredInsList = deleteZeroAccesses(InsBase::insList);
  cout << "Static memory instructions: After zero access delete " << filteredInsList.size() << endl;

  derivePatternInitial(filteredInsList);   //needed for next step
  // 1. filter constant access instructions
  filteredInsList = deleteConstAccess(filteredInsList);
  cout << "Static memory instructions: After const access delete " << filteredInsList.size() << endl;

  // 2. Only take instructions that represents top_perc of reads/writes
  filteredInsList = keepTop(filteredInsList, top_perc);
  cout << "Static memory instructions: top " << filteredInsList.size() << endl;
  markTopAndProcessInfo(filteredInsList);
  updateAddressSpace(filteredInsList);

  cout << "Inst Trace size: " << insTrace.size() << endl;
  set<InsBlock*> cfg = createDCFGfromInstTrace(insTrace);

  printMaxEdgeStack(cfg);
  derivePattern(filteredInsList);

  generateCode(filteredInsList, cfg, out_file_name.c_str());

  printInfo(filteredInsList);

  if(log_en){
    writeLog("top_trace.csv");
  }

  //printStrideAddr(filteredInsList, 394900101);
  //printStrideRef(filteredInsList, 394900101);

  //assert(callHash == HASH_INIT_VALUE);
  //for(InsNormal* it : insNormalList){ delete it; }
  for(PatternInfo* it : patternList){ delete it; }
  for(InsRoot* it : insRootList){ delete it; }
  for(InsHashedRoot* it : insHashedRootList){ delete it; }
  for(InsBlock* it : blockList){ delete it; }
  InsBase::deleteAllInst();

  cout << "DONE" << endl;
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

InsNormal* getInsLeaf(InsRoot* root, UINT32 op){
  if(root->childMap.find(callHash) == root->childMap.end()){
    //create new hashed map
    InsHashedRoot* tmp = new InsHashedRoot();
    insHashedRootList.push_back(tmp);
    tmp->root = root;
    root->childMap[callHash] = tmp;
    tmp->id = root->id * 1000 + root->childMap.size();
    for(UINT32 i = 0; i < root->opCnt; i++){
      InsNormal* ins = new InsNormal(tmp->id * 100 + i + 1);
      ins->accSz = root->opInfo[i].accSz;
      ins->accType = root->opInfo[i].accType;
      ins->hashedRoot = tmp;
      tmp->children.push_back(ins);
      ins->patInfo = new PatternInfo();
      patternList.push_back(ins->patInfo);
    }
  }
  InsHashedRoot* hrt = root->childMap[callHash];
  return hrt->children[op];
}

void record(InsRoot* root, ADDRINT ea, UINT32 op) {
  if(rtnEntryCnt <= 0)  return;
  InsNormal* ins = getInsLeaf(root, op);
  insTrace.push_back(ins);
  ins->patInfo->addr.push_back(ea);
  if(log_en){
    addrTrace.push_back(ea);
  }
}

InsRoot* createInsRoot(INS &ins){
  static UINT64 rootId = 0;
  static map<ADDRINT, InsRoot*> processedIns;   //set of already processed instructions

  ADDRINT addr = INS_Address(ins);
  // check if already processed or not
  map<ADDRINT, InsRoot*>::iterator it = processedIns.find(addr);
  if (it != processedIns.end()) {
    return it->second;   //already processed
  }

  InsRoot* root = new InsRoot();
  root->id = rootId++;
  PIN_GetSourceLocation(addr, NULL, &root->srcLine, &root->srcFile);
  root->dis = INS_Disassemble(ins);
  root->opCnt = INS_MemoryOperandCount(ins);
  for(UINT32 i = 0; i < root->opCnt; i++){
    OpInfo info;
    info.accSz = INS_MemoryOperandSize(ins, i);
    if(INS_MemoryOperandIsRead(ins,i) && !INS_MemoryOperandIsWritten(ins,i)){
      info.accType = AccessType::AccessTypeRead;
    }
    else if(!INS_MemoryOperandIsRead(ins,i) && INS_MemoryOperandIsWritten(ins,i)){
      info.accType = AccessType::AccessTypeWrite;
    }
    else if(INS_MemoryOperandIsRead(ins,i) && INS_MemoryOperandIsWritten(ins,i)){
      info.accType = AccessType::AccessTypeRMW;
    }
    else{
      info.accType = AccessType::AccessTypeInvalid;
    }

    root->opInfo.push_back(info);
  }

  insRootList.push_back(root);
  processedIns[addr] = root;
  return root;
}

void Instruction(INS ins, VOID *v) {
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

  if(memOperands){
    InsRoot* root = createInsRoot(ins);
    for (UINT32 memOp = 0; memOp < memOperands; memOp++) {
      INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record, IARG_PTR, root, IARG_MEMORYOP_EA, memOp, IARG_UINT32, memOp, IARG_END);
    }
  }
}


/*******************************************************************************
 * PIN Entry
 ******************************************************************************/
int main(int argc, char *argv[]) {
  if (PIN_Init(argc, argv)) {
    cerr << "Wrong arguments. Exiting..." << endl;
    return -1;
  }

  // Initializations
  PIN_InitLock(&lock);
  PIN_InitSymbolsAlt(IFUNC_SYMBOLS);

  rtn_name = knobFunctionName.Value();
  log_en = knobLogEn.Value();
  top_perc = knobTopPerc.Value();
  out_file_name = knobOutFile.Value();


  insRootList.reserve(100000);
  insHashedRootList.reserve(100000);
  insTrace.reserve(40000000);

  IMG_AddInstrumentFunction(ImgCallback, NULL);
  INS_AddInstrumentFunction(Instruction, NULL);
  PIN_AddFiniFunction(Fini, NULL);

  // Start the program, never returns
  PIN_StartProgram();

  return 0;
}

