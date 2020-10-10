#pragma once

#include <cln_types.h>

#include <vector>
#include <map>
#include <set>
#include "Interval.h"
#include "LoopInfo.h"

class PatternBase;

class PatternInfo{
public:
  std::vector<ADDRINT> addr;
  UINT64 totalSz = 0;
  Interval addrRange;
  std::map<ADDRINT, std::set<INT64>> addrStrideMap;
  std::map<INT64, std::set<ADDRINT>> strideAddr;
  std::map<INT64, std::set<ADDRINT>> strideRef;
  std::map<INT64, UINT64> strideDist;
  PatternBase* pat;
  std::vector<LoopInfo> loops;
};
