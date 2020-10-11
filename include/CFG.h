#pragma once

#include <set>
#include "cln_types.h"

class InsBlock;

class CFG {
  InsBlock* s;
  InsBlock* e;
  std::set<InsBlock> blocks;



};
