#include <InsMem.h>
#include "PatternLoopIndexed.h"
#include "PatternInfo.h"
#include "InsLoopBase.h"
#include "cln_utils.h"

using namespace std;

PatternLoopIndexed* PatternLoopIndexed::create(const InsMem* ins){
    if(ins->patInfo->loops.size() == 0){ //no loops
      return nullptr;
    }

    for(const auto &li : ins->patInfo->loops){
      if(li.lp == nullptr){
        return nullptr;   // not simple loop indexed
      }
    }

    return new PatternLoopIndexed(ins);
  }

string PatternLoopIndexed::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "//Loop Indexed\n";
  ss << _tab(indent) << "addr = " << ins->patInfo->addrRange.s;
  for(const auto &it : ins->patInfo->loops){
    if(it.m){
      ss << " + (" << it.m << " * loop" << it.lp->id << ")";
    }
  }
  ss << ";\n";
  ss << ins->printReadWrite(indent, false);
  return ss.str();
}

string PatternLoopIndexed::printPattern() const {
  return "LoopIndexed";
}
