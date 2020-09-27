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
#include <limits>
#include "pin.H"
//#include "lib/variadic_table/VariadicTable.h"
#include "lib/libfort/fort.h"

using namespace std;

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define MAX_STRIDE_BUCKETS  10
#define MIN_SZ              2048
#define HASH_INIT_VALUE     (0xABCDEF94ED70BA3EULL)
#define _tab(x)             setw((x)*4) << " "

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
typedef enum {InsTypeInvalid, InsTypeNormal, InsTypeLoop} InsType;
typedef enum {AccessTypeInvalid, AccessTypeRead, AccessTypeWrite, AccessTypeRMW} AccessType;
typedef enum {PatTypeInvalid, PatTypeConst, PatTypeSmallTile, PatTypeTile, PatTypeRefs, PatTypeDominant, PatTypeRandom, Pat1D} PatType;
struct InsBase;
struct InsNormal;
struct InsLoop;
struct InsBlock;
struct Interval;
struct InsRoot;
struct InsHashedRoot;
struct OpInfo;
struct PatternInfo;
class PatternBase;

//void deriveAccessPattern(const vector<InsNormal*> &insList);
void derivePattern(const vector<InsNormal*> &insList);
void shiftAddressSpace(InsNormal* ins, INT64 offset);
UINT64 isRepeat(const vector<ADDRINT> &addr);
string genReadWriteInst(const InsNormal* ins, int indent, bool useId);

/*******************************************************************************
 * Data structures
 ******************************************************************************/
typedef map<ADDRINT, InsNormal*> InfoMap;

typedef struct Interval {
  ADDRINT s = 0xFFFFFFFFFFFFFFFFULL;;
  ADDRINT e = 0;
} Interval;

typedef struct OpInfo{
  AccessType accType;
  UINT32 accSz;
} OpInfo;

typedef struct PatternInfo{
  vector<ADDRINT> addr;
  UINT64 totalSz = 0;
  Interval addrRange;
  map<ADDRINT, set<INT64>> addrStrideMap;
  map<INT64, set<ADDRINT>> strideAddr;
  map<INT64, set<ADDRINT>> strideRef;
  map<INT64, UINT64> strideDist;
  PatternBase* pat;
  INT64 rep = -1;
  //string strStart;
  //string strEnd;
  //string strCurr;
  //string strType;
} Pattern;

typedef struct InsNormal{
  PatternInfo *patInfo;
  InsHashedRoot* parent;
  UINT64 id = -1;
  UINT32 accSz;
  AccessType accType = AccessTypeInvalid;
  bool isTop = false;
  InsBlock* block = NULL;
} InsNormal;

typedef struct InsHashedRoot {
  UINT64 id;
  InsRoot* parent;
  vector<InsNormal*> children;
  UINT64 getSize() const {
    UINT64 tot = 0;
    for(InsNormal* it : children){
      tot += it->patInfo->totalSz;
    }
    return tot;
  }
} InsHashedRoot;

typedef struct InsRoot{
  UINT64 id;
  INT32 srcLine;
  string srcFile;
  string dis;
  UINT32 opCnt;
  vector<OpInfo> opInfo;
  map<ADDRINT, InsHashedRoot*> childMap;
} InsRoot;

typedef struct InsLoop {
  UINT64 id = -1;
  UINT64 loopCnt = 0;
  vector<InsBase*> ins;
}InsLoop;

typedef struct InsBlock{
  UINT64 id = -1;
  vector< pair<InsBlock*, UINT64> > outEdges;   //run count compression
  set<InsBlock*> inEdges;
  vector<InsBase*> ins;
} InsBlock;

typedef struct InsBase{
  InsType type = InsTypeInvalid;
  InsNormal* insNormal = NULL;
  InsLoop* insLoop = NULL;
}InsBase;


/*******************************************************************************
 * Global variables
 ******************************************************************************/
static string rtn_name;
static PIN_LOCK lock;
static bool log_en = false;
static float top_perc;
static string out_file_name;
static UINT64 rtnEntryCnt = 0;
static bool firstLine = true;

static vector<InsRoot*> insRootList;
static vector<InsHashedRoot*> insHashedRootList;


static vector<InsNormal*> insNormalList;
static vector<PatternInfo*> patternList;
static vector<InsBlock*> blockList;
static vector<InsBase*> baseList;
static vector<InsLoop*> loopList;

static vector<InsNormal*> insTrace;   //td

static stack<ADDRINT> callStack;
static ADDRINT callHash = HASH_INIT_VALUE;

static ADDRINT globalMaxAddr = 0;

static map<UINT64, string> accTypeMap;
static map<UINT64, char> movSuffixMap;
static map<UINT64, string> regNameMap;



/*******************************************************************************
 * Pattern Classes
 ******************************************************************************/
UINT64 isRepeat(const vector<ADDRINT> &addr){
  const size_t sz = addr.size();
  if(sz == 0) return 0;
  if(sz == 1) return 0;

  ADDRINT startAddr = addr[0];
  UINT64 lastIdx = 0;
  UINT64 gap = 0;
  for(UINT64 i = 1; i < sz; i++){
    if(addr[i] == startAddr){
      UINT64 newGap = i - lastIdx;
      lastIdx = i;
      if(gap == 0){
        gap = newGap;
      }
      if(gap != newGap){
        return 0;
      }
    }
  }

  //check min requirement
  if(gap * 2 > sz){
    return 0;
  }

  //check two consecutive patterns [should check for others too, but just assume they will match (highly likely)]
  for(UINT64 i = 0; i < gap; i++){
    if(addr[i] != addr[gap+i]){
      return 0;
    }
  }

  return gap;
}

/*class PatternFactory;
class PatternBase;
class PatternInvalid;
class PatternTile;*/

bool numModFixedHop(const set<ADDRINT> &num, UINT64 hop){
  UINT64 maxSz = num.size();
  UINT64 diff[hop];
  UINT64 prev[hop];
  for(UINT64 i = 0; i < hop; i++){
    diff[i] = 0xFFFFFFFFFFFFFFFFULL;
    prev[i] = 0xFFFFFFFFFFFFFFFFULL;
  }

  auto it = num.begin();
  for(UINT64 i = 0; i < maxSz; i++){
    UINT64 idx = i % hop;
    UINT64 c = *it++;
    UINT64 p = prev[idx];
    prev[idx] = c;
    if(p != 0xFFFFFFFFFFFFFFFFULL){
      if(diff[idx] == 0xFFFFFFFFFFFFFFFFULL){
        diff[idx] = c - p;
        continue;
      }
      if((c - p) != diff[idx]){
        return false;
      }
    }
  }
  return true;
}

UINT64 numMod(const set<ADDRINT> &num){
  if(num.size() < 3) return 1;
  for(int hop = 1; hop < 5; hop++){
    if(numModFixedHop(num, hop)){
      return hop;
    }
  }
  return 10000;
}


/*******************************************************************************
 * Pattern Base
 ******************************************************************************/
class PatternBase{
private:
  PatternBase(){};

protected:
  PatternBase(const InsNormal* _ins, PatType _type) {
    this->ins = _ins;
    this->type = _type;
  }

public:
  PatType type;
  const InsNormal* ins;

  virtual ~PatternBase(){};
  virtual void shiftAddress(INT64 offset) {}
  virtual string genHeader(UINT32 indent) {return ""; }
  virtual string genBody(UINT32 indent) {
    stringstream ss;
    ss << _tab(indent) << "ID: " << ins->id << "\n";
    ss << _tab(indent) << "Type: ";
    if(ins->accType == AccessType::AccessTypeRead)        ss << "READ\n";
    else if(ins->accType == AccessType::AccessTypeWrite)  ss << "WRITE\n";
    else if(ins->accType == AccessType::AccessTypeRMW)    ss << "RMW\n";
    else                                                  ss << "Invalid\n";
    ss << _tab(indent) << "Code Line: " << ins->parent->parent->srcLine << "\n";
    ss << _tab(indent);
    for(auto s : ins->patInfo->strideDist){
      ss << "{" << s.first << ":" << s.second << "} ";
    }
    ss << "\n";
    ss << _tab(indent) << ins->patInfo->pat->printPattern() << "\n";
    ss << _tab(indent) << ins->patInfo->addrRange.e - ins->patInfo->addrRange.s << " [ " << ins->patInfo->addrRange.s << " : " << ins->patInfo->addrRange.e << " ]\n";
    return ss.str();
  }
  //virtual string genFooter() { return ""; }
  virtual string printPattern() = 0;
};


/*******************************************************************************
 * Pattern 1D array
 ******************************************************************************/
/*class Pattern1D : public PatternBase{
private:
  Pattern1D(const InsNormal* _ins) : PatternBase(_ins, PatType::Pat1D) {}

public:
  static Pattern1D* create(const InsNormal* _ins){
    //check if inside a loop
    if(ins->parent->)
  }

  string printPattern(){
    return "1D";
  }
};*/


/*******************************************************************************
 * Pattern Random
 ******************************************************************************/
class PatternRandom : public PatternBase{
private:
  PatternRandom(const InsNormal* _ins) : PatternBase(_ins, PatType::PatTypeRandom) {}

public:
  static PatternRandom* create(const InsNormal* _ins){
    return new PatternRandom(_ins);
  }

  string genBody(UINT32 indent){
    stringstream ss;
    //first, generate random address within range, and without accessing memory
    ss << _tab(indent) << "hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);\n";
    ss << _tab(indent) << "addr = ((hash % " << ins->patInfo->addrRange.e - ins->patInfo->addrRange.s << ") + " << ins->patInfo->addrRange.s << ") & ~" << ins->accSz-1 << "ULL;\n";
    ss << genReadWriteInst(ins, indent, false);
    return ss.str();
  }

  string printPattern(){
    return "Random";
  }
};


/*******************************************************************************
 * Pattern Invalid
 ******************************************************************************/
class PatternInvalid : public PatternBase{
private:
  PatternInvalid() : PatternBase(nullptr, PatType::PatTypeInvalid) {}
  static PatternInvalid pat;

public:
  static PatternInvalid* create(const InsNormal* _ins){
    return &pat;
  }

  string printPattern(){
    return "Invalid";
  }
};
PatternInvalid PatternInvalid::pat;



/*******************************************************************************
 * Pattern Dominant
 ******************************************************************************/
class PatternDominant : public PatternBase{
private:
  PatternDominant(const InsNormal* ins, INT64 _domStride) : PatternBase(ins, PatType::PatTypeDominant), domStride(_domStride) {}
  INT64 domStride = 0;

public:
  static PatternDominant* create(const InsNormal* ins){
    for(const auto &it : ins->patInfo->strideDist){
      if(it.second * ins->accSz > ins->patInfo->totalSz * 0.8){
        //found dominant stride
        return new PatternDominant(ins, it.first);
      }
    }
    return nullptr;
  }

  string printPattern(){
    stringstream ss;
    ss << "Dom: " << domStride;
    return ss.str();
  }
};


/*******************************************************************************
 * Pattern Const
 ******************************************************************************/
class PatternConst : public PatternBase{
private:
  PatternConst() : PatternBase(nullptr, PatType::PatTypeConst) {}
  static PatternConst pat;

public:
  static PatternConst* create(const InsNormal* ins){
    if(ins->patInfo->strideDist.find(0) != ins->patInfo->strideDist.end()){
      UINT64 zeroCnt = ins->patInfo->strideDist[0];
      //if zero stride access contributes more than 80%
      if(zeroCnt * ins->accSz > ins->patInfo->totalSz * 0.8){
        return &pat;
      }
    }
    return nullptr;
  }

  string printPattern(){
    return "Const";
  }
};
PatternConst PatternConst::pat;


/*******************************************************************************
 * Pattern Refs
 ******************************************************************************/
class PatternRefs : public PatternBase{
  typedef struct {
    INT64 stride;
    ADDRINT offset;
    ADDRINT mod;
  } StrideInfo;

private:
  PatternRefs();
  PatternRefs(const InsNormal* _ins, vector<StrideInfo> &infoList, UINT64 _maxHop) : PatternBase(_ins, PatType::PatTypeRefs), maxHop(_maxHop){
    this->strideInfoList = infoList;
  }
  vector<StrideInfo> strideInfoList;
  UINT64 maxHop = 0;

public:
  static PatternRefs* create(const InsNormal* ins){
    const auto &strideRefs = ins->patInfo->strideRef;

    vector<StrideInfo> infoList;

    UINT64 maxHop = 1;
    for(auto sset : strideRefs){
      const INT64 stride = sset.first;
      set<ADDRINT> &refs = sset.second;
      if(refs.size() == 1) {
        StrideInfo info;
        info.stride = stride;
        info.mod = -1;
        info.offset = 0;
        infoList.push_back(info);
        continue;
      }

      UINT64 hop = numMod(refs);
      if(hop > maxHop){
        maxHop = hop;
      }
      if(maxHop > 20){
        return nullptr;
      }

      /*auto it = refs.begin();
      ADDRINT first = *it;
      it++;
      ADDRINT prev = *it;
      const UINT64 diff = prev - first;   //assumed difference
      it++;
      for( ; it != refs.end(); it++){
        ADDRINT curr = *it;
        if(diff != (curr - prev)){
          return nullptr;
        }
        prev = curr;
      }
      StrideInfo info;
      info.stride = stride;
      info.mod = diff;
      info.offset = first;
      infoList.push_back(info);*/
    }
    return new PatternRefs(ins, infoList, maxHop);
  }

  void shiftAddress(INT64 offset){
    for(auto &it : strideInfoList){
      it.offset += offset;
    }
  }

  string printPattern(){
    stringstream ss;
    ss << "Refs: " << maxHop;
    return ss.str();
  }
};




/*******************************************************************************
 * Pattern Small Tile
 ******************************************************************************/
class PatternSmallTile : public PatternBase{
private:
  PatternSmallTile(const InsNormal* _ins) : PatternBase(_ins, PatType::PatTypeSmallTile){};

public:
  static PatternSmallTile* create(const InsNormal* ins){
    if(ins->patInfo->addrStrideMap.size() > 5){
      return nullptr;   //too many if statement
    }

    //check validity
    for(auto it : ins->patInfo->addrStrideMap){
      if(it.second.size() != 1){
        return nullptr;
      }
    }

    //fits!!
    return new PatternSmallTile(ins);
  }

  string genHeader(UINT32 indent) {
    stringstream ss;
    if(ins->patInfo->addrStrideMap.size() == 1){
      ss << _tab(indent) << "uint64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] << ";\n";
    }
    else{
      ss << _tab(indent) << "uint64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] << ", strd_" << ins->id << " = 0;\n";
    }
    return ss.str();
  }

  string genBody(UINT32 indent) {
    stringstream ss;
    if(ins->patInfo->addrStrideMap.size() == 1){
      ss << genReadWriteInst(ins, indent, true);
      auto it = ins->patInfo->addrStrideMap.begin();
      ss << _tab(indent) << "addr_" << ins->id << " += " << *(it->second.begin()) << ";\n";
    }
    else{
      ss << genReadWriteInst(ins, indent, true);
      ss << _tab(indent) << "switch(addr_" << ins->id << ") {\n";
      for(auto it : ins->patInfo->addrStrideMap){
        ss << _tab(indent+1) << "case " << it.first << " : strd_" << ins->id << " = " << *(it.second.begin()) << "; break;\n";
      }
      //ss << _tab(indent+1) << "default : strd_" << ins->id << " = 0;\n";
      ss << _tab(indent) << "}\n";
      ss << _tab(indent) << "addr_" << ins->id << " += strd_" << ins->id << ";\n";
    }
    return ss.str();
  }

  string printPattern(){
    stringstream ss;
    ss << "SmallTile" << ins->patInfo->addrStrideMap.size();
    return ss.str();
  }
};




/*******************************************************************************
 * Pattern Tile
 ******************************************************************************/
class PatternTile : public PatternBase{
  typedef struct {
    INT64 stride;
    ADDRINT offset;
    ADDRINT mod;
  } StrideInfo;

private:
  PatternTile();
  PatternTile(const InsNormal* _ins, vector<StrideInfo> &infoList, UINT64 _maxHop) : PatternBase(_ins, PatType::PatTypeTile), maxHop(_maxHop){
    this->strideInfoList = infoList;
  }
  vector<StrideInfo> strideInfoList;
  UINT64 maxHop;

public:
  static PatternTile* create(const InsNormal* ins){
    const auto &strideAddr = ins->patInfo->strideAddr;

    set<ADDRINT> unionSet;
    UINT64 totPoints = 0;
    for(auto it : strideAddr){
      totPoints += it.second.size();
      unionSet.insert(it.second.begin(), it.second.end());
    }
    if(totPoints != unionSet.size()){
      return nullptr;   //different stride at same address
    }

    vector<StrideInfo> infoList;

    UINT64 maxHop = 1;
    for(auto sset : strideAddr){
      const INT64 stride = sset.first;
      set<ADDRINT> &addr = sset.second;
      if(addr.size() == 1) {
        StrideInfo info;
        info.stride = stride;
        info.mod = -1;
        info.offset = 0;
        infoList.push_back(info);
        continue;
      }

      UINT64 hop = numMod(addr);
      if(hop > maxHop){
        maxHop = hop;
      }
      if(maxHop > 20){
        return nullptr;
      }
      /*auto it = addr.begin();
      ADDRINT first = *it;
      it++;
      ADDRINT prev = *it;
      const UINT64 diff = prev - first;   //assumed difference
      it++;
      for( ; it != addr.end(); it++){
        ADDRINT curr = *it;
        if(diff != (curr - prev)){
          return nullptr;
        }
        prev = curr;
      }
      StrideInfo info;
      info.stride = stride;
      info.mod = diff;
      info.offset = first;
      infoList.push_back(info);*/
    }
    return new PatternTile(ins, infoList, maxHop);
  }

  void shiftAddress(INT64 offset){
    for(auto &it : strideInfoList){
      it.offset += offset;
    }
  }

  string printPattern(){
    stringstream ss;
    ss << "Tile: " << maxHop;
    return ss.str();
  }
};


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
        InsBlock* out = in->outEdges[0].first;
        if(out->id == 1) continue;
        if(out->inEdges.size() == 1){
          //update the in edges of neighbors
          for(auto it : out->outEdges){
            it.first->inEdges.erase(out);
            it.first->inEdges.insert(in);
          }

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
  for(InsBlock* blk : cfg){
    if(blk->outEdges.size() < 2) continue;
    if(!(blk->outEdges.size() % 2)){
      bool isLoop = true;
      uint64_t pred_iter = blk->outEdges[0].second;
      for(uint64_t i = 0; i < blk->outEdges.size(); i++){
        if(!(i % 2)){
          //even index
          if((blk->outEdges[i].second != pred_iter) || (blk->outEdges[i].first != blk)){
            isLoop = false;
            break;
          }
        }
        else{
          //odd index
          if(blk->outEdges[i].second != 1){
            isLoop = false;
            break;
          }
        }
      }
      if(isLoop){
        //fix out edges
        vector< pair<InsBlock*, UINT64> > old_edges = blk->outEdges;
        blk->outEdges.clear();
        blk->outEdges.push_back({old_edges[1].first, 0});
        for(auto it : old_edges){
          InsBlock* nextBlk = it.first;
          if(nextBlk != blk){
            if(blk->outEdges.back().first == nextBlk){
              blk->outEdges.back().second++;
            }
            else{
              blk->outEdges.push_back({nextBlk, 1});
            }
          }
        }

        InsLoop* loop = new InsLoop();
        loopList.push_back(loop);
        InsBase* base = new InsBase();
        baseList.push_back(base);

        static UINT64 loopId = 0;
        loop->loopCnt = pred_iter + 1;
        loop->ins = blk->ins;    //copy
        loop->id = loopId++;
        blk->ins.clear();

        base->type = InsType::InsTypeLoop;
        base->insLoop = loop;
        blk->ins.push_back(base);
        blk->inEdges.erase(blk);
        isChanged = true;
      }
    }
  }
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
    //if(!firstLine){
      out << "<br />";
    //}
    firstLine = false;
    for(UINT32 i = 0; i < indent; i++){
      out << "  ";
    }
    if(it->type == InsType::InsTypeNormal){
      /*InsNormal* ins = it->insNormal;
      out << setw(4) << ins->id << ":";
      if(ins->accType == AccessType::AccessTypeRead){
        out << "RD ";
      }
      else if(ins->accType == AccessType::AccessTypeWrite){
        out << "WR ";
      }
      out << ins->patInfo->pat->printPattern();
      out << " A" << ins->accSz << " [" << ins->patInfo->addrRange.s << ":" << ins->patInfo->addrRange.e << ")";*/
      InsNormal* ins = it->insNormal;
      out << ins->id << ": ";
      out << ins->parent->parent->srcLine << ", " << ins->patInfo->pat->printPattern();
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
      out << "Block: " << ib->id;
      printInsLabel(out, ib->ins, 0);
      out << "</TD></TR> </table> >];\n";
    }
    map<InsBlock*, UINT64> outBlocks;
    for(auto it : ib->outEdges){
      outBlocks[it.first] += it.second;
    }

    for(auto it : outBlocks){
      InsBlock* o = it.first;
      out << "\tB" << ib->id;// << ":o" << cnt;
      out << " -> B" << o->id;// << ":i";
      out << " [label=\"" << it.second << "\"];\n";
    }
  }

  out << "}\n";
}


string genReadWriteInst(const InsNormal* ins, int indent, bool useId){
  stringstream ad;
  if(useId){
    ad << "addr_" << ins->id;
  }
  else{
    ad << "addr";
  }

  stringstream ss;
  if(ins->accType == AccessType::AccessTypeRead){
    ss << _tab(indent) << "__asm__ __volatile__ (\"mov" << movSuffixMap[ins->accSz] << " (%1,%2), %0\" : \"=r\"(tmp" << movSuffixMap[ins->accSz] <<
        ") : \"r\"(gm), \"r\"(" << ad.str() << ") : \"memory\");\n";
  }
  else if(ins->accType == AccessType::AccessTypeWrite){
    ss << _tab(indent) << "__asm__ __volatile__ (\"mov" << movSuffixMap[ins->accSz] << " %2, (%0,%1)\" : : \"r\"(gm), \"r\"(" << ad.str() <<
        "), \"r\"(tmp" << movSuffixMap[ins->accSz] << ") : \"memory\");\n";
  }
  else{
    cerr << "[ERROR] Unimplemented access type for " << ins->id << endl;
    return "";
  }
  return ss.str();
}

void generateCodeInst(ofstream &out, InsNormal* ins, int indent){
  out << ins->patInfo->pat->genBody(indent);
  out << "\n";
  /*if(ins->pType == PatType::PatTypeSeq){
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
    generateRandom(out, indent);
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
  out << "\n";*/
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

UINT64 numOutBlocks(const InsBlock* blk){
  set<InsBlock*> blkSet;
  for(auto it : blk->outEdges){
    blkSet.insert(it.first);
  }
  return blkSet.size();
}

void generateCodeBlock(ofstream &out, InsBlock* blk, int indent){
  out << "block" << blk->id << ":\n";
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

  // simple if just one edge
  if(blk->outEdges.size() == 1){
    out << _tab(indent) << "goto block" << blk->outEdges[0].first->id << ";\n\n";
    return;
  }


  // small number number of transitions. No need to find patterns
  if (blk->outEdges.size() < 10){
    out << _tab(indent) << "//Few edges. Don't bother optimizing\n";

    out << _tab(indent) << "static uint64_t out_" << blk->id << " = 0;\n";
    out << _tab(indent) << "out_" << blk->id << "++;\n";
    UINT64 total = 0;
    UINT64 sz = blk->outEdges.size();
    for(UINT64 i = 0; i < sz; i++){
      total += blk->outEdges[i].second;
      out << _tab(indent);
      if(i){
        out << "else ";
      }
      if(i != (sz - 1)){
        out << "if (out_" << blk->id << " <= " << total << ") ";
      }
      out << "goto block" << blk->outEdges[i].first->id << ";\n";
    }
    out << "\n\n";
    return;
  }

  /*if(int numOut = numOutBlocks(blk) == 2){
    auto outEdges = blk->outEdges;


    // two outblocks
    if(numOut % 2){
      // case ABABAB....A

    }
    else{
      // case ABABAB....AB

    }
    return;
  }*/



  //remove last edge
  InsBlock* endBlock = blk->outEdges.back().first;
  blk->outEdges.pop_back();



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
  for(const auto it : blk->outEdges){
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
  UINT64 sz = blk->outEdges.size();
  for(UINT64 i = 0; i < sz; i++){
    total += blk->outEdges[i].second;
    out << _tab(indent);
    if(i){
      out << "else ";
    }
    if(i != (sz - 1)){
      out << "if (out_" << blk->id << " <= " << total << ") ";
    }
    out << "goto block" << blk->outEdges[i].first->id << ";\n";
  }
  out << _tab(indent) << "goto block" << endBlock->id << "\n\n";



  /*// check if regular pattern
  map<InsBlock*, vector<Interval>> blkSeq;

  //get access intervals for each block
  UINT64 cnt = 1;
  for(auto it : blk->outEdges){
    UINT64 sz = it.second;
    Interval itv;
    itv.s = cnt;
    itv.e = cnt + sz - 1;
    blkSeq[it.first].push_back(itv);
    cnt = cnt + sz;
  }

  cnt = 0;
  for(auto &it : blkSeq){
    if(isRegularSeq(it.second)){
      cnt++;
    }
  }

  if(cnt >= blkSeq.size()){
    out << _tab(indent) << "//Regular out block pattern\n\n";

  }
  else{
    out << _tab(indent) << "//Irregular out block pattern\n\n";

  }*/
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
      if(prev->outEdges.empty()){
        //no out edge yet. add.
        prev->outEdges.push_back({ib,1});
      } else if(prev->outEdges.back().first == ib){
        //same as last one. increment count.
        prev->outEdges.back().second++;
      } else{
        //not same as last one. add.
        prev->outEdges.push_back({ib,1});
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
  ib->id = 1;
  topInsBlocks.insert(ib);
  ib->inEdges.insert(prev);
  prev->outEdges.push_back({ib,1});

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
    cout << setw(40) << i->parent->parent->dis;

    cout << setw(20) << "TotalSz: " << i->patInfo->totalSz;
    cout << setw(20) << i->patInfo->pat->printPattern();
    cout << setw(10) << "[" << setw(10) << i->patInfo->addrRange.s << " : " << setw(10) << i->patInfo->addrRange.e << "]\t";
    cout << setw(10);
    for(auto s : i->patInfo->strideDist){
      cout << "{" << s.first << ":" << s.second << "} ";
    }
    cout << "\t" << i->parent->parent->srcLine;
    //cout << "\tRep: " << isRepeat(i->patInfo->addr);
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
    if(it->patInfo->pat->type == PatType::PatTypeConst){
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
    PatternInfo* pat = it->patInfo;
    pat->totalSz = it->accSz * pat->addr.size();
    if(pat->totalSz >= MIN_SZ){
      out.push_back(it);
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
  pat->pat->shiftAddress(offset);
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

void derivePattern(const vector<InsNormal*> &insList){
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

    if(it->id == 430200101){
      cout << "dev pat" << endl;
    }

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

    //check if small tiled access
    if((it->patInfo->pat = PatternSmallTile::create(it))){
      continue;
    }

    //check if tiled access
    if((it->patInfo->pat = PatternTile::create(it))){
      continue;
    }

    //check if boundary access
    if((it->patInfo->pat = PatternRefs::create(it))){
      continue;
    }


    //check if irregular dominant stride access
    if((it->patInfo->pat = PatternDominant::create(it))){
      continue;
    }

    //nothing matches, assign as random access
    it->patInfo->pat = PatternRandom::create(it);
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
    set<InsBlock*> outBlocks;
    for(auto it : blk->outEdges){
      outBlocks.insert(it.first);
    }
    if(outBlocks.size() > maxOutBlocks){
      maxOutBlocks = outBlocks.size();
    }
    if(blk->outEdges.size() > maxEdgeStack){
      maxEdgeStack = blk->outEdges.size();
    }
  }
  cout << "Max edge stack size: " << maxEdgeStack << endl;
  cout << "Max outgoing blocks: " << maxOutBlocks << endl;
}

void writeLog(const char* logFile, const vector<InsNormal*> &insList){
  ofstream log(logFile);
  log << "ins,addr,r0w1\n";
  for(const InsNormal* ins : insList){
    if(ins->isTop){
      const UINT64 id = ins->id;
      for(ADDRINT ea : ins->patInfo->addr){
        log << id << ',' << ea << ',';
        if(ins->accType == AccessTypeRead){
          log << "0\n";
        }
        else if(ins->accType == AccessTypeWrite){
          log << "1\n";
        }
        else{
          cerr << "Unimplemented instruction access type!" << endl;
          exit(-1);
        }
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
  cout << "Static memory instructions: Before any filtering " << insNormalList.size() << endl;

  filteredInsList = deleteZeroAccesses(insNormalList);
  cout << "Static memory instructions: After zero access delete " << filteredInsList.size() << endl;

  derivePattern(filteredInsList);   //needed for next step
  // 1. filter constant access instructions
  filteredInsList = deleteConstAccess(filteredInsList);
  cout << "Static memory instructions: After const access delete " << filteredInsList.size() << endl;

  // 2. Only take instructions that represents top_perc of reads/writes
  filteredInsList = keepTop(filteredInsList, top_perc);
  cout << "Static memory instructions: top " << filteredInsList.size() << endl;
  markTopAndProcessInfo(filteredInsList);

  printInfo(filteredInsList);

  cout << "Inst Trace size: " << insTrace.size() << endl;
  set<InsBlock*> cfg = createDCFGfromInstTrace(insTrace);
  printMaxEdgeStack(cfg);
  generateCode(filteredInsList, cfg, out_file_name.c_str());

  if(log_en){
    writeLog("top_trace.csv", filteredInsList);
  }

  printStrideAddr(filteredInsList, 394900101);
  printStrideRef(filteredInsList, 394900101);

  //assert(callHash == HASH_INIT_VALUE);
  for(InsNormal* it : insNormalList){ delete it; }
  for(PatternInfo* it : patternList){ delete it; }
  for(InsRoot* it : insRootList){ delete it; }
  for(InsHashedRoot* it : insHashedRootList){ delete it; }
  for(InsBlock* it : blockList){ delete it; }
  for(InsBase* it : baseList){ delete it; }
  for(InsLoop* it : loopList){ delete it; }
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
    tmp->parent = root;
    root->childMap[callHash] = tmp;
    tmp->id = root->id * 1000 + root->childMap.size();
    for(UINT32 i = 0; i < root->opCnt; i++){
      InsNormal* ins = new InsNormal();
      insNormalList.push_back(ins);
      ins->accSz = root->opInfo[i].accSz;
      ins->accType = root->opInfo[i].accType;
      ins->parent = tmp;
      ins->id = tmp->id * 100 + i + 1;
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

