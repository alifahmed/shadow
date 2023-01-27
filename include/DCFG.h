#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <set>

#include "pinplay.H"
#include "dcfg_pin_api.H"
#include "dcfg_trace_api.H"
#include "dcfg_api.H"

class InsBlock;

using namespace dcfg_pin_api;
using namespace dcfg_trace_api;
using namespace dcfg_api;

class DCFG {

public:

  std::string dcfg_cfg_file;
  ofstream shadow_output, dcfg_output;
  UINT64 shadow_cnt = 0, dcfg_cnt = 0;
  bool dcfg_trace_done;
  DCFG_PIN_MANAGER *dcfgMgr;
  DCFG_DATA *dcfgData;
  DCFG_PROCESS_CPTR dcfgProcInfo = nullptr;
  DCFG_TRACE_READER* dcfgTraceReader;
  DCFG_ID_VECTOR dcfgTraceBuffer;
  DCFG_ID_VECTOR::iterator dcfgTraceBufferPtr;
  UINT64 total_addr = 0, total_addr_in_bbl = 0;
  const UINT64 BBL_INVALID = 0xFFFFFFFFFFFFFFFF;
  InsBlock *beginBlock, *endBlock;
  std::unordered_map<UINT64, InsBlock*> DCFGMap;

  InsBlock *prevBlockinTrace = nullptr;

  // if cfg file not supplied then we are just generating cfg file as the first pass
  DCFG(InsBlock *&beginBlock, InsBlock *&endBlock, const std::string &dcfg_cfg_file="");

  bool exist() {
    return dcfgProcInfo != nullptr;
  }

  void initDCFGMap(InsBlock *&beginBlock, InsBlock *&endBlock);
  InsBlock *getInsBlockByBBLAddress(ADDRINT addr);
  void write(const std::string &file);
  void compressDCFG(std::set<InsBlock *> &cfg);

  static void recordBBL(DCFG *self, InsBlock *blk);

};
