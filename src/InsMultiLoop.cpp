#include "InsMultiLoop.h"
#include "InsBlock.h"

using namespace std;

string InsMultiLoop::printDot(UINT32 indent) const {
  stringstream out;
  out << "<br />" << _tab(indent) << "loop" << id << ": " << iters << "  Block " << sBlk->getId();
  return out.str();
}

string InsMultiLoop::printCodeBody(UINT32 indent) const {
  return "Multi Loop\n";
}

void InsMultiLoop::setParentLoop(InsLoopBase* pl) {
  parentLoop = pl;
  for(InsBlock* blk : cfg){
    blk->setParentLoop(this);
  }
}
