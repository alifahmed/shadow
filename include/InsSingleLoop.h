#pragma once

#include <cln_types.h>

#include <vector>
#include <string>
#include <sstream>
#include "InsLoopBase.h"

class InsBase;

class InsSingleLoop : public InsLoopBase {
public:
  std::vector<InsBase*> ins;

  InsSingleLoop() : InsLoopBase(InsTypeSingleLoop) {}
  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const;
  void setParentLoop(InsLoopBase* pl);
};
