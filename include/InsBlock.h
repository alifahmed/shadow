#pragma once

#include <cln_types.h>

class InsBase;

class InsBlock{
public:
  UINT64 id = -1;
  std::vector< std::pair<InsBlock*, UINT64> > outEdgesStack;   //run count compression
  std::set<InsBlock*> outEdges;
  std::set<InsBlock*> inEdges;
  std::vector<InsBase*> ins;
  bool isUsed = true;

  std::string printDot(UINT32 indent);
};
