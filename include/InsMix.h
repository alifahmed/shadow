#pragma once

#include <cln_types.h>

#include <vector>

class InsMix {
public:
  enum InsMixType {
    LOAD, STORE, CONTROL, BRANCH, FPMUL, FPDIV, FPOTHER, INTMUL, INTDIV, INTOTHER, SYSCALL, OTHER, InsMixNum
  };
  std::vector<UINT64> cnt;

  InsMix() { cnt.resize(InsMixNum, 0); }
};