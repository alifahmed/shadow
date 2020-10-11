#include "InsLoopBase.h"

#include "InsSingleLoop.h"

InsLoopBase* InsLoopBase::splitLoop(UINT64 inIter){
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
}

UINT64 InsLoopBase::_idCnt = 0;
