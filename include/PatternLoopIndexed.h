#pragma once

#include <cln_types.h>
#include "PatternBase.h"

class PatternLoopIndexed : public PatternBase{
private:
  PatternLoopIndexed();
  PatternLoopIndexed(const InsMem* _ins) : PatternBase(_ins, PatType::PatLoopIndexed) {}

public:
  static PatternLoopIndexed* create(const InsMem* ins);
  std::string genBody(UINT32 indent) const;
  std::string printPattern() const;
};
