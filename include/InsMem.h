#pragma once

#include <cln_types.h>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include "InsBase.h"
#include "LoopInfo.h"

class InsHashedRoot;
class InsBlock;
class PatternBase;

class InsMem : public InsBase {
public:
  std::vector<ADDRINT> addr;
  UINT64 totalSz = 0;
  UINT64 minAddr = 0xFFFFFFFFFFFFFFFFULL;
  UINT64 maxAddr = 0;

  //std::unordered_map<ADDRINT, INT64> addrStrideMap;
  std::unordered_map<ADDRINT, INT64> addrStrideMap;
  std::unordered_map<INT64, UINT64> strideDist;

  std::vector<LoopInfo> loops;

  PatternBase* pat = nullptr;

  //size_t cnt = 0;
  InsHashedRoot* hashedRoot = nullptr;
  UINT64 accSz = 0;
  AccessType accType = AccessTypeInvalid;

  InsMem(UINT64 id) : InsBase(InsTypeNormal, id){};
  ~InsMem(){}

  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const ;
  std::string printReadWrite(UINT32 indent, bool useId) const ;
  void setParentLoop(InsLoop* pl);
  void reset();
};
