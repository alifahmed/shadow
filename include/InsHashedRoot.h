#pragma once

#include <cln_types.h>

#include <vector>

class InsRoot;
class InsNormal;

class InsHashedRoot {
public:
  UINT64 id;
  InsRoot* root;
  std::vector<InsNormal*> children;
};
