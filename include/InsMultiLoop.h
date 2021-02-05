#pragma once

#include <InsLoop.h>
#include "cln_types.h"

class InsBlock;

class InsMultiLoop : public InsLoop {
public:
  std::set<InsBlock*> cfg;
  InsBlock* sBlk = nullptr;
  InsBlock* eBlk = nullptr;

  InsMultiLoop() : InsLoop(InsTypeMultiLoop) {}

  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const;
  void setParentLoop(InsLoop* pl);
};
