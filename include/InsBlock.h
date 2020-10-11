#pragma once

#include <vector>
#include <cln_types.h>
#include "InsBase.h"


class InsBlock {
private:
  static std::vector<InsBlock*> blockList;
  static UINT64 _idCnt;
  UINT64 id = -1;

public:
  std::vector< std::pair<InsBlock*, UINT64> > outEdgesStack;   //run count compression
  std::set<InsBlock*> outEdges;
  std::set<InsBlock*> inEdges;
  std::vector<InsBase*> ins;
  bool isUsed = true;

  //constructors
  explicit InsBlock();
  explicit InsBlock(UINT64 id);

  //class members
  std::string printDot(UINT32 indent) const;
  UINT64 getId() const;
  std::string printCodeBody(UINT32 indent) const;
  void setParentLoop(InsLoopBase* pl);


  //operate on all registered blocks
  static std::string printDotAll(UINT32 indent);
  static UINT64 getNumBlocks();
  static void deleteAll();
};
