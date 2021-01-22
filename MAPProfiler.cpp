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
#include "InsHashedRoot.h"
#include "InsRoot.h"
#include "InsMem.h"
#include "InsCondJump.h"
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
#include "InsRand.h"
#include <unordered_map>

using namespace std;

/*******************************************************************************
 * Knobs for configuring the instrumentation
 ******************************************************************************/
// Name of the function to profile
KNOB<string> knobFunctionName(KNOB_MODE_WRITEONCE, "pintool", "func", "main", "Function to be profiled.");

// Output file name
KNOB<string> knobOutFile(KNOB_MODE_WRITEONCE, "pintool", "out", "genCode.cpp", "Output file name.");

// Enable Log
KNOB<bool> knobLogEn(KNOB_MODE_WRITEONCE, "pintool", "log", "0",
		"Enable logging \
        [1: enable, 0: disable (default)].");

// Keep percentage
KNOB<float> knobTopPerc(KNOB_MODE_WRITEONCE, "pintool", "top", "95", "Top instruction percentage.");

// Max threads
KNOB<UINT64> knobMaxThreads(KNOB_MODE_WRITEONCE, "pintool", "threads", "10000",
		"Upper limit of the number of threads that can be used by the program \
        being profiled.");

/*******************************************************************************
 * Forward declarations
 ******************************************************************************/

//void deriveAccessPattern(const vector<InsNormal*> &insList);
void derivePattern(const vector<InsMem*> &insList);
void shiftAddressSpace(InsMem *ins, INT64 offset);
bool isRepeat(const vector<ADDRINT> &addr, size_t sz, size_t rep, INT64 &m);
void compressCFG(set<InsBlock*> &cfg);
void printDotCFG(ofstream &out, const set<InsBlock*> &cfg);
void printDotFile(const char *fname);

/*******************************************************************************
 * Global variables
 ******************************************************************************/
static string rtn_name;
static PIN_LOCK lock;
static bool log_en = false;
static float top_perc;
static string out_file_name;
static INT64 rtnEntryCnt = 0;

static vector<InsRoot*> insRootList;
static vector<InsHashedRoot*> insHashedRootList;

static vector<PatternInfo*> patternList;

//static vector<InsNormal*> insTrace;   //td
static vector<InsBase*> insTrace;   //td
static vector<ADDRINT> addrTrace;

static stack<ADDRINT> callStack;
static ADDRINT callHash = HASH_INIT_VALUE;

static ADDRINT globalMaxAddr = 0;

static map<UINT64, string> accTypeMap;
static map<UINT64, string> regNameMap;

/*******************************************************************************
 * Pattern Classes
 ******************************************************************************/
bool isRepeat(const vector<ADDRINT> &addr, size_t sz, size_t rep, INT64 &m) {
	if (sz == 0)
		return false;
	if (rep == 0)
		return false;
	if (rep == 1)
		return false;
	if (sz % rep)
		return false;

	size_t elems = sz / rep;
	m = addr[elems] - addr[0];

	for (size_t i = 0; i < elems; i++) {
		ADDRINT ref = addr[i];
		for (size_t j = 1; j < rep; j++) {
			size_t idx = elems * j + i;
			if (addr[idx] != (ref + j * m)) {
				return false;
			}
		}
	}

	return true;
}

void deriveLoopInfo(InsMem *ins) {
	stack<InsLoopBase*> loops;
	InsLoopBase *lp = ins->parentLoop;
	while (lp) {
		loops.push(lp);
		lp = lp->parentLoop;
	}
	if (loops.size() == 0) {
		return; //not inside any loops
	}

	vector<LoopInfo> _info;
	size_t sz = ins->patInfo->addr.size();
	while (loops.size()) {
		lp = loops.top();
		loops.pop();
		INT64 m;
		if (isRepeat(ins->patInfo->addr, sz, lp->iters, m)) {
			sz = sz / lp->iters;
			_info.push_back( { lp, m });
		} else {
			_info.push_back( { nullptr, 0 });
		}
	}

	ins->patInfo->loops = _info;
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

vector<pair<InsBlock*, UINT64> > mergeEdgeStack(vector<pair<InsBlock*, UINT64> > in) {
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

//check if one block creates a loop
bool isSelfLoop(InsBlock *blk) {
	if (blk->outEdges.find(blk) == blk->outEdges.end()) {
		return false;   //does not have any self edge
	}
	if (blk->outEdgesStack.size() == 0) {
		return false; //no out edges
	}

	if (blk->ins.size() == 0) { //jmp block with loop, just remove the edge
		blk->removeOutEdge(blk);
		blk->inEdges.erase(blk);
		return true;
	}

	if (blk->outEdgesStack[0].first != blk) {
		return false; // pattern does not match
	}

	UINT64 loopCnt = blk->outEdgesStack[0].second;

	for (size_t i = 0; i < blk->outEdgesStack.size(); i++) {
		if (i & 1) {    //odd
			//out edge count should be 1 (loop exit)
			if (blk->outEdgesStack[i].second != 1)
				return false;
		} else {         //even
			//should be same block, and same loop count
			if (blk->outEdgesStack[i].first != blk)
				return false;
			if (blk->outEdgesStack[i].second != loopCnt)
				return false;
		}
	}

	loopCnt++;

	// Found a loop
	// 1. Create loop inst
	InsSingleLoop *lp = new InsSingleLoop();
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

	return true;
}

bool isMultiLoop(set<InsBlock*> &cfg, InsBlock *root, InsBlock *a, InsBlock *b) {
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
}

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

bool isCommonLoop(set<InsBlock*> &cfg, InsBlock *blk) {
	if (blk->ins.size()) {
		return false;     //for now, only supports empty origin blocks
	}
	InsBlock *target = nullptr;
	for (InsBlock *t : blk->outEdges) {
		if ((t->inEdges.size() == 1) && (t->outEdges.size() == 1)) {
			if (t->outEdges.find(blk) != t->outEdges.end()) {
				target = t;
				break;
			}
		}
	}
	if (target == nullptr) {
		return false;       //not found
	}

	//potential target found. Check edge stack
	UINT64 loopCnt = blk->outEdgesStack[0].second;

	for (size_t i = 0; i < blk->outEdgesStack.size(); i++) {
		if (i & 1) {    //odd
			//out edge count should be 1 (loop exit)
			if (blk->outEdgesStack[i].second != 1)
				return false;
		} else {         //even
			//should be same block, and same loop count
			if (blk->outEdgesStack[i].first != target)
				return false;
			if (blk->outEdgesStack[i].second != loopCnt)
				return false;
		}
	}

	// Found a loop
	// 1. Create loop inst
	InsSingleLoop *lp = new InsSingleLoop();
	lp->iters = loopCnt;
	lp->ins = target->ins;

	// 2. Fix current block
	blk->removeOutEdge(target);
	blk->inEdges.erase(target);
	blk->ins.push_back(lp); //insert loop instruction

	// 3. Invalidate target block
	cfg.erase(target);
	target->isUsed = false;
	return true;
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
		if (in->getId() == 0)
			continue;   //skip begin block
		if (in->outEdgesStack.size() == 1) {
			InsBlock *out = in->outEdgesStack[0].first;
			if (out->getId() == 1)
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
			continue;                   // Found a self loop, start from beginning
		}
		if (mergeCommonLoop(cfg)) {    // Try to merge a common loop
			continue;
		}
		if (!mergeMultiLoops(cfg)) {    // Last resort, try to merge multi block loops
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

void generateCodeHeader(ofstream &out, const vector<InsMem*> &insList) {
	out << "#include <cstdlib>\n";
	out << "#include <cstdint>\n";
	out << "#include <cstdio>\n";
	out << "#include \"immintrin.h\"\n";
	out << "\n";
	out << "__attribute__((always_inline)) static inline uint64_t bounded_rnd(uint64_t bound) {\n";
	out << _tab(1) << "static uint64_t hash = 0xC32ED012FEA8B4D3ULL;\n";
	out << _tab(1) << "hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);\n";
	out << _tab(1) << "return (hash * (__uint128_t)bound) >> 64;\n";
	out << "}\n";
	out << "\n";
	out << "#define READ_1b(X)  __asm__ __volatile__ (\"movb       (\%1,\%2), \%0\" : \"=r\"(tmp1)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out << "#define READ_2b(X)  __asm__ __volatile__ (\"movw       (\%1,\%2), \%0\" : \"=r\"(tmp2)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out << "#define READ_4b(X)  __asm__ __volatile__ (\"movl       (\%1,\%2), \%0\" : \"=r\"(tmp4)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out << "#define READ_8b(X)  __asm__ __volatile__ (\"movq       (\%1,\%2), \%0\" : \"=r\"(tmp8)  : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define READ_16b(X) __asm__ __volatile__ (\"movdqa     (\%1,\%2), \%0\" : \"=r\"(tmp16) : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define READ_32b(X) __asm__ __volatile__ (\"vmovdqa    (\%1,\%2), \%0\" : \"=r\"(tmp32) : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	//out << "#define READ_64b(X) __asm__ __volatile__ (\"vmovdqa32  (\%1,\%2), \%0\" : \"=r\"(tmp64) : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  out << "#define READ_16b(X) tmp16 = _mm_load_si128((__m128i const*)(gm + (X)))\n";
  out << "#define READ_32b(X) tmp32 = _mm256_load_si256((__m256i const*)(gm + (X)))\n";
  out << "#define READ_64b(X) tmp64 = _mm512_load_si512((__m512i const*)(gm + (X)))\n";
	out << "\n";
	out << "#define WRITE_1b(X)  __asm__ __volatile__ (\"movb      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp1)  : \"memory\")\n";
	out << "#define WRITE_2b(X)  __asm__ __volatile__ (\"movw      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp2)  : \"memory\")\n";
	out << "#define WRITE_4b(X)  __asm__ __volatile__ (\"movl      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp4)  : \"memory\")\n";
	out << "#define WRITE_8b(X)  __asm__ __volatile__ (\"movq      \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp8)  : \"memory\")\n";
	//out << "#define WRITE_16b(X) __asm__ __volatile__ (\"movdqa    \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp16) : \"memory\")\n";
	//out << "#define WRITE_32b(X) __asm__ __volatile__ (\"vmovdqa   \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp32) : \"memory\")\n";
	//out << "#define WRITE_64b(X) __asm__ __volatile__ (\"vmovdqa32 \%2, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X), \"r\"(tmp64) : \"memory\")\n";
  out << "#define WRITE_16b(X) _mm_store_si128((__m128i*)(gm + (X)), tmp16)\n";
  out << "#define WRITE_32b(X) _mm256_store_si256((__m256i*)(gm + (X)), tmp32)\n";
  out << "#define WRITE_64b(X) _mm512_store_si512((__m512i*)(gm + (X)), tmp64)\n";
  out << "\n";
  out << "#define RMW_1b(X)  __asm__ __volatile__ (\"addb $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  out << "#define RMW_2b(X)  __asm__ __volatile__ (\"addw $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  out << "#define RMW_4b(X)  __asm__ __volatile__ (\"addl $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  out << "#define RMW_8b(X)  __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  //out << "#define RMW_16b(X) __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  //out << "#define RMW_32b(X) __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
  //out << "#define RMW_64b(X) __asm__ __volatile__ (\"addq $1, (\%0,\%1)\" : : \"r\"(gm), \"r\"(X) : \"memory\")\n";
	out << "\n";
	out << "volatile uint8_t* gm;\n\n";
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
	for (InsMem *ins : insList) {
		if (ins->isTop) {
			out << ins->patInfo->pat->genHeader(1);
		}
	}
	out << "\n";
	out << _tab(1) << "goto block0;\n";
	out << "\n";
}

bool isRegularSeq(const vector<Interval> &seq) {
	if (seq.size() < 3) {
		return true;
	}

	UINT64 range = seq[0].e - seq[0].s;

	//check if all intervals have same range
	for (const Interval &it : seq) {
		if ((it.e - it.s) != range)
			return false;
	}

	//check if two consecutive intervals have same difference
	UINT64 diff = seq[1].s - seq[0].s;
	for (UINT64 i = 1; i < seq.size(); i++) {
		if ((seq[i].s - seq[i - 1].s) != diff) {
			return false;
		}
	}

	return true;
}

void generateCodeFooter(ofstream &out) {
	out << "block1:\n";
	out << _tab(1) << "free((void*)gm);\n";
	out << _tab(1) << "return 0;\n";
	out << "}\n";
}

void generateCode(const vector<InsMem*> &insList, const set<InsBlock*> &cfg, const char *fname) {
	cout << "Generating code in: " << fname << "...\n";

	//open output file
	ofstream out(fname);

	//write headers
	generateCodeHeader(out, insList);

	//write code blocks
	for (InsBlock *blk : cfg) {
		if (blk->getId() != 1) {   //skip end block. Handled in footer
			out << blk->printCodeBody(1);
		}
	}

	//write footer
	generateCodeFooter(out);

}

set<InsBlock*> cfgFromTrace(vector<InsBase*> &trace) {
	set<InsBlock*> topInsBlocks;

	InsBlock *prev = new InsBlock(0);    //begin block
	topInsBlocks.insert(prev);

	for (InsBase *ins : trace) {
		if(ins->isTop){
			InsBlock* ib = ins->parentBlock;
			if(ib == nullptr){
				ib = new InsBlock();
				topInsBlocks.insert(ib);
				ins->parentBlock = ib;
				if(ins->type == InsTypeNormal){
					ib->ins.push_back(ins);
				}
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
	InsBlock *ib = new InsBlock(1);
	topInsBlocks.insert(ib);
	ib->inEdges.insert(prev);
	prev->outEdges.insert(ib);
	prev->outEdgesStack.push_back( { ib, 1 });

	return topInsBlocks;
}

set<InsBlock*> createDCFGfromInstTrace(vector<InsBase*> &trace) {
	cout << "Creating DCFG from trace..." << endl;
	set<InsBlock*> topInsBlocks = cfgFromTrace(trace);
	vector<InsBase*>().swap(trace);  //free trace memory
	cout << "Created initial CFG with " << topInsBlocks.size() << " blocks." << endl;
	//printDotFile("dcfgBC.gv");

	compressCFG(topInsBlocks);
	//printDotFile("dcfgLC.gv");
	cout << "Compressed CFG with " << topInsBlocks.size() << " blocks." << endl;

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
		cout << setw(40) << i->hashedRoot->root->dis;

		cout << setw(20) << "TotalSz: " << i->patInfo->totalSz;
		cout << setw(20) << i->patInfo->pat->printPattern();
		cout << setw(10) << "[" << setw(10) << i->patInfo->addrRange.s << " : " << setw(10) << i->patInfo->addrRange.e
				<< "]\t";
		cout << setw(10);
		int pCnt = 0;
		for (auto s : i->patInfo->strideDist) {
			if (pCnt++ == 6)
				break;
			cout << "{" << s.first << ":" << s.second << "} ";
		}
		cout << "\t" << i->hashedRoot->root->srcLine << "\t\t" << i->patInfo->addr.size() << "\t";
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
		sz += it->patInfo->totalSz;
	}
	return sz;
}

vector<InsMem*> keepTop(vector<InsMem*> &insList, double perc) {
	UINT64 sz = getTotalAccessSz(insList);
	cout << "Before pruning. NumInst: " << insList.size() << "\t\tAccessSz: " << sz << endl;
	UINT64 szAfter = sz * perc / 100.0;

	//sort using total accessed size
	sort(insList.begin(), insList.end(), [](const InsMem *lhs, const InsMem *rhs) {
		return lhs->patInfo->totalSz > rhs->patInfo->totalSz;
	});

	vector<InsMem*> out;
	sz = 0;
	for (InsMem *it : insList) {
		out.push_back(it);
		sz += it->patInfo->totalSz;
		if (sz > szAfter)
			break;
	}

	cout << "After pruning. NumInst: " << out.size() << "\t\tAccessSz: " << getTotalAccessSz(out) << endl;
	return out;
}

vector<InsMem*> deleteConstAccess2(const vector<InsMem*> &insList) {
	vector<InsMem*> out;
	for (InsMem *it : insList) {
		ADDRINT lastAddr = 0;
		UINT64 zeroCnt = 0;
		for(ADDRINT addr : it->patInfo->addr){
			if(lastAddr - addr == 0){
				zeroCnt++;
			}
			lastAddr = addr;
		}

		//consider only if less than 20% is zero stride access
		if(zeroCnt < it->patInfo->addr.size() * 0.2){
			it->patInfo->totalSz = it->patInfo->addr.size() * it->accSz;
			out.push_back(it);
		} else {
			vector<ADDRINT>().swap(it->patInfo->addr);
		}
	}
	return out;
}

vector<InsMem*> deleteConstAccess(const vector<InsMem*> &insList) {
	vector<InsMem*> out;
	out.reserve(insList.size());
	for (InsMem *it : insList) {
		if (it->patInfo->pat) {
			if (it->patInfo->pat->type == PatType::PatTypeConst) {
				continue;
			}
		}
		out.push_back(it);
	}
	return out;
}

vector<InsMem*> deleteZeroAccesses(const vector<InsBase*> &insList) {
	vector<InsMem*> out;
	for (InsBase *it : insList) {
		if (it->type == InsTypeNormal) {
			InsMem *ins = static_cast<InsMem*>(it);
			PatternInfo *pat = ins->patInfo;
			pat->totalSz = ins->accSz * pat->addr.size();
			if (pat->totalSz >= MIN_SZ) {
				out.push_back(ins);
			} else {
				vector<ADDRINT>().swap(pat->addr);
			}
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

void updateStrideInfo(vector<InsMem*> instList){
	cout << "Updating stride info..." << endl;
	for (InsMem *it : instList) {
		PatternInfo *pat = it->patInfo;
		UINT64 cnt = pat->addr.size();
		INT64 lastStride = 0xDEADBEEF;
		bool isRandom = false;
		bool isValidAddrMap = true;
		for (UINT64 i = 0; i < (cnt - 1); i++) {
			ADDRINT currAddr = pat->addr[i];
			ADDRINT nextAddr = pat->addr[i + 1];

			INT64 stride = nextAddr - currAddr;
			pat->strideDist[stride]++;
			if(pat->strideDist.size() > 30){
				isRandom = true;
				break;
			}
			if (stride != lastStride && isValidAddrMap) {
				//stride change point!
				auto iter = pat->addrStrideMap.find(currAddr);
				if(iter == pat->addrStrideMap.end()){
					//not found, insert
					pat->addrStrideMap[currAddr] = stride;
				}
				else if(iter->second != stride){
					//found, but different stride. Invalidate...
					iter->second = -1;
					isValidAddrMap = false;
				}
				if(pat->addrStrideMap.size() > MAX_SMALL_TILES){
					isValidAddrMap = false;
				}
			}
			lastStride = stride;
		}
		if(isRandom){
			it->patInfo->pat = PatternRandom::create(it);
		}
	}
}

void derivePattern(const vector<InsMem*> &insList) {
	for (InsMem *it : insList) {
		//check if already assigned a pattern
		if (it->patInfo->pat) {
			continue;
		}

		//check for repeats in loops
		deriveLoopInfo(it);

		//check if loop indexed
		if ((it->patInfo->pat = PatternLoopIndexed::create(it))) {
			continue;
		}

		//check if small tiled access
		if ((it->patInfo->pat = PatternSmallTile::create(it))) {
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
		if ((it->patInfo->pat = PatternDominant::create(it))) {
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
		it->patInfo->pat = PatternRandom::create(it);
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

void markTopAndProcessInfo(vector<InsMem*> &insList) {
	for (InsMem *it : insList) {
		it->isTop = true;         //mark as top instruction
		//update address start and end
		ADDRINT min = 0xFFFFFFFFFFFFFFFFULL;
		ADDRINT max = 0;
		for(ADDRINT addr : it->patInfo->addr){
			if(addr > max){
				max = addr;
			}
			if(addr < min){
				min = addr;
			}
		}
		it->patInfo->addrRange.s = min;
		it->patInfo->addrRange.e = max + it->accSz;
	}
}

void updateAddressSpace(vector<InsMem*> &insList) {
	cout << "Updating address space..." << endl;
	//sort using min address
	sort(insList.begin(), insList.end(), [](const InsMem *lhs, const InsMem *rhs) {
		if (lhs->patInfo->addrRange.s == rhs->patInfo->addrRange.s) {
			return lhs->patInfo->addrRange.e < rhs->patInfo->addrRange.e;
		}
		return lhs->patInfo->addrRange.s < rhs->patInfo->addrRange.s;
	});

	//update address space to remove gaps
	ADDRINT gmax = 0;
	ADDRINT gap = 0;
	for (InsMem *it : insList) {
		Interval &range = it->patInfo->addrRange;
		if (range.s > gmax) {
			//found a gap in the address space
			gap = gap + range.s - gmax;

			//ensure alignment of the original address
			//gap &= getMask(range.s);

			//align to access size
			gap &= ~(it->accSz - 1ULL);
		}
		if (range.e > gmax) {
			//update max address if needed
			gmax = range.e;
		}

		range.s -= gap;
		range.e -= gap;
		it->patInfo->gap = gap;
		//cout << gap << endl;

		//update global max addresses
		if (range.e > globalMaxAddr) {
			globalMaxAddr = range.e;
		}
	}
	cout << "Global max address: " << globalMaxAddr << endl;
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

void writeLog(const char *logFile) {
	ofstream log(logFile);
	log << "ins,addr,r0w1\n";
	for (size_t i = 0; i < insTrace.size(); i++) {
		if (insTrace[i]->type == InsTypeNormal) {
			InsMem *ins = (InsMem*) (insTrace[i]);
			if (ins->isTop) {
				ADDRINT ea = ins->patInfo->addr[ins->cnt];
				ins->cnt++;
				log << ins->id << "," << ea << ",";
				if (ins->accType == AccessTypeRead) {
					log << "0\n";
				} else if (ins->accType == AccessTypeWrite) {
					log << "1\n";
				}
			}
		}
	}
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
			InsSingleLoop *ins = (InsSingleLoop*) insList[i];
			replaceRand(ins->ins);
		} else if (insList[i]->type == InsTypeNormal) {
			InsMem *ins = (InsMem*) insList[i];
			if (ins->patInfo->pat->type == PatTypeSmallTile) {
				if ((ins->patInfo->addrRange.e - ins->patInfo->addrRange.s) == 124) {
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

VOID Fini(INT32 code, VOID *v) {
	cout << "AT FINI" << endl;
	// 0. Filter zero  (or very low) cnt instructions
	vector<InsMem*> filteredInsList;
	//cout << "Static memory instructions: Before any filtering " << InsBase::insList.size() << endl;

	filteredInsList = deleteZeroAccesses(InsBase::insList);
	cout << "Static memory instructions: After zero access delete " << filteredInsList.size() << endl;

	//derivePatternInitial(filteredInsList);   //needed for next step
	// 1. filter constant access instructions
	filteredInsList = deleteConstAccess2(filteredInsList);
	cout << "Static memory instructions: After const access delete " << filteredInsList.size() << endl;

	// 2. Only take instructions that represents top_perc of reads/writes
	filteredInsList = keepTop(filteredInsList, top_perc);
	//cout << "Static memory instructions: top " << filteredInsList.size() << endl;
	markTopAndProcessInfo(filteredInsList);
	//updateAddressSpace(filteredInsList);

	updateStrideInfo(filteredInsList);
	updateAddressSpace(filteredInsList);

	cout << "Inst Trace size: " << insTrace.size() << endl;
	set<InsBlock*> cfg = createDCFGfromInstTrace(insTrace);
	updateParentLoops(cfg);
	printMaxEdgeStack(cfg);
	derivePattern(filteredInsList);
	//detectRandFunction();

	printInfo(filteredInsList);
	generateCode(filteredInsList, cfg, out_file_name.c_str());


	//if(log_en){
	//  writeLog("top_trace.csv");
	//}

	//printStrideAddr(filteredInsList, 394900101);
	//printStrideRef(filteredInsList, 394900101);

	//assert(callHash == HASH_INIT_VALUE);
	//for(InsNormal* it : insNormalList){ delete it; }
	for (PatternInfo *it : patternList) {
		delete it;
	}
	for (InsRoot *it : insRootList) {
		delete it;
	}
	for (InsHashedRoot *it : insHashedRootList) {
		delete it;
	}
	InsBlock::deleteAll();
	InsBase::deleteAll();

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
				string name = PIN_UndecorateSymbolName(RTN_Name(rtn), UNDECORATION_NAME_ONLY);
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
	cout << "Exact match not found! Tagging all functions containing \"" << rtn_name << "\"..." << endl;
	for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)) {
		if (SEC_Name(sec) == ".text") {
			for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn)) {
				string name = PIN_UndecorateSymbolName(RTN_Name(rtn), UNDECORATION_NAME_ONLY);

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
		cout << "Unable to find any function containing \"" << rtn_name << "\"... Quitting..." << endl;
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
			ins->patInfo = new PatternInfo();
			patternList.push_back(ins->patInfo);
		}
	}
	InsHashedRoot *hrt = root->childMap[callHash];
	return hrt->children[op];
}

void record(InsRoot *root, ADDRINT ea, UINT32 op) {
	if (rtnEntryCnt <= 0)
		return;
	InsMem *ins = getInsLeaf(root, op);
	insTrace.push_back(ins);
	ins->patInfo->addr.push_back(ea);
	//if(log_en){
	//  addrTrace.push_back(ea);
	//}
}

InsRoot* createInsRoot(INS &ins) {
	static UINT64 rootId = 0;
	static unordered_map<ADDRINT, InsRoot*> processedIns;   //set of already processed instructions

	ADDRINT addr = INS_Address(ins);
	// check if already processed or not
	auto it = processedIns.find(addr);
	if (it != processedIns.end()) {
		return it->second;   //already processed
	}

	InsRoot *root = new InsRoot();
	root->id = rootId++;
	PIN_GetSourceLocation(addr, NULL, &root->srcLine, &root->srcFile);
	root->dis = INS_Disassemble(ins);
	root->opCnt = INS_MemoryOperandCount(ins);
	for (UINT32 i = 0; i < root->opCnt; i++) {
		OpInfo info;
		info.accSz = INS_MemoryOperandSize(ins, i);
		if (INS_MemoryOperandIsRead(ins, i) && !INS_MemoryOperandIsWritten(ins, i)) {
			info.accType = AccessType::AccessTypeRead;
		} else if (!INS_MemoryOperandIsRead(ins, i) && INS_MemoryOperandIsWritten(ins, i)) {
			info.accType = AccessType::AccessTypeWrite;
		} else if (INS_MemoryOperandIsRead(ins, i) && INS_MemoryOperandIsWritten(ins, i)) {
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

InsBase* getJmpInsLeaf(InsRoot *root) {
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
}

void Instruction(INS ins, VOID *v) {
	// do some filtering
	if (INS_IsLea(ins))
		return;
	// Add other instructions if needed

	if (INS_IsCall(ins)) {    //excludes system call
		INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) anyCallEntry, IARG_INST_PTR, IARG_END);
		return;
	}

	if (INS_IsRet(ins)) {
		INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) anyCallRet, IARG_END);
		return;
	}

	if (INS_Category(ins) == XED_CATEGORY_COND_BR) {
		InsRoot *root = createInsRoot(ins);
		INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR) jmpInst, IARG_PTR, root, IARG_END);
		return;
	}

	// Get the memory operand count of the current instruction.
	UINT32 memOperands = INS_MemoryOperandCount(ins);

	if (memOperands) {
		InsRoot *root = createInsRoot(ins);
		for (UINT32 memOp = 0; memOp < memOperands; memOp++) {
			INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR) record, IARG_PTR, root, IARG_MEMORYOP_EA, memOp,
					IARG_UINT32, memOp, IARG_END);
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

