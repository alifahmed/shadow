#pragma once

#include "cln_types.h"
#include "PatternBase.h"

class PatternInvalid : public PatternBase{
private:
  PatternInvalid() : PatternBase(nullptr, PatType::PatTypeInvalid) {}
  static PatternInvalid pat;

public:
  static PatternInvalid* create(const InsMem* _ins){
    return &pat;
  }

  std::string printPattern() const {
    return "Invalid";
  }
};

