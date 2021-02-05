#pragma once

#include <string>
#include "cln_types.h"
#include "InsBase.h"

class InsCondJump : public InsBase {
private:
  InsCondJump();

public:
  InsCondJump(UINT64 id) : InsBase(InsTypeCondJump, id){
	  isTop = true;
  };

  std::string printDot(UINT32 indent) const {
    return "";
  }

  std::string printCodeBody(UINT32 indent) const {
    return "";
  }

  void setParentLoop(InsLoop* pl) {
    parentLoop = pl;
  }
};
