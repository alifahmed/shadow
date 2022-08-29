#include <InsLoop.h>
#include "types.h"
#include "cln_utils.h"
#include "InsBase.h"
#include "InsHashedRoot.h"
#include "InsRoot.h"
#include "InsMem.h"
#include "InsCondJump.h"
#include "InsLoop.h"
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
#include "InsRand.h"
#include "InsMix.h"
#include <unordered_map>
#include <algorithm>
#include <set>

#include "pinplay.H"
#include "dcfg_pin_api.H"
#include "dcfg_trace_api.H"
#include "dcfg_api.H"
#include "pin.H"

using namespace std;
using namespace dcfg_pin_api;
using namespace dcfg_trace_api;
using namespace dcfg_api;

/*******************************************************************************
 * Knobs for configuring the instrumentation
 ******************************************************************************/
// Name of the function to profile
KNOB<string> knobFunctionName(KNOB_MODE_WRITEONCE, "pintool", "func", "main",
		"Function to be profiled.");

// Output file name
KNOB<string> knobOutFile(KNOB_MODE_WRITEONCE, "pintool", "out", "genCode.cpp",
		"Output file name.");

KNOB<string> knobStatFile(KNOB_MODE_WRITEONCE, "pintool", "stat", "cloneStat.log",
		"Clone statistics file name.");

// Enable Log
KNOB<bool> knobLogEn(KNOB_MODE_WRITEONCE, "pintool", "log", "0",
		"Enable logging \
        [1: enable, 0: disable (default)].");

// Keep percentage
KNOB<float> knobTopPerc(KNOB_MODE_WRITEONCE, "pintool", "top", "95",
		"Top instruction percentage.");
KNOB<INT64> knobInterval(KNOB_MODE_WRITEONCE, "pintool", "step", "-1",
		"Interval in number of memory instructions executed");
KNOB<INT64> knobStart(KNOB_MODE_WRITEONCE, "pintool", "start", "0",
		"Profiling starts after this many number of memory instructions executed");

KNOB<UINT64> knobMaxInst(KNOB_MODE_WRITEONCE, "pintool", "maxinst", "-1",
		"Profile upto maxinst number of instructions (any type, not just memory instructions)");

// DCFG and PinPlay intergration
PINPLAY_ENGINE pinplay_engine;
KNOB<BOOL> KnobPinPlayReplayer(KNOB_MODE_WRITEONCE, 
                      "pintool", "replay", "0",
                      "Activate the pinplay replayer");

// Max threads
//KNOB<UINT64> knobMaxThreads(KNOB_MODE_WRITEONCE, "pintool", "threads", "10000",	"Upper limit of the number of threads that can be used by the program being profiled.");

/*******************************************************************************
 * Forward declarations
 ******************************************************************************/

//void deriveAccessPattern(const vector<InsNormal*> &insList);
void derivePattern(const vector<InsMem*> &insList);
void shiftAddressSpace(InsMem *ins, INT64 offset);
void compressCFG(set<InsBlock*> &cfg);
void printDotCFG(ofstream &out, const set<InsBlock*> &cfg);
void printDotFile(const char *fname);

/*******************************************************************************
 * Global variables
 ******************************************************************************/
static string rtn_name;
//static PIN_LOCK lock;
static bool log_en = false;
static float top_perc;
static string out_file_name;
static string stat_file_name;
static INT64 rtnEntryCnt = 0;
static INT64 interval = 0;
static UINT64 MAX_INST = 0;
static INT64 startCnt = 0;
static INT64 startCntSaved = 0;
static UINT64 intervalCnt = 0;
static UINT64 instCount = 0;

static InsMix insMixCnt;

static vector<InsRoot*> insRootList;
static vector<InsHashedRoot*> insHashedRootList;

//static vector<InsNormal*> insTrace;   //td
//static vector<InsBase*> insTrace;   //td
static vector<InsMem*> insTrace;   //td
//static vector<ADDRINT> addrTrace;

static stack<ADDRINT> callStack;
static ADDRINT callHash = HASH_INIT_VALUE;

static set<ADDRINT> vpnSet;
static map<ADDRINT, ADDRINT> vpnToPpnMap;
static vector<string> codeFragments;

static InsBlock* beginBlock = nullptr;
static InsBlock* endBlock = nullptr;

//static map<UINT64, string> accTypeMap;
//static map<UINT64, string> regNameMap;

//static uint64_t edgeStatDirect = 0;
//static uint64_t edgeStatOrdered = 0;
//static uint64_t edgeStatRandom = 0;
uint64_t edgeDynDirect = 0;
uint64_t edgeDynOrdered = 0;
uint64_t edgeDynRandom = 0;

static uint64_t instStatDom = 0;
static uint64_t instStatLoopedIndex = 0;
static uint64_t instStatRandom = 0;
static uint64_t instDynDom = 0;
static uint64_t instDynLoopedIndex = 0;
static uint64_t instDynRandom = 0;

static ofstream cloneLog;

typedef struct {
	set<InsMem*> statMemInst;
	uint64_t dynMemInst = 0;
	uint64_t totMemUsage = 0;
} FilterInfo;

static FilterInfo fInfoOrig;
static FilterInfo fInfoAfterZero;
static FilterInfo fInfoTop;

/************************* DCFG Global variables ******************************/
static string dcfg_cfg_file, dcfg_trace_file;
static ofstream shadow_output, dcfg_output;
// static uint64_t shadow_cnt = 0, dcfg_cnt = 0;
static bool dcfg_trace_done;
DCFG_PIN_MANAGER *dcfgMgr;
DCFG_DATA *dcfgData;
DCFG_PROCESS_CPTR dcfgProcInfo;
DCFG_TRACE_READER* dcfgTraceReader;

DCFG_ID_VECTOR dcfgTraceBuffer;
DCFG_ID_VECTOR::iterator dcfgTraceBufferPtr;

// static UINT64 total_addr = 0, total_addr_in_bbl = 0;
const UINT64 BBL_INVALID = 0xFFFFFFFFFFFFFFFF;

set<InsBlock*> DCFG;

/*******************************************************************************
 * Pattern Classes
 ******************************************************************************/
static inline ADDRINT getPageNum(ADDRINT addr){
	return addr & 0xFFFFFFFFFFFFF000UL;
}

static void genVpnToPpnMap(){
	uint64_t ppn = 0;
	for (UINT64 vpn : vpnSet) {
		vpnToPpnMap[vpn] = ppn << 12;
		ppn++;
	}
}

static inline ADDRINT virtToPhyConvert(ADDRINT vAddr){
	return vpnToPpnMap[getPageNum(vAddr)] + (vAddr & 0xFFFUL);
}


string replaceVtoPAddr(const string &str){
	stringstream ss;
	const UINT64 len = str.length();
	UINT64 lastPos = 0;
	for(UINT64 i = 0; i < len; i++){
		if(str[i] == '@' && str[i+1] == '{'){
			ss << str.substr(lastPos, i - lastPos);
			i++;
			UINT64 val = 0;
			while(str[++i] != '}'){
				val = val * 10UL + str[i] - '0';
			}
			ss << virtToPhyConvert(val) << "LL";
			lastPos = ++i;
		}
	}
	ss << str.substr(lastPos, len - lastPos);
	return ss.str();
}


void deriveLoopInfo(InsMem *ins) {

	typedef struct {
		InsLoop *lp = nullptr;
		UINT64 cumProd = 1;
	} LInfo;

	stack<LInfo> loops;
	InsLoop *lp = ins->parentLoop;
	UINT64 prod = 1;
	while (lp) {
		loops.push( { lp, prod });
		prod *= lp->iters;
		lp = lp->parentLoop;
	}
	if (loops.size() == 0) {
		return; //not inside any loops
	}

	size_t sz = ins->addr.size();
	//check outermost loop
	if (sz % prod) {
		return;
	}
	INT64 m;
	if (cln_utils::isRepeat(ins->addr, sz, sz / prod, m)) {
		if (m) {
			return;
		}
	}

	vector<LoopInfo> _info;
	sz = prod;
	while (loops.size()) {
		auto linfo = loops.top();
		loops.pop();
		if (sz % linfo.cumProd) {
			_info.push_back( { nullptr, 0 });
			break;
		}

		if (cln_utils::isRepeat(ins->addr, sz, sz / linfo.cumProd, m)) {
			sz = linfo.cumProd;
			_info.push_back( { linfo.lp, m });
		} else {
			_info.push_back( { nullptr, 0 });
			break;
		}
	}

	ins->loops = _info;
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
bool findCFGStartEnd(const set<InsBlock*> &cfg, InsBlock **s, InsBlock **e) {
	*s = nullptr;
	*e = nullptr;
	for (InsBlock *blk : cfg) {
		if (blk->inEdges.size() == 0) {
			if (*s) { //already assigned
				return false;
			}
			*s = blk;
		}
		if (blk->outEdges.size() == 0) {
			if (*e) { //already assigned
				return false;
			}
			*e = blk;
		}
	}
	return true;
}

void colorCFG(InsBlock *blk, set<InsBlock*> &visited) {
	if (visited.find(blk) == visited.end()) {
		visited.insert(blk);
		for (InsBlock *out : blk->outEdges) {
			colorCFG(out, visited);
		}
	}
}

vector<pair<InsBlock*, UINT64> > mergeEdgeStack(
		vector<pair<InsBlock*, UINT64> > in) {
	vector<pair<InsBlock*, UINT64> > out;
	for (auto it : in) {
		if (out.empty()) {
			out.push_back(it);
		} else { //not the first element
			auto last = out.back();
			if (last.first == it.first) {
				//same, just change count
				out.back().second += it.second;
			} else {
				//different, insert
				out.push_back(it);
			}
		}
	}
	return out;
}

bool isCommonLoop(set<InsBlock*> &cfg, InsBlock *blk) {
	if (blk->ins.size() || (blk->outEdges.size() == 0)) {
		return false;     //for now, only supports empty origin blocks
	}
	InsBlock *target = blk->outEdgesStack[0].first;
	if ((target->inEdges.size() != 1) || (target->outEdges.size() != 1)
			|| (target->outEdgesStack[0].first != blk)) {
		return false;
	}

	//potential target found. Check edge stack
	//UINT64 loopCnt = blk->outEdgesStack[0].second;
	UINT64 totalCnt = 0;
	UINT64 entryCnt = 0;

	for (size_t i = 0; i < blk->outEdgesStack.size(); i++) {
		if (i & 1) {    //odd
			//out edge count should be 1 (loop exit)
			if (blk->outEdgesStack[i].second != 1)
				return false;
			//totalCnt++;
			entryCnt++;
		} else {         //even
			//should be same block, and same loop count
			if (blk->outEdgesStack[i].first != target)
				return false;
			//if (blk->outEdgesStack[i].second != loopCnt)
			//  return false;
			totalCnt += blk->outEdgesStack[i].second;
		}
	}

	UINT64 loopCnt = totalCnt / entryCnt;
	UINT64 rem = totalCnt % entryCnt;
	if (rem) {
		loopCnt++;
	}

	// Found a loop
	// 1. Create loop inst
	InsLoop *lp = new InsLoop(InsTypeSingleLoop);
	lp->iters = loopCnt;
	lp->ins = target->ins;

	// 2. Fix current block
	blk->removeOutEdge(target);
	blk->inEdges.erase(target);
	blk->ins.push_back(lp); //insert loop instruction

	// 3. Invalidate target block
	cfg.erase(target);
	target->isUsed = false;

	//take care of remaining counts (if any)
	if (rem) {
		stringstream ss;
		ss << "static int64_t loop" << lp->id << "_break = " << totalCnt
				<< "ULL;\n";
		lp->prefix.push_back(ss.str());

		ss.str("");
		ss.clear();
		ss << "if(loop" << lp->id << "_break-- <= 0) break;\n";
		lp->postfix.push_back(ss.str());
	}
	return true;
	//return false;
}

//check if one block creates a loop
bool isSelfLoop(InsBlock *blk) {
	if (blk->outEdgesStack.size() == 0) {
		return false; //no out edges
	}
	if (blk->outEdges.find(blk) == blk->outEdges.end()) {
		return false;   //does not have any self edge
	}

	if (blk->ins.size() == 0) { //jmp block with loop, just remove the edge
		blk->removeOutEdge(blk);
		blk->inEdges.erase(blk);
		return true;
	}

	if (blk->outEdgesStack[0].first != blk) {
		return false; // pattern does not match
	}

	//UINT64 loopCnt = blk->outEdgesStack[0].second;
	UINT64 totalCnt = 0;
	UINT64 entryCnt = 0;

	for (size_t i = 0; i < blk->outEdgesStack.size(); i++) {
		if (i & 1) {    //odd
			//out edge count should be 1 (loop exit)
			if (blk->outEdgesStack[i].second != 1)
				return false;
			totalCnt++;
			entryCnt++;
		} else {         //even
			//should be same block, and same loop count
			if (blk->outEdgesStack[i].first != blk)
				return false;
			//if (blk->outEdgesStack[i].second != loopCnt)
			//	return false;
			totalCnt += blk->outEdgesStack[i].second;
		}
	}

	UINT64 loopCnt = totalCnt / entryCnt;
	UINT64 rem = totalCnt % entryCnt;
	if (rem) {
		loopCnt++;
	}

	// Found a loop
	// 1. Create loop inst
	InsLoop *lp = new InsLoop(InsTypeSingleLoop);
	lp->iters = loopCnt;
	lp->ins = blk->ins;

	// 2. Fix current block
	blk->inEdges.erase(blk);
	blk->outEdges.erase(blk);
	vector<pair<InsBlock*, UINT64> > newOutEdgeStack;
	for (auto it : blk->outEdgesStack) {
		if (it.first != blk) {
			//only include non-self edges
			newOutEdgeStack.push_back( { it.first, it.second });
		}
	}
	newOutEdgeStack = mergeEdgeStack(newOutEdgeStack);
	blk->outEdgesStack = newOutEdgeStack;
	blk->ins.clear(); //remove current instructions
	blk->ins.push_back(lp); //insert loop instruction

	//take care of remaining counts (if any)
	if (rem) {
		stringstream ss;
		ss << "static int64_t loop" << lp->id << "_break = " << totalCnt
				<< "ULL;\n";
		lp->prefix.push_back(ss.str());

		ss.str("");
		ss.clear();
		ss << "if(loop" << lp->id << "_break-- <= 0) break;\n";
		lp->postfix.push_back(ss.str());
	}

	return true;
}

/*bool isMultiLoop(set<InsBlock*> &cfg, InsBlock *root, InsBlock *a, InsBlock *b) {
 if (a == b) {
 return false;
 }

 if (b->outEdges.find(a) == b->outEdges.end()) {
 return false;
 }

 //check if consistent loopCnt
 UINT64 loopCnt = 0;
 for (auto it : b->outEdgesStack) {
 if (it.first == a) {
 loopCnt = it.second;
 break;
 }
 }
 assert(loopCnt);

 for (auto it : b->outEdgesStack) {
 if (it.first == a) {
 if (loopCnt != it.second) {
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
 oit = set_intersection(visitedByA.begin(), visitedByA.end(), visitedByRoot.begin(), visitedByRoot.end(),
 overlap.begin());
 if (oit != overlap.begin()) { //has overlap
 return false;
 }

 //create a loop inst
 InsMultiLoop *lp = new InsMultiLoop();
 lp->iters = loopCnt + 1;
 lp->cfg = visitedByA;
 lp->sBlk = a;
 lp->eBlk = b;

 //passed all checks! congrats!!
 //create replacement node
 InsBlock *r = new InsBlock();
 r->outEdgesStack = b->outEdgesStack;
 r->outEdges = b->outEdges;
 r->inEdges = a->inEdges;
 r->ins.push_back(lp);

 //fix edges of r
 r->inEdges.erase(b);
 r->outEdges.erase(a);

 vector<pair<InsBlock*, UINT64> > newOutEdgeStack;
 for (auto it : r->outEdgesStack) {
 if (it.first != a) {
 //only include non-self edges
 newOutEdgeStack.push_back( { it.first, it.second });
 }
 }
 newOutEdgeStack = mergeEdgeStack(newOutEdgeStack);
 r->outEdgesStack = newOutEdgeStack;
 for (InsBlock *blk : r->outEdges) {
 blk->inEdges.erase(b);
 blk->inEdges.insert(r);
 }
 for (InsBlock *blk : r->inEdges) {
 blk->outEdges.erase(a);
 blk->outEdges.insert(r);
 for (size_t i = 0; i < blk->outEdgesStack.size(); i++) {
 if (blk->outEdgesStack[i].first == a) {
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
 }*/

bool mergeMultiLoops(set<InsBlock*> &cfg) {
	/*InsBlock* s;
	 InsBlock* e;
	 if(!findCFGStartEnd(cfg, &s, &e)){
	 printDotFile("dcfgErr.gv");
	 cerr << "Cannot detect start/end block of a CFG" << endl;
	 assert(0);
	 }

	 bool isChanged = false;
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

	 return isChanged;*/
	return false;
}

bool mergeCommonLoop(set<InsBlock*> &cfg) {
	bool isChanged = false;

	//first, check for self loops
	for (InsBlock *blk : cfg) {
		if (isCommonLoop(cfg, blk)) {
			isChanged = true;
			break;
		}
	}

	return isChanged;
}

bool mergeSingleLoops(set<InsBlock*> &cfg) {
	bool isChanged = false;

	//first, check for self loops
	for (InsBlock *blk : cfg) {
		if (isSelfLoop(blk)) {
			isChanged = true;
			break;
		}
	}

	return isChanged;
}

bool mergeBlocks(set<InsBlock*> &cfg) {
	bool isChanged = false;
	for (InsBlock *in : cfg) {
		if (in == beginBlock)
			continue;   //skip begin block
		if (in->outEdgesStack.size() == 1) {
			InsBlock *out = in->outEdgesStack[0].first;
			if (out == endBlock)	//skip end block
				continue;
			if ((out->inEdges.size() == 1) || (in->ins.size() == 0)) {
				//fix incoming neighbors
				for (InsBlock *ib : in->inEdges) {
					ib->replaceOutEdge(in, out);
					out->inEdges.erase(in);
					out->inEdges.insert(ib);
				}

				//append instructions
				in->ins.insert(in->ins.end(), out->ins.begin(), out->ins.end());
				out->ins = in->ins;

				//remove from cfg
				isChanged = true;
				cfg.erase(in);
				in->isUsed = false;
				break;
			}
		}
	}

	return isChanged;
}

void compressCFG(set<InsBlock*> &cfg) {
	//static UINT32 dfCounter = 0;
	//static char dfName[32];
	while (true) {
		while (mergeBlocks(cfg))
			;      // First, merge all blocks
		if (mergeSingleLoops(cfg)) {    // Try to merge a self loop
			continue;                 // Found a self loop, start from beginning
		}
		if (mergeCommonLoop(cfg)) {    // Try to merge a common loop
			continue;
		}
		if (!mergeMultiLoops(cfg)) { // Last resort, try to merge multi block loops
			break;                      // Not found anything, quit
		}
		//sprintf(dfName, "dots/gv/dot%dq", dfCounter++);
		//printDotFile(dfName);
	}
}

void updateParentLoops(set<InsBlock*> &cfg) {
	for (InsBlock *blk : cfg) {
		blk->setParentLoop(nullptr);
	}
}

void printDotFile(const char *fname) {
	ofstream out(fname);
	cout << "Printing " << fname << "..." << endl;

	out << "digraph DCFG {\n";
	out << InsBlock::printDotAll(0);
	out << "}\n";
}

void generateCodeHeader(ofstream &out) {
	out << "#include <cstdlib>\n";
	out << "#include <cstdint>\n";
	out << "#include <cstdio>\n";
	out << "#include \"immintrin.h\"\n";
	out << "\n";
	out
			<< "__attribute__((always_inline)) static inline uint64_t bounded_rnd(uint64_t bound) {\n";
	out << _tab(1) << "static uint64_t hash = 0xC32ED012FEA8B4D3ULL;\n";
	out << _tab(1) << "hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);\n";
	out << _tab(1) << "return (hash * (__uint128_t)bound) >> 64;\n";
	out << "}\n";
	out << "\n";
	out
			<< "#define READ_1b(X)  __asm__ __volatile__ (\"movb       (\%1,\%2), \%0\" : \"=r\"(tmp1)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define READ_2b(X)  __asm__ __volatile__ (\"movw       (\%1,\%2), \%0\" : \"=r\"(tmp2)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define READ_4b(X)  __asm__ __volatile__ (\"movl       (\%1,\%2), \%0\" : \"=r\"(tmp4)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define READ_8b(X)  __asm__ __volatile__ (\"movq       (\%1,\%2), \%0\" : \"=r\"(tmp8)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define READ_16b(X) __asm__ __volatile__ (\"movdqa     (\%1,\%2), \%0\" : \"=r\"(tmp16) : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define READ_32b(X) __asm__ __volatile__ (\"vmovdqa    (\%1,\%2), \%0\" : \"=r\"(tmp32) : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define READ_64b(X) __asm__ __volatile__ (\"vmovdqa32  (\%1,\%2), \%0\" : \"=r\"(tmp64) : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define READ_16b(X) tmp16 = _mm_load_si128((__m128i const*)(gm + (X)))\n";
	out
			<< "#define READ_32b(X) tmp32 = _mm256_load_si256((__m256i const*)(gm + (X)))\n";
	out
			<< "#define READ_64b(X) tmp64 = _mm512_load_si512((__m512i const*)(gm + (X)))\n";
	out << "\n";
	out
			<< "#define WRITE_1b(X)  __asm__ __volatile__ (\"movb      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp1)  : \"memory\")\n";
	out
			<< "#define WRITE_2b(X)  __asm__ __volatile__ (\"movw      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp2)  : \"memory\")\n";
	out
			<< "#define WRITE_4b(X)  __asm__ __volatile__ (\"movl      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp4)  : \"memory\")\n";
	out
			<< "#define WRITE_8b(X)  __asm__ __volatile__ (\"movq      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp8)  : \"memory\")\n";
	//out << "#define WRITE_16b(X) __asm__ __volatile__ (\"movdqa    \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp16) : \"memory\")\n";
	//out << "#define WRITE_32b(X) __asm__ __volatile__ (\"vmovdqa   \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp32) : \"memory\")\n";
	//out << "#define WRITE_64b(X) __asm__ __volatile__ (\"vmovdqa32 \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp64) : \"memory\")\n";
	out
			<< "#define WRITE_16b(X) _mm_store_si128((__m128i*)(gm + (X)), tmp16)\n";
	out
			<< "#define WRITE_32b(X) _mm256_store_si256((__m256i*)(gm + (X)), tmp32)\n";
	out
			<< "#define WRITE_64b(X) _mm512_store_si512((__m512i*)(gm + (X)), tmp64)\n";
	out << "\n";
	out
			<< "#define RMW_1b(X)  __asm__ __volatile__ (\"addb $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define RMW_2b(X)  __asm__ __volatile__ (\"addw $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define RMW_4b(X)  __asm__ __volatile__ (\"addl $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out
			<< "#define RMW_8b(X)  __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define RMW_16b(X) __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define RMW_32b(X) __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define RMW_64b(X) __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out << "\n";
	out << "volatile uint8_t* gm;\n";  //[" << globalMaxAddr << "ULL];\n\n";
	out << "#ifdef __SSE2__\n";
	out << _tab(1) << "volatile __m128i tmp16;\n";
	out << "#endif\n";
	out << "#ifdef __AVX__\n";
	out << _tab(1) << "volatile __m256i tmp32;\n";
	out << "#endif\n";
	out << "#ifdef __AVX512F__\n";
	out << _tab(1) << "volatile __m512i tmp64;\n";
	out << "#endif\n\n";
	out << "int main(){\n";
	//out << _tab(1) << "volatile uint8_t* addr = NULL;\n";
	out << _tab(1) << "int64_t addr;\n";
	//out << _tab(1) << "uint64_t hash = 0xC32ED012FEA8B4D3ULL;\n";
	out << _tab(1) << "uint64_t tmpRnd;\n";
	out << _tab(1) << "uint8_t tmp1;\n";
	out << _tab(1) << "uint16_t tmp2;\n";
	out << _tab(1) << "uint32_t tmp4;\n";
	out << _tab(1) << "uint64_t tmp8;\n";
	out << _tab(1) << "uint64_t allocSize = " << vpnSet.size() * 4096 << "ULL;\n";
	out << _tab(1)
			<< "gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);\n";
	//out << _tab(1) << "if(gm == NULL) {\n";
	//out << _tab(2) << "fprintf(stderr, \"Cannot allocate memory\\n\");\n";
	//out << _tab(2) << "exit(-1);\n";
	//out << _tab(1) << "}\n";
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
}

string generateCodeHeaderFragment(int indent, const vector<InsMem*> &insList){
	stringstream ss;
	for (InsMem *ins : insList) {
		if (ins->isTop) {
			ss << ins->pat->genHeader(indent);
		}
	}
	//ss << "\n";
	//ss << _tab(1) << "goto block0;\n";
	//ss << "\n";
	return ss.str();
}

void generateCodeFooter(ofstream &out) {
	//out << "block1:\n";
	out << _tab(1) << "free((void*)gm);\n";
	out << _tab(1) << "return 0;\n";
	out << "}\n";
}

void generateCode(const char *fname) {
	cout << "Generating code in: " << fname << "...\n";

	genVpnToPpnMap();

	//open output file
	ofstream out(fname);

	//write headers
	generateCodeHeader(out);

	for(string& s : codeFragments){
		out << replaceVtoPAddr(s);
	}

	//write footer
	generateCodeFooter(out);

}

void generateCodeFragment(int indent, const vector<InsMem*> &insList, const set<InsBlock*> &cfg){
	stringstream ss;
	UINT64 intervalStart = startCntSaved + intervalCnt * interval;
	UINT64 IntervalEnd = intervalStart + startCnt;
	ss << _tab(indent) << "// Interval: " << intervalStart << " - " << IntervalEnd << "\n";
	ss << _tab(indent) << "{\n";
	ss << generateCodeHeaderFragment(indent + 1, insList);

	ss << beginBlock->printCodeBody(indent + 1);	//dump begin block

	//write code blocks
	for (InsBlock *blk : cfg) {
		if ((blk != beginBlock) && (blk != endBlock)) {   //skip end block. Handled in footer
			ss << blk->printCodeBody(indent + 1);
		}
	}

	ss << endBlock->printCodeBody(indent + 1);
	ss << _tab(indent + 1) << "int dummy;\n";
	ss << _tab(indent) << "}\n\n";
	codeFragments.push_back(ss.str());
}

set<InsBlock*> cfgFromTrace(vector<InsMem*> &trace) {
	set<InsBlock*> topInsBlocks;

	beginBlock = new InsBlock();
	//InsBlock *prev = new InsBlock(0);    //begin block
	InsBlock *prev = beginBlock;
	topInsBlocks.insert(prev);

	for (InsBase *ins : trace) {
		if (ins->isTop) {
			InsBlock *ib = ins->parentBlock;
			if (ib == nullptr) {
				ib = new InsBlock();
				topInsBlocks.insert(ib);
				ins->parentBlock = ib;
				//if (ins->type == InsTypeNormal) {
					ib->ins.push_back(ins);
				//}
			}
			//add ib as the successor of prev
			ib->inEdges.insert(prev);
			prev->outEdges.insert(ib);
			if (prev->outEdgesStack.empty()) {
				//no out edge yet. add.
				prev->outEdgesStack.push_back( { ib, 1 });
			} else if (prev->outEdgesStack.back().first == ib) {
				//same as last one. increment count.
				prev->outEdgesStack.back().second++;
			} else {
				//not same as last one. add.
				prev->outEdgesStack.push_back( { ib, 1 });
			}
			prev = ib;
		}
	}

	//add end block
	endBlock = new InsBlock();
	InsBlock *ib = endBlock;
	topInsBlocks.insert(ib);
	ib->inEdges.insert(prev);
	prev->outEdges.insert(ib);
	prev->outEdgesStack.push_back( { ib, 1 });

	return topInsBlocks;
}

void writeLog(const char *logFile) {
//	cout << "Writing log file..." << endl;
//	ofstream log(logFile);
//	log << "ins,addr,r0w1\n";
//	for (size_t i = 0; i < insTrace.size(); i++) {
//		if (insTrace[i]->type == InsTypeNormal) {
//			InsMem *ins = (InsMem*) (insTrace[i]);
//			if (ins->isTop) {
//				ADDRINT ea = ins->addr[ins->cnt];
//				ins->cnt++;
//				log << ins->id << "," << ea << ",";
//				if (ins->accType == AccessTypeRead) {
//					log << "0\n";
//				} else if (ins->accType == AccessTypeWrite) {
//					log << "1\n";
//				}
//			}
//		}
//	}
}


set<InsBlock*> createDCFGfromInstTrace(vector<InsMem*> &trace) {
	//cout << "Creating DCFG from trace..." << endl;
	set<InsBlock*> topInsBlocks = cfgFromTrace(trace);

	//if (log_en) {
	//	writeLog("top_trace.csv");
	//}

	vector<InsMem*>().swap(trace);  //free trace memory
	//cout << "Created initial CFG with " << topInsBlocks.size() << " blocks." << endl;
	printDotFile("dcfgBC.gv");

	compressCFG(topInsBlocks);
	//printDotFile("dcfgLC.gv");
	//cout << "Compressed CFG with " << topInsBlocks.size() << " blocks." << endl;

	return topInsBlocks;
}


set<InsBlock*> createDCFGfromDCFGFile() {
	unordered_map<UINT64, InsBlock*> topInsBlocksMap;
	beginBlock = new InsBlock();
	endBlock = new InsBlock();

	DCFG_ID_VECTOR bblids, edge_ids, temp_ids;
	dcfgProcInfo->get_basic_block_ids(bblids);
	topInsBlocksMap[3] = new InsBlock();
	for (DCFG_ID id: bblids) {
		topInsBlocksMap[id] = new InsBlock();
		// DCFG_BASIC_BLOCK_CPTR bbl = dcfgProcInfo->get_basic_block_info(id);
	}

	dcfgProcInfo->get_internal_edge_ids(edge_ids);
	temp_ids.clear();
	dcfgProcInfo->get_inbound_edge_ids(temp_ids);
	edge_ids.insert(edge_ids.end(), temp_ids.begin(), temp_ids.end());
	temp_ids.clear();
	dcfgProcInfo->get_outbound_edge_ids(temp_ids);
	edge_ids.insert(edge_ids.end(), temp_ids.begin(), temp_ids.end());

	DCFG_ID begin_id = dcfgProcInfo->get_start_node_id();
	DCFG_ID end_id = dcfgProcInfo->get_end_node_id();

	for (DCFG_ID id: edge_ids) {
		DCFG_EDGE_CPTR e = dcfgProcInfo->get_edge_info(id);
		DCFG_ID src = e->get_source_node_id();
		DCFG_ID dst = e->get_target_node_id();
		
		UINT64 cnt = e->get_exec_count_for_thread(dcfgProcInfo->get_process_id());
		cout << src << " " << dst << " " << cnt << endl;
		InsBlock *src_block = (src == begin_id ? beginBlock : topInsBlocksMap[src]);
		InsBlock *dst_block = (dst == end_id ? endBlock : topInsBlocksMap[dst]);
		src_block->outEdges.insert(dst_block);
		src_block->outEdgesStack.push_back({dst_block, cnt});
		dst_block->inEdges.insert(src_block);
	}

	set<InsBlock*> topInsBlocks;
	for (auto it : topInsBlocksMap) {
		topInsBlocks.insert(it.second);
	}
	return topInsBlocks;
}

void printInfo(vector<InsMem*> &res) {
	//sort using total accessed size
	//sort(res.begin(), res.end(), [](const InsMem *lhs, const InsMem *rhs) {
	//	return lhs->patInfo->totalSz > rhs->patInfo->totalSz;
	//});

	/*  ft_table_t *table = ft_create_table();
	 ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

	 ft_write_ln(table, "N", "Driver", "Time", "Avg Speed");

	 cout << ft_to_string(table);
	 ft_destroy_table(table);*/

	//int cnt = 0;
	for (InsMem *i : res) {
		cout << "  " << setw(12) << dec << i->id << " ";
		if (i->accType == AccessType::AccessTypeRead) {
			cout << "READ  : " << i->accSz;
		} else if (i->accType == AccessType::AccessTypeWrite) {
			cout << "WRITE : " << i->accSz;
		} else if (i->accType == AccessType::AccessTypeRMW) {
			cout << "RMW   : " << i->accSz;
		} else {
			cout << "INVALID: ";
		}
		//cout << setw(40) << i->hashedRoot->root->dis;

		cout << setw(20) << "TotalSz: " << i->totalSz;
		cout << setw(20) << i->pat->printPattern();
		cout << setw(10) << "[" << setw(10) << i->minAddr << " : " << setw(10)
				<< i->maxAddr << "]   ";
		//cout << setw(10);
		int pCnt = 0;
		for (auto s : i->strideDist) {
			if (pCnt++ == 6)
				break;
			cout << "{" << s.first << ":" << s.second << "} ";
		}
		auto idx = i->hashedRoot->root->srcFile.find_last_of('/');
		string srcFile;
		if (idx == string::npos) {
			srcFile = i->hashedRoot->root->srcFile;
		} else {
			srcFile = i->hashedRoot->root->srcFile.substr(idx + 1);
		}
		cout << "\t" << srcFile << ":" << i->hashedRoot->root->srcLine << "\t\t"
				<< i->addr.size() << "\t";
		/*InsLoopBase* lp = i->parentLoop;
		 //InsLoop* ol = nullptr;
		 while(lp){
		 //ol = lp;
		 cout << lp->iters << ",";
		 lp = lp->parentLoop;
		 }*/

		cout << dec << endl;
		//cnt++;
		//if(cnt == 100){		//only print first 100 instructions
		//	break;
		//}
	}
}

UINT64 getTotalAccessSz(const vector<InsMem*> &insList) {
	UINT64 sz = 0;
	for (InsMem *it : insList) {
		sz += it->totalSz;
	}
	return sz;
}

vector<InsMem*> keepTop(vector<InsMem*> &insList, double perc) {
	UINT64 sz = getTotalAccessSz(insList);
	//cout << "Before pruning. NumInst: " << insList.size() << "\t\tAccessSz: "
	//		<< sz << endl;
	UINT64 szAfter = sz * perc / 100.0;

	//sort using total accessed size
	sort(insList.begin(), insList.end(),
			[](const InsMem *lhs, const InsMem *rhs) {
				return lhs->totalSz > rhs->totalSz;
			});

	vector<InsMem*> out;
	sz = 0;
	for (InsMem *it : insList) {
		it->isTop = true;
		out.push_back(it);
		sz += it->totalSz;
		if (sz > szAfter)
			break;
	}

	//cout << "After pruning. NumInst: " << out.size() << "\t\tAccessSz: "
	//		<< getTotalAccessSz(out) << endl;
	return out;
}

vector<InsMem*> deleteConstAccess2(const vector<InsMem*> &insList) {
	vector<InsMem*> out;
	for (InsMem *it : insList) {
		ADDRINT lastAddr = 0;
		UINT64 zeroCnt = 0;
		for (ADDRINT addr : it->addr) {
			if (lastAddr - addr == 0) {
				zeroCnt++;
			}
			lastAddr = addr;
		}

		//consider only if less than 20% is zero stride access
		if (zeroCnt < it->addr.size() * 0.2) {
			it->totalSz = it->addr.size() * it->accSz;
			out.push_back(it);
		} else {
			vector<ADDRINT>().swap(it->addr);
		}
	}
	return out;
}

vector<InsMem*> deleteZeroAccesses(const vector<InsMem*> &insList) {
	vector<InsMem*> out;
	for (InsMem *ins : insList) {
		if (ins->totalSz >= MIN_SZ) {
			out.push_back(ins);
		} else {
			vector<ADDRINT>().swap(ins->addr);
		}
	}
	return out;
}

void shiftAddressSpace(InsMem *ins, INT64 offset) {
	/*PatternInfo *pat = ins->patInfo;
	 pat->addrRange.s += offset;
	 pat->addrRange.e += offset;
	 const UINT64 cnt = pat->addr.size();
	 for (UINT64 i = 0; i < cnt; i++) {
	 pat->addr[i] += offset;
	 }
	 //pat->pat->shiftAddress(offset);
	 for (auto &it : pat->strideAddr) {
	 for (ADDRINT ea : it.second) {
	 it.second.erase(ea);
	 it.second.insert(ea + offset);
	 }
	 }
	 map<ADDRINT, set<INT64>> nm;
	 for (auto &it : pat->addrStrideMap) {
	 nm[it.first + offset] = it.second;
	 }
	 pat->addrStrideMap = nm;*/
}

void derivePatternInitial(const vector<InsMem*> &insList) {
	/*for (InsMem *it : insList) {
	 PatternInfo *pat = it->patInfo;
	 //bool isRandom = false;
	 pat->totalSz = pat->addr.size() * it->accSz;
	 ADDRINT min = 0xFFFFFFFFFFFFFFFFULL;
	 ADDRINT max = 0;
	 UINT64 cnt = pat->addr.size();
	 INT64 lastStride = 0xDEADBEEF;
	 for (UINT64 i = 0; i < (cnt - 1); i++) {
	 ADDRINT currAddr = pat->addr[i];
	 ADDRINT nextAddr = pat->addr[i + 1];

	 if (currAddr > max) {
	 max = currAddr;
	 }
	 if (currAddr < min) {
	 min = currAddr;
	 }

	 //if(isRandom == false){
	 INT64 stride = nextAddr - currAddr;
	 pat->strideDist[stride]++;
	 if (stride != lastStride) {
	 //stride change point!
	 pat->strideAddr[stride].insert(currAddr);
	 pat->strideRef[stride].insert(i);
	 pat->addrStrideMap[currAddr].insert(stride);
	 //if(pat->strideAddr.size() > MAX_STRIDE_BUCKETS){
	 //  isRandom = true;
	 //}
	 }
	 lastStride = stride;
	 //}
	 }
	 ADDRINT lastAddr = pat->addr[cnt - 1];
	 if (lastAddr > max) {
	 max = lastAddr;
	 }
	 if (lastAddr < min) {
	 min = lastAddr;
	 }
	 pat->addrRange.s = min;
	 pat->addrRange.e = max + it->accSz;

	 //only go further if pattern type is not random
	 //if(isRandom){
	 //create random
	 //  it->patInfo->pat = PatternRandom::create(it);
	 //  continue;
	 //}

	 //check if constant/zero stride access
	 if ((it->patInfo->pat = PatternConst::create(it))) {
	 continue;
	 }
	 }*/
}






void updateAddrInfo(vector<InsMem*> &insList) {
	for (InsMem *it : insList) {
		for (UINT64 addr : it->addr) {
			vpnSet.insert(getPageNum(addr));
		}
	}

	//cout << "\tUpdate addr..." << endl;
	for (InsMem *it : insList) {
		it->addrStrideMap.clear();
		it->strideDist.clear();
		assert(it->maxAddr > it->minAddr);
		it->maxAddr += it->accSz;

		UINT64 cnt = it->addr.size();
		INT64 lastStride = 0xDEADBEEF;
		//bool isRandom = false;
		bool isValidAddrMap = true;
		for (UINT64 i = 0; i < (cnt - 1); i++) {
			//if(isRandom == false){
			ADDRINT currAddr = it->addr[i];
			ADDRINT nextAddr = it->addr[i + 1];

			INT64 stride = nextAddr - currAddr;
			it->strideDist[stride]++;
			//if(it->strideDist.size() > 30){
			//  isRandom = true;
			//}
			if (stride != lastStride && isValidAddrMap) {
				//stride change point!
				auto iter = it->addrStrideMap.find(currAddr);
				if (iter == it->addrStrideMap.end()) {
					//not found, insert
					it->addrStrideMap[currAddr] = nextAddr;
				} else if (iter->second != nextAddr) {
					//found, but different stride. Invalidate...
					iter->second = 0xDEADBEAF;
					isValidAddrMap = false;
				}
				if (it->addrStrideMap.size() > MAX_SMALL_TILES) {
					isValidAddrMap = false;
				}
			}
			lastStride = stride;
			//}
		}
		//if(isRandom){
		//  it->pat = PatternRandom::create(it);
		//}
	}


//	//cout << "Updating address related info..." << endl;
//
//	//cout << "\tBuild VPN list..." << endl;
//	set<UINT64> vpnSet;
//	for (InsMem *it : insList) {
//		for (UINT64 addr : it->addr) {
//			UINT64 vpn = addr & 0xFFFFFFFFFFFFF000ULL;
//			vpnSet.insert(vpn);
//		}
//	}
//
//	//cout << "\tTotal VPN count: " << vpnSet.size() << endl;
//	if(vpnSet.size() * 4096ULL > globalMaxAddr){
//		globalMaxAddr = vpnSet.size() * 4096ULL;
//	}
//	//cout << "\tGlobal max address (or memory footprint): " << globalMaxAddr << endl;
//
//	map<UINT64, UINT64> vpnMap;
//	uint64_t ppn = 0;
//	for (UINT64 vpn : vpnSet) {
//		vpnMap[vpn] = (ppn << 12);
//		//cout << vpn << " : " << ppn << "\n";
//		ppn++;
//	}
//
//	//cout << "\tUpdate addr..." << endl;
//	for (InsMem *it : insList) {
//		assert(it->maxAddr > it->minAddr);
//		it->minAddr = vpnMap[it->minAddr & 0xFFFFFFFFFFFFF000ULL]
//				| (it->minAddr & 0xFFFULL);
//		it->maxAddr = vpnMap[it->maxAddr & 0xFFFFFFFFFFFFF000ULL]
//				| (it->maxAddr & 0xFFFULL);
//		it->maxAddr += it->accSz;
//		assert(it->maxAddr > it->minAddr);
//
//		UINT64 cnt = it->addr.size();
//		INT64 lastStride = 0xDEADBEEF;
//		//bool isRandom = false;
//		bool isValidAddrMap = true;
//		it->addr[0] = vpnMap[it->addr[0] & 0xFFFFFFFFFFFFF000ULL]
//				| (it->addr[0] & 0xFFFULL);
//		for (UINT64 i = 0; i < (cnt - 1); i++) {
//			it->addr[i + 1] = vpnMap[it->addr[i + 1] & 0xFFFFFFFFFFFFF000ULL]
//					| (it->addr[i + 1] & 0xFFFULL);
//			//if(isRandom == false){
//			ADDRINT currAddr = it->addr[i];
//			ADDRINT nextAddr = it->addr[i + 1];
//
//			INT64 stride = nextAddr - currAddr;
//			it->strideDist[stride]++;
//			//if(it->strideDist.size() > 30){
//			//  isRandom = true;
//			//}
//			if (stride != lastStride && isValidAddrMap) {
//				//stride change point!
//				auto iter = it->addrStrideMap.find(currAddr);
//				if (iter == it->addrStrideMap.end()) {
//					//not found, insert
//					it->addrStrideMap[currAddr] = stride;
//				} else if (iter->second != stride) {
//					//found, but different stride. Invalidate...
//					iter->second = 0xDEADBEAF;
//					isValidAddrMap = false;
//				}
//				if (it->addrStrideMap.size() > MAX_SMALL_TILES) {
//					isValidAddrMap = false;
//				}
//			}
//			lastStride = stride;
//			//}
//		}
//		//if(isRandom){
//		//  it->pat = PatternRandom::create(it);
//		//}
//	}
}

void derivePattern(const vector<InsMem*> &insList) {
	for (InsMem *it : insList) {
		//check if already assigned a pattern
		if (it->pat) {
			continue;
		}

		//check for repeats in loops
		deriveLoopInfo(it);

		//check if loop indexed
		if ((it->pat = PatternLoopIndexed::create(it))) {
			continue;
		}

		//check if small tiled access
		if ((it->pat = PatternSmallTile::create(it))) {
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
		if ((it->pat = PatternDominant::create(it))) {
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
		//it->patInfo->pat = PatternInvalid::create(it);

		//nothing matches, assign random
		it->pat = PatternRandom::create(it);
	}
}

ADDRINT getMask(ADDRINT addr) {
	ADDRINT cnt = 0;
	while (!(addr & 1) && (cnt < 12)) {
		cnt++;
		addr = (addr >> 1);
	}
	return ~((1ULL << cnt) - 1);
}

vector<InsMem*> markTopAndProcessInfo(const vector<InsMem*> &insList) {
	vector<InsMem*> out;
	for (InsMem *it : insList) {
		//it->maxAddr += it->accSz;
		//if((it->maxAddr - it->minAddr) > MAX_ADDRESS_RANGE){
		//  cerr << "[WARN] dropping inst for going over range" << endl;
		//}
		//else{
		it->isTop = true;
		out.push_back(it);
		//}
	}
	return out;
}

void printMaxEdgeStack(const set<InsBlock*> &cfg) {
	uint64_t maxEdgeStack = 0;
	uint64_t maxOutBlocks = 0;
	for (InsBlock *blk : cfg) {
		if (blk->outEdges.size() > maxOutBlocks) {
			maxOutBlocks = blk->outEdges.size();
		}
		if (blk->outEdgesStack.size() > maxEdgeStack) {
			maxEdgeStack = blk->outEdgesStack.size();
		}
	}
	cout << "Max edge stack size: " << maxEdgeStack << endl;
	cout << "Max outgoing blocks: " << maxOutBlocks << endl;
}

/*void printStrideAddr(const vector<InsMem*> &insList, UINT64 id) {
 cout << "Printing Stride Address for " << id << endl;
 for (InsMem *ins : insList) {
 if (ins->id == id) {
 PatternInfo *pat = ins->patInfo;
 for (auto &it : pat->strideAddr) {
 cout << setw(10) << it.first << ": ";
 for (ADDRINT addr : it.second) {
 cout << addr << ", ";
 }
 cout << endl;
 }
 return;
 }
 }
 }*/

/*void printStrideRef(const vector<InsMem*> &insList, UINT64 id) {
 cout << "Printing Stride Refs for " << id << endl;
 for (InsMem *ins : insList) {
 if (ins->id == id) {
 PatternInfo *pat = ins->patInfo;
 for (auto &it : pat->strideRef) {
 cout << setw(10) << it.first << ": ";
 for (ADDRINT addr : it.second) {
 cout << addr << ", ";
 }
 cout << endl;
 }
 return;
 }
 }
 }*/

void replaceRand(vector<InsBase*> &insList) {
	int state = 0;
	vector<InsMem*> tmp;
	for (size_t i = 0; i < insList.size(); i++) {
		if (insList[i]->type == InsTypeSingleLoop) {
			InsLoop *ins = (InsLoop*) insList[i];
			replaceRand(ins->ins);
		} else if (insList[i]->type == InsTypeNormal) {
			InsMem *ins = (InsMem*) insList[i];
			if (ins->pat->type == PatTypeSmallTile) {
				if ((ins->maxAddr - ins->minAddr) == 124) {
					state++;
					tmp.push_back(ins);
					if (state == 3) {
						state = 0;
						tmp.clear();
						//found a rand
						for (InsMem *mm : tmp) {
							mm->isTop = false;
						}
						insList[i] = new InsRand(ins->id + 1);
					}
					continue;
				}
			}
		}
		state = 0;
	}
}

void detectRandFunction() {
	for (InsBlock *blk : InsBlock::blockList) {
		if (blk->isUsed) {
			replaceRand(blk->ins);
		}
	}
}



void update_pat_dist(vector<InsMem*> &insList) {
	for (InsMem *ins : insList) {
		if ((ins->pat->type == PatType::PatLoopIndexed)
				|| (ins->pat->type == PatType::PatTypeSmallTile)) {
			instStatLoopedIndex++;
			instDynLoopedIndex += ins->addr.size();
		} else if (ins->pat->type == PatType::PatTypeDominant) {
			instStatDom++;
			instDynDom += ins->addr.size();
		} else if (ins->pat->type == PatType::PatTypeRandom) {
			instStatRandom++;
			instDynRandom += ins->addr.size();
		} else {
			cout << "[ERROR] unknown pattern" << endl;
			exit(-1);
		}
	}
}

void print_pat_dist() {
	cout << "Dynamic Inst: #dom: " << instDynDom << endl;
	cout << "Dynamic Inst: #rand: " << instDynRandom << endl;
	cout << "Dynamic Inst: #loopedIndex: " << instDynLoopedIndex << endl;
	//cout << "Static #dom: " << instStatDom << endl;
	//cout << "Static #rand: " << instStatRandom << endl;
	//cout << "Static #loopedIndex: " << instStatLoopedIndex << endl;

	cloneLog << "Dynamic Inst: #dom: " << instDynDom << endl;
	cloneLog << "Dynamic Inst: #rand: " << instDynRandom << endl;
	cloneLog << "Dynamic Inst: #loopedIndex: " << instDynLoopedIndex << endl;
}

void print_edge_dist() {
	cout << "Dynamic Edge: #direct: " << edgeDynDirect << endl;
	cout << "Dynamic Edge: #ordered: " << edgeDynOrdered << endl;
	cout << "Dynamic Edge: #random: " << edgeDynRandom << endl;
	//cout << "Static #direct: " << edgeStatDirect << endl;
	//cout << "Static #ordered: " << edgeStatOrdered << endl;
	//cout << "Static #random: " << edgeStatRandom << endl;

	cloneLog << "Dynamic Edge: #direct: " << edgeDynDirect << endl;
	cloneLog << "Dynamic Edge: #ordered: " << edgeDynOrdered << endl;
	cloneLog << "Dynamic Edge: #random: " << edgeDynRandom << endl;
}

void update_filtering_info(const vector<InsMem*> &insList, bool top, FilterInfo &fInfo) {
	for (InsMem *ins : insList) {
		if (ins->isTop == top) {
			fInfo.totMemUsage += ins->totalSz;
			fInfo.dynMemInst += ins->addr.size();
			fInfo.statMemInst.insert(ins);
		}
	}
}


void print_filtering_info(const FilterInfo &fInfo, string msg) {
	cout << msg << endl;
	cout << "\tDynamic memory instructions: " << fInfo.dynMemInst << endl;
	cout << "\tStatic memory instructions: " << fInfo.statMemInst.size() << endl;
	cout << "\tMemory access size: " << fInfo.totMemUsage << endl;

	cloneLog << msg << endl;
	cloneLog << "\tDynamic memory instructions: " << fInfo.dynMemInst << endl;
	cloneLog << "\tStatic memory instructions: " << fInfo.statMemInst.size() << endl;
	cloneLog << "\tMemory access size: " << fInfo.totMemUsage << endl;
}


void processInterval() {
	UINT64 intervalStart = startCntSaved + intervalCnt * interval;
	UINT64 IntervalEnd = intervalStart + startCnt;
	cout << "Interval: " << intervalStart << " - " << IntervalEnd << "\n";
	// 0. Filter zero  (or very low) cnt instructions
	vector<InsMem*> filteredInsList;
	for (InsBase *it : InsBase::insList) {
		if (it->type == InsTypeNormal) {
			InsMem *ins = static_cast<InsMem*>(it);
			if(ins->addr.size()){		//delete zero accesses
				ins->totalSz = ins->accSz * ins->addr.size();
				filteredInsList.push_back(ins);
			}
		}
	}
	//print_filtering(filteredInsList, "Before filtering...", false);
	update_filtering_info(filteredInsList, false, fInfoOrig);
	filteredInsList = deleteZeroAccesses(filteredInsList);

	// 1. filter constant access instructions
	filteredInsList = deleteConstAccess2(filteredInsList);

	//print_filtering(filteredInsList, "After const access filtering...", false);
	update_filtering_info(filteredInsList, false, fInfoAfterZero);

	// 2. Only take instructions that represents top_perc of reads/writes
	filteredInsList = keepTop(filteredInsList, top_perc);

	//cout << "Static memory instructions: top " << filteredInsList.size() << endl;
	//filteredInsList = markTopAndProcessInfo(filteredInsList);

	//print_filtering(filteredInsList, "After filtering...", true);
	update_filtering_info(filteredInsList, true, fInfoTop);

	updateAddrInfo(filteredInsList);

	//cout << "Inst Trace size: " << insTrace.size() << endl;
	// set<InsBlock*> cfg = createDCFGfromInstTrace(insTrace);
	
	// updateParentLoops(cfg);
	// derivePattern(filteredInsList);

	// printInfo(filteredInsList);
	generateCodeFragment(1, filteredInsList, DCFG);
	//cout << "Process Done" << endl;
	// update_pat_dist(filteredInsList);
}

void resetState() {
	for(InsBase* it : InsBase::insList){
		if(it->type == InsType::InsTypeNormal){
			InsMem *ins = static_cast<InsMem*>(it);
			ins->reset();
		}
		else if(it->type != InsType::InsTypeSingleLoop){
			cout << "WRONG TYPE" << endl;
		}
	}
	InsBlock::deleteAll();
	insTrace.clear();
	//cout << "Reset Done" << endl;
}

bool reloadDcfgTraceBuffer() {
	string msg;
	dcfgTraceBuffer.clear();
	if (!dcfg_trace_done) {
		if (!dcfgTraceReader->get_edge_ids(dcfgTraceBuffer, dcfg_trace_done, msg)) {
			cerr << " error: " << msg << endl;
			dcfg_trace_done = true;
			return false;
		}
		dcfgTraceBufferPtr = dcfgTraceBuffer.begin();
		return true;
	}
	return false;
}

UINT64 getDcfgEdgeAddress(DCFG_ID_VECTOR::iterator &edgePtr) {
	DCFG_EDGE_CPTR edge = dcfgProcInfo->get_edge_info(*edgePtr);
	if (!edge) {
		cerr << "error: invalid edge" << endl;
		return 0; 
	}
	DCFG_ID bbId = edge->get_target_node_id();
	DCFG_BASIC_BLOCK_CPTR bb = dcfgProcInfo->get_basic_block_info(bbId);
	
	if (!bb) return 0;
	// if (edge->is_exit_edge_type()) {
	// 	dcfg_output << bbId << " " << (void *)bb->get_first_instr_addr() << ",end" << endl;
	// 	return 0;
	// }
	return bb->get_first_instr_addr();
}

VOID Fini(INT32 code, VOID *v) {
	cout << "Entered FINI" << endl;
	processInterval();

	DCFG_DATA_CPTR data = dcfgMgr->get_dcfg_data();
	string msg;
	data->write("output.txt", msg);


	// for (; dcfgTraceBufferPtr != dcfgTraceBuffer.end(); ++dcfgTraceBufferPtr) {
	// 	shadow_output << (void *)getDcfgEdgeAddress(dcfgTraceBufferPtr) << endl;
	// }
	// while (!dcfg_trace_done) {
	// 	reloadDcfgTraceBuffer();
	// 	for (; dcfgTraceBufferPtr != dcfgTraceBuffer.end(); ++dcfgTraceBufferPtr) {
	// 		shadow_output << (void *)getDcfgEdgeAddress(dcfgTraceBufferPtr) << endl;
	// 	}
	// }

	generateCode(out_file_name.c_str());

	for (InsRoot *it : insRootList) {
		delete it;
	}
	for (InsHashedRoot *it : insHashedRootList) {
		delete it;
	}
	InsBlock::deleteAll();
	InsBase::deleteAll();

	cloneLog.open(stat_file_name.c_str());
	print_pat_dist();
	print_edge_dist();
	print_filtering_info(fInfoOrig, "Filter info orig...");
	print_filtering_info(fInfoAfterZero, "Filter info after zero stride filtering...");
	print_filtering_info(fInfoTop, "Filter info of top...");


	cout << "DONE" << endl;
	cout << "Total instructions executed: " << instCount << endl;

	cloneLog << "Total instructions executed: " << instCount << endl;

	cloneLog.close();
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
			for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn);
					rtn = RTN_Next(rtn)) {
				string name = PIN_UndecorateSymbolName(RTN_Name(rtn),
						UNDECORATION_NAME_ONLY);
				// add suffix for openmp functions
				string rtn_name_omp = rtn_name + "._omp_fn.";

				// Try exact name match
				if ((name == rtn_name)
						|| (name.find(rtn_name_omp) != string::npos)) {
					// Match found!
					match_count++;
					cout << "    Tagged function \"" << name << "\"" << endl;

					// Instrument function entry and exit
					RTN_Open(rtn);
					RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) RtnEntry,
							IARG_THREAD_ID, IARG_END);
					RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) RtnLeave,
							IARG_THREAD_ID, IARG_END);
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
			for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn);
					rtn = RTN_Next(rtn)) {
				string name = PIN_UndecorateSymbolName(RTN_Name(rtn),
						UNDECORATION_NAME_ONLY);

				// Check if the current routine contains the requested routine name
				if (name.find(rtn_name) != string::npos) {
					// Match found!
					match_count++;
					cout << "    Tagged function \"" << name << "\"" << endl;

					// Instrument function entry and exit
					RTN_Open(rtn);
					RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR) RtnEntry,
							IARG_THREAD_ID, IARG_END);
					RTN_InsertCall(rtn, IPOINT_AFTER, (AFUNPTR) RtnLeave,
							IARG_THREAD_ID, IARG_END);
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
VOID anyCallEntry(ADDRINT ptr) {
	callStack.push(ptr);
	callHash ^= ptr;
}

VOID anyCallRet() {
	ADDRINT lastAddr = callStack.top();
	callHash ^= lastAddr;
	callStack.pop();
}

InsMem* getInsLeaf(InsRoot *root, UINT32 op) {
	if (root->childMap.find(callHash) == root->childMap.end()) {
		//create new hashed map
		InsHashedRoot *tmp = new InsHashedRoot();
		insHashedRootList.push_back(tmp);
		tmp->root = root;
		root->childMap[callHash] = tmp;
		tmp->id = root->id * 1000 + root->childMap.size();
		for (UINT32 i = 0; i < root->opCnt; i++) {
			InsMem *ins = new InsMem(tmp->id * 100 + i + 1);
			ins->accSz = root->opInfo[i].accSz;
			ins->accType = root->opInfo[i].accType;
			ins->hashedRoot = tmp;
			tmp->children.push_back(ins);
		}
	}
	InsHashedRoot *hrt = root->childMap[callHash];
	return hrt->children[op];
}

void record(InsRoot *root, ADDRINT ea, UINT32 op) {
	if (rtnEntryCnt <= 0)
		return;
	startCnt++;
	if (startCnt > 0) {
		InsMem *ins = getInsLeaf(root, op);
		/*if(ea & (ins->accSz-1)){
			cout << "Unaligned access" << endl;
			cout << "\t" << ins->hashedRoot->root->dis << endl;
			cout << "\tSize: " << ins->accSz << endl;
			cout << "\tAddr: " << hex << ea << dec << endl;
			exit(-1);
		}*/
		insTrace.push_back(ins);
		//make the address aligned
		ea &= ~(ins->accSz - 1ULL);
		if (ea > ins->maxAddr) {
			ins->maxAddr = ea;
		}
		if (ea < ins->minAddr) {
			ins->minAddr = ea;
		}
		ins->addr.push_back(ea);
		if (__builtin_expect(startCnt == interval, 0)) {
			processInterval();
			resetState();
			startCnt = 0;
			intervalCnt++;
		}
	}
}

InsRoot* createInsRoot(INS &ins, UINT64 bblid) {
	static UINT64 rootId = 0;
	static unordered_map<ADDRINT, InsRoot*> processedIns; //set of already processed instructions

	ADDRINT addr = INS_Address(ins);
	// check if already processed or not
	auto it = processedIns.find(addr);
	if (it != processedIns.end()) {
		return it->second;   //already processed
	}

	InsRoot *root = new InsRoot();
	root->id = rootId++;
	root->bblid = bblid;
	PIN_GetSourceLocation(addr, NULL, &root->srcLine, &root->srcFile);
	root->dis = INS_Disassemble(ins);
	root->opCnt = INS_MemoryOperandCount(ins);
	for (UINT32 i = 0; i < root->opCnt; i++) {
		OpInfo info;
		info.accSz = INS_MemoryOperandSize(ins, i);
		if (INS_MemoryOperandIsRead(ins, i)
				&& !INS_MemoryOperandIsWritten(ins, i)) {
			info.accType = AccessType::AccessTypeRead;
		} else if (!INS_MemoryOperandIsRead(ins, i)
				&& INS_MemoryOperandIsWritten(ins, i)) {
			info.accType = AccessType::AccessTypeWrite;
		} else if (INS_MemoryOperandIsRead(ins, i)
				&& INS_MemoryOperandIsWritten(ins, i)) {
			info.accType = AccessType::AccessTypeRMW;
		} else {
			info.accType = AccessType::AccessTypeInvalid;
		}

		root->opInfo.push_back(info);
	}

	insRootList.push_back(root);
	processedIns[addr] = root;
	return root;
}

/*InsBase* getJmpInsLeaf(InsRoot *root) {
	if (root->childMap.find(callHash) == root->childMap.end()) {
		//create new hashed map
		InsHashedRoot *tmp = new InsHashedRoot();
		insHashedRootList.push_back(tmp);
		tmp->root = root;
		root->childMap[callHash] = tmp;
		tmp->id = root->id * 1000 + root->childMap.size();

		//create InsCondJump
		InsCondJump *ins = new InsCondJump(tmp->id);
		tmp->onlyChild = ins;
	}
	InsHashedRoot *hrt = root->childMap[callHash];
	return hrt->onlyChild;
}

void jmpInst(InsRoot *root) {
	if (rtnEntryCnt <= 0)
		return;
	InsBase *ins = getJmpInsLeaf(root);
	insTrace.push_back(ins);
}*/

void inst_count(){
	instCount++;
	if(instCount == MAX_INST){
		PIN_ExitApplication(0);
	}
}

void inst_mix_count(InsMix::InsMixType ty) {
	insMixCnt.cnt[ty] += 1;
}

// VOID shadow_outfunc(ADDRINT addr) {
// 	shadow_output << "outfunc " << (void*) addr << endl;
// 	while (true) {
// 		if (dcfgTraceBufferPtr == dcfgTraceBuffer.end()) {
// 			if (!reloadDcfgTraceBuffer()) {
// 				shadow_cnt++;
// 				shadow_output << string(19, ' ') << (void *) addr << " " << shadow_cnt << "/" << dcfg_cnt << endl;
// 			}
// 			break;
// 		}
		
// 		UINT64 dcfg_addr = getDcfgEdgeAddress(dcfgTraceBufferPtr);
// 		if ((addr & 0xffff) == 0xbac0) {
// 			shadow_output << "wowow " << (void *)addr << ' ' << (void *)dcfg_addr << endl;
// 		}
		
// 		if ((dcfg_addr & 0xfff) == (addr & 0xfff)) {
// 			dcfg_cnt++;
// 			shadow_cnt++;
// 			shadow_output << (void *) dcfg_addr << " " << (void *) addr << (dcfg_addr == addr ? "" : " diff") << " " << shadow_cnt << "/" << dcfg_cnt << endl;
// 			++dcfgTraceBufferPtr;
// 			break;
// 		}
// 		else {
// 			dcfg_cnt++;
// 			shadow_output << (void *) dcfg_addr << " " << shadow_cnt << "/" << dcfg_cnt << " curaddr=" << (void*)addr << endl;
// 			++dcfgTraceBufferPtr;
// 		}
// 	}

// 	DCFG_DATA_CPTR data = dcfgMgr->get_dcfg_data();
// 	DCFG_ID_VECTOR process_ids;
// 	int process_count = data->get_process_ids(process_ids);
// 	assert(process_count >= 1);
// 	DCFG_PROCESS_CPTR proc_info = data->get_process_info(process_ids[0]);
// }


VOID Trace(TRACE trace, VOID *v) {
	// acquire BBL ID in DCFG, then mark each instruction with that ID
	for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
		DCFG_ID_VECTOR bblids;
		dcfgProcInfo->get_basic_block_ids_by_addr(BBL_Address(bbl), bblids);
		UINT64 bblid = BBL_INVALID;
		if (bblids.size() > 0) {
			bblid = bblids[0];
		}
		for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins)) {
			INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) inst_count, IARG_END);

			// do some filtering

			// Get the memory operand count of the current instruction.
			UINT32 memOperands = INS_MemoryOperandCount(ins);

			if (memOperands && INS_IsMov(ins)) {
				InsRoot *root = createInsRoot(ins, bblid);
				for (UINT32 memOp = 0; memOp < memOperands; memOp++) {
					const int accSz = INS_MemoryOperandSize(ins, memOp);
					if((accSz == 1) || (accSz == 2) || (accSz == 4) || (accSz == 8) || (accSz == 16) || (accSz == 32) || (accSz == 64)){
						INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record,
								IARG_PTR, root, IARG_MEMORYOP_EA, memOp, IARG_UINT32, memOp,
								IARG_END);
					}
				}
			}

			if (INS_IsMemoryRead(ins) || INS_HasMemoryRead2(ins)) {
				INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::LOAD, IARG_END);
			}
			if (INS_IsMemoryWrite(ins)) {
				INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::STORE, IARG_END);
			}
			if (INS_IsControlFlow(ins)) { // account for func calls
				INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::CONTROL, IARG_END);
			}
			if (INS_IsBranch(ins)) {
				INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::BRANCH, IARG_END);
			}
			if (INS_IsSyscall(ins)) {
				INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::SYSCALL, IARG_END);
			}

			xed_iclass_enum_t iclass = static_cast<xed_iclass_enum_t>(INS_Opcode(ins));
			if ((INS_Category(ins) == XED_CATEGORY_FCMOV) || (INS_Category(ins) == XED_CATEGORY_X87_ALU) || (INS_Category(ins) == XED_CATEGORY_LOGICAL_FP)) {	
				if ((iclass == XED_ICLASS_FMUL) || (iclass == XED_ICLASS_PFMUL) || (iclass == XED_ICLASS_FMULP)) {
					INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::FPMUL, IARG_END);
				}
				else if ((iclass == XED_ICLASS_FDIV) || (iclass == XED_ICLASS_FDIVR) || (iclass == XED_ICLASS_FDIVRP) || (iclass == XED_ICLASS_FDIVP)) {
					INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::FPDIV, IARG_END);
				}
				else {
					INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::FPOTHER, IARG_END);
				}
			}
			else if ((INS_Category(ins) == XED_CATEGORY_LOGICAL) || (INS_Category(ins) == XED_CATEGORY_BINARY) || (INS_Category(ins) == XED_CATEGORY_BITBYTE) || (INS_Category(ins) == XED_CATEGORY_FLAGOP)) {
				if((iclass == XED_ICLASS_IMUL) || (iclass == XED_ICLASS_MUL) || (iclass == XED_ICLASS_PMULLW) || (iclass == XED_ICLASS_PMULUDQ) || (iclass == XED_ICLASS_PMULHUW) || (iclass == XED_ICLASS_PMULHW) || (iclass == XED_ICLASS_MULPS) || (iclass == XED_ICLASS_MULSS) || (iclass == XED_ICLASS_MULPD) || (iclass == XED_ICLASS_MULSD)) {
					INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::INTMUL, IARG_END);
				}
				else if ((iclass == XED_ICLASS_DIV) || (iclass == XED_ICLASS_IDIV) || (iclass == XED_ICLASS_DIVPS) || (iclass == XED_ICLASS_DIVSS) || (iclass == XED_ICLASS_DIVPD) || (iclass == XED_ICLASS_DIVSD)) {
					INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::INTDIV, IARG_END);
				}
				else {
					INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::INTOTHER, IARG_END);
				}
			}
			else {
				INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(inst_mix_count), IARG_UINT32, InsMix::InsMixType::OTHER, IARG_END);
			}
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
	// PIN_InitLock(&lock);
	PIN_InitSymbolsAlt(IFUNC_SYMBOLS);

	rtn_name = knobFunctionName.Value();
	log_en = knobLogEn.Value();
	top_perc = knobTopPerc.Value();
	out_file_name = knobOutFile.Value();
	stat_file_name = knobStatFile.Value();
	interval = knobInterval.Value();
	MAX_INST = knobMaxInst.Value();
	startCntSaved = knobStart.Value();
	startCnt = 0 - startCntSaved;
	//cout << "Start Ref: " << startCnt << endl;
	cout << "Interval: " << interval << endl;
	cout << "Maxinst: " << (INT64)MAX_INST << endl;


	insRootList.reserve(100000);
	insHashedRootList.reserve(100000);

	if(interval <= 0 || interval > 40000000L){
		insTrace.reserve(40000000L);
	}
	else {
		insTrace.reserve(interval);
	}

	// pinplay_engine.Activate(argc, argv, 
	// 	knobLogEn, KnobPinPlayReplayer);
	// &pinplay_engine

	// dcfg_cfg_file = "dcfg-out.dcfg.json.bz2";
	// dcfg_trace_file = "dcfg-out.trace.json.bz2";
	dcfg_cfg_file = "output.txt";

	shadow_output.open("shadow_output.out", ofstream::out);
	dcfg_output.open("dcfg_output.out", ofstream::out);

	dcfgMgr = DCFG_PIN_MANAGER::new_manager();
	dcfgMgr->set_cfg_collection(true);
	dcfgMgr->activate();


	dcfgData = DCFG_DATA::new_dcfg();
	string msg;
	if (!dcfgData->read(dcfg_cfg_file, msg)) {
		cerr << "error: " << msg << endl;
        return 1;
	}

	DCFG_ID_VECTOR process_ids;
	int process_count = dcfgData->get_process_ids(process_ids);
	assert(process_count >= 1);
	
	dcfgProcInfo = dcfgData->get_process_info(process_ids[0]);

	DCFG = createDCFGfromDCFGFile();
	// dcfgTraceReader = DCFG_TRACE_READER::new_reader(process_ids[0]);
	
	// if (!dcfgTraceReader->open(dcfg_trace_file, 0, msg)) {
    //     cerr << "error: " << msg << endl;
    //     return 1;
    // }

	// dcfgTraceBuffer.clear();
	// dcfgTraceBufferPtr = dcfgTraceBuffer.end();

	IMG_AddInstrumentFunction(ImgCallback, NULL);
	TRACE_AddInstrumentFunction(Trace, NULL);
	PIN_AddFiniFunction(Fini, NULL);

	// Start the program, never returns
	PIN_StartProgram();

	return 0;
}

