#pragma once

#include <cln_types.h>

#include <vector>
#include <string>
#include "InsBase.h"


class InsLoopBase : public InsBase{
private:
  static UINT64 _idCnt;

public:
  UINT64 loopCnt = 1;
  std::vector<std::string> extraStr;

  virtual ~InsLoopBase(){};
  InsLoopBase(InsType type) : InsBase(type, _idCnt++) {};
};

