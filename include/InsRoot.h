#pragma once

#include <cln_types.h>

#include <vector>
#include <string>
#include <map>

class InsHashedRoot;

class InsRoot{
public:
  UINT64 id;
  UINT64 bblid;
  INT32 srcLine;
  std::string srcFile;
  std::string dis;
  UINT32 opCnt;
  std::vector<OpInfo> opInfo;
  std::map<ADDRINT, InsHashedRoot*> childMap;
};
