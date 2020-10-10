#pragma once

#include <cln_types.h>

#include <vector>
#include <string>

class InsLoopBase;

class InsBase{
private:
  InsBase(){};

public:
  static std::vector<InsBase*> insList;
  UINT64 id = 0;
  InsType type = InsTypeInvalid;
  InsLoopBase* parentLoop = nullptr;

  virtual ~InsBase(){};

  InsBase(InsType type, UINT64 id);
  static void deleteAllInst();

  virtual std::string printDot(UINT32 indent) const {return "";};
  virtual std::string printCodeBody(UINT32 indent) const = 0;
};
