#include "InsMultiLoop.h"
#include "InsBlock.h"

using namespace std;

string InsMultiLoop::printDot(UINT32 indent) const {
  stringstream out;
  out << "<br />" << _tab(indent) << "loop" << id << ": " << loopCnt << "  Block " << sBlk->id;
  return out.str();
}

string InsMultiLoop::printCodeBody(UINT32 indent) const {
  return "Multi Loop\n";
}
