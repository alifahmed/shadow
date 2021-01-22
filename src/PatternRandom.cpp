#include <InsMem.h>
#include "PatternRandom.h"
#include "PatternInfo.h"
#include "cln_utils.h"

using namespace std;

string PatternRandom::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "//Random\n";
  //first, generate random address within range, and without accessing memory
  //ss << _tab(indent) << cln_utils::printHash();
  ss << _tab(indent) << "addr = (bounded_rnd(" << ins->patInfo->addrRange.e - ins->patInfo->addrRange.s << ") + " << ins->patInfo->addrRange.s << ") & ~" << ins->accSz-1 << "ULL;\n";
  ss << ins->printReadWrite(indent, false);
  return ss.str();
}
