#pragma once

#include <set>
#include <map>
#include "cln_types.h"

class InsBlock;

class CFG {
private:
  CFG();

public:
  InsBlock* s;
  InsBlock* e;
  std::set<InsBlock*> blocks;
  std::map<InsBlock*, std::set<InsBlock*>> doms;

  //constructor
  CFG(std::set<InsBlock*> blocks);

  //Is 'a' an element of this cfg?
  bool isElem(InsBlock* a);

  //Is 'a' is a dominator of b?
  bool dom(InsBlock* a, InsBlock* b);

  //Is 'a' is a strict dominator of b?
  bool sdom(InsBlock* a, InsBlock* b);

  //Is 'a' is a immediate dominator of b?
  bool idom(InsBlock* a, InsBlock* b);

  //Calculate dominator of all nodes
  void domAll();

  //Is a=>b is a back edge?
  bool isBackEdge(InsBlock* a, InsBlock* b);
};
