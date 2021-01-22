#pragma once

#include <cln_types.h>

#include <vector>

class InsRoot;
class InsMem;
class InsBase;

class InsHashedRoot {
public:
  UINT64 id;
  InsRoot* root;
  std::vector<InsMem*> children;
  InsBase* onlyChild;
};
