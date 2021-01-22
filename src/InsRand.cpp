#include "InsRand.h"

using namespace std;

string InsRand::printDot(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "<br /> rand()";
  return ss.str();
}

string InsRand::printCodeBody(UINT32 indent) const{
  stringstream ss;
  ss << _tab(indent) << "rand();\n";
  return ss.str();
}

void InsRand::setParentLoop(InsLoopBase* pl){

}
