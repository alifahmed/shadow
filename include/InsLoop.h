#pragma once

#include "cln_types.h"

#include <vector>
#include <string>
#include "InsBase.h"

class InsLoop : public InsBase{
private:
  static UINT64 _idCnt;

public:
  UINT64 iters = 1;
  std::vector<std::string> prefix;
  std::vector<std::string> postfix;
  std::vector<InsBase*> ins;

  InsLoop(InsType type) : InsBase(type, _idCnt++) {};

  std::string printDot(UINT32 indent) const;
  std::string printCodeBody(UINT32 indent) const;
  void setParentLoop(InsLoop* pl);

  //virtual InsLoop* splitLoop(UINT64 inIter);
};

