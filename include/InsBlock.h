#pragma once

#include <map>
#include <set>
#include <cln_types.h>
#include "InsBase.h"


class InsBlock {
private:
  static UINT64 _idCnt;
  UINT64 id = -1;

  //checks if out edges are entered in same order every time
  bool isOutOrderConst(std::vector<InsBlock*> &order) const;

  //merges run count of consecutive same blocks
  void updateOutEdgesStack();

  //print edge info
  std::string printEdgeInfo(UINT32 indent) const;

  typedef struct {
    UINT64 totCnt = 0;
    UINT64 avgCnt = 0;    //average iter per entry
    UINT64 remCnt = 0;    //remaining count
    UINT64 entryCnt = 0;
  } EdgeStat;

  //returns 0 if corresponding block does not have constant entry count
  std::map<InsBlock*, EdgeStat> calcEdgeStats() const;

public:
  static std::vector<InsBlock*> blockList;
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

  //replaces all occurrences of old with nw on the outEdges
  void replaceOutEdge(InsBlock* old, InsBlock* nw);
  void removeOutEdge(InsBlock* out);

  //operate on all registered blocks
  static std::string printDotAll(UINT32 indent);
  static UINT64 getNumBlocks();
  static void deleteAll();
};
