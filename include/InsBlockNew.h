#pragma once

#include <set>
#include <vector>
#include "cln_types.h"
#include "InsBase.h"


class InsBlockNew : public InsBase {
public:
  UINT64 loopCnt = 1;
  std::set<InsBlockNew*> inEdges;
  std::set<InsBlockNew*> outEdges;

  std::vector<InsBase*> insList;

};
