#pragma once

#include <cln_types.h>

#include <string>
#include <sstream>
#include <vector>
#include "InsBase.h"

class PatternInfo;
class InsHashedRoot;
class InsBlock;

class InsMem : public InsBase {
public:
  PatternInfo *patInfo = nullptr;
  size_t cnt = 0;
  InsHashedRoot* hashedRoot = nullptr;
  UINT32 accSz = 0;
  AccessType accType = AccessTypeInvalid;
  //InsBlock* block = nullptr;

  InsMem(UINT64 id) : InsBase(InsTypeNormal, id){};

  char getMovSuffix() const;

  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const ;
  std::string printReadWrite(UINT32 indent, bool useId) const ;
  void setParentLoop(InsLoopBase* pl);
};
