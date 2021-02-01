#include <InsMem.h>
#include "PatternConst.h"

PatternConst* PatternConst::create(InsMem* ins) {
    if(ins->strideDist.find(0) != ins->strideDist.end()){
      UINT64 zeroCnt = ins->strideDist[0];
      //if zero stride access contributes more than 80%
      if(zeroCnt * ins->accSz > ins->totalSz * 0.8){
        return &pat;
      }
    }
    return nullptr;
  }

PatternConst PatternConst::pat;
