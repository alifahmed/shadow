#pragma once

#include "cln_types.h"

#include <vector>
#include <string>

class InsLoop;
class InsBlock;

class InsBase{
private:
  InsBase();

public:
  static std::vector<InsBase*> insList;
  const UINT64 id = 0;
  const InsType type = InsTypeInvalid;
  InsLoop* parentLoop = nullptr;
  bool isTop = false;
  InsBlock* parentBlock = nullptr;

  InsBase(InsType type, UINT64 id);
  virtual ~InsBase(){};


  virtual std::string printDot(UINT32 indent) const = 0;
  virtual std::string printCodeBody(UINT32 indent) const = 0;
  virtual void setParentLoop(InsLoop* pl) = 0;

  static void deleteAll();
};
