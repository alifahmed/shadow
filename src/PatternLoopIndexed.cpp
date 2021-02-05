#include <InsLoop.h>
#include <InsMem.h>
#include "PatternLoopIndexed.h"
#include "cln_utils.h"

using namespace std;

PatternLoopIndexed* PatternLoopIndexed::create(InsMem *ins) {
  if (ins->loops.size() == 0) { //no loops
    return nullptr;
  }

  for(auto it : ins->loops){
    if(it.lp == nullptr){
      return nullptr;
    }
  }

  return new PatternLoopIndexed(ins);
}

string PatternLoopIndexed::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "//Loop Indexed\n";
  ss << _tab(indent) << "addr = " << ins->addr[0] << "LL";
  for (const auto &it : ins->loops) {
    if (it.m) {
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
