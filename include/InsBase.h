#pragma once

#include "cln_types.h"

#include <vector>
#include <string>

class InsLoopBase;

class InsBase{
private:
  InsBase();

public:
  static std::vector<InsBase*> insList;
  const UINT64 id = 0;
  const InsType type = InsTypeInvalid;
  InsLoopBase* parentLoop = nullptr;


  InsBase(InsType type, UINT64 id);
  virtual ~InsBase(){};


  virtual std::string printDot(UINT32 indent) const = 0;
  virtual std::string printCodeBody(UINT32 indent) const = 0;
  virtual void setParentLoop(InsLoopBase* pl) = 0;

  static void deleteAll();
};
