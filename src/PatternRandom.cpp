#include "PatternRandom.h"
#include "InsNormal.h"
#include "PatternInfo.h"

using namespace std;

string PatternRandom::genBody(UINT32 indent) const {
  stringstream ss;
  //first, generate random address within range, and without accessing memory
  ss << _tab(indent) << "hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);\n";
  ss << _tab(indent) << "addr = ((hash % " << ins->patInfo->addrRange.e - ins->patInfo->addrRange.s << ") + " << ins->patInfo->addrRange.s << ") & ~" << ins->accSz-1 << "ULL;\n";
  ss << ins->printReadWrite(indent, false);
  return ss.str();
}
