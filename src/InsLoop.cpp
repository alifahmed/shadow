
#include "InsLoop.h"

using namespace std;

UINT64 InsLoop::_idCnt = 0;

/*InsLoop* InsLoop::splitLoop(UINT64 inIter){
  if(inIter == 0) return nullptr;
  if(inIter == 1) return this;
  if(iters % inIter) return nullptr;   //not divisable

  UINT64 outIter = iters / inIter;

  //create new out loop
  InsSingleLoop* outLoop = new InsSingleLoop();
  outLoop->iters = outIter;
  outLoop->ins.push_back(this);

  //Fix In loop
  this->iters = inIter;

  //caller should fix the references to the loop
  return outLoop;
}*/

string InsLoop::printDot(UINT32 indent) const {
  stringstream out;
  out << "<br />" << _tab(indent) << "loop" << id << ": " << iters;
  for(InsBase* it :ins){
    out << it->printDot(indent+1);
  }
  return out.str();
}


string InsLoop::printCodeBody(UINT32 indent) const {
  stringstream out;
  for(const auto &str : prefix){
    out << _tab(indent) << str;
  }
  out << _tab(indent) << "for(uint64_t loop" << id << " = 0; loop" << id << " < " << iters << "ULL; loop" << id << "++){\n";
  for(const auto &str : postfix){
    out << _tab(indent+1) << str;
  }
  for(InsBase* base : ins){
    out << base->printCodeBody(indent+1);
  }
  out << _tab(indent) << "}\n";
  return out.str();
}

void InsLoop::setParentLoop(InsLoop* pl){
  parentLoop = pl;
  for(InsBase* i : ins) {
    i->setParentLoop(this);
  }
}
