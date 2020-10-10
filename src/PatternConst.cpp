#include "PatternConst.h"
#include "PatternInfo.h"
#include "InsNormal.h"

PatternConst* PatternConst::create(const InsNormal* ins) {
    if(ins->patInfo->strideDist.find(0) != ins->patInfo->strideDist.end()){
      UINT64 zeroCnt = ins->patInfo->strideDist[0];
      //if zero stride access contributes more than 80%
      if(zeroCnt * ins->accSz > ins->patInfo->totalSz * 0.8){
        return &pat;
      }
    }
    return nullptr;
  }

PatternConst PatternConst::pat;
