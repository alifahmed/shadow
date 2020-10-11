#pragma once

#include "cln_types.h"
#include "InsLoopBase.h"

class InsBlock;

class InsMultiLoop : public InsLoopBase {
public:
  std::set<InsBlock*> cfg;
  InsBlock* sBlk = nullptr;
  InsBlock* eBlk = nullptr;

  InsMultiLoop() : InsLoopBase(InsTypeMultiLoop) {}

  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const;
  void setParentLoop(InsLoopBase* pl);
};
