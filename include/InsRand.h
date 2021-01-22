#pragma once

#include "cln_types.h"
#include "InsBase.h"

class InsRand : public InsBase {
public:
  InsRand(UINT64 id) : InsBase(InsTypeRandFunc, id) {};

  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const;
  void setParentLoop(InsLoopBase* pl);
};
