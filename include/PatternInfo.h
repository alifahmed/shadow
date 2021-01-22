#pragma once

#include <cln_types.h>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include "Interval.h"
#include "LoopInfo.h"

class PatternBase;

class PatternInfo{
public:
  std::vector<ADDRINT> addr;
  UINT64 totalSz = 0;
  Interval addrRange;
  std::unordered_map<ADDRINT, INT64> addrStrideMap;
  //std::map<ADDRINT, std::set<INT64>> addrStrideMap;
  //std::map<INT64, std::set<ADDRINT>> strideAddr;
  //std::map<INT64, std::set<ADDRINT>> strideRef;
  std::unordered_map<INT64, UINT64> strideDist;
  PatternBase* pat;
  std::vector<LoopInfo> loops;
  ADDRINT gap = 0;
};
