#pragma once

#include "cln_types.h"
#include "PatternBase.h"

class PatternConst : public PatternBase{
private:
  PatternConst() : PatternBase(nullptr, PatType::PatTypeConst) {}
  static PatternConst pat;

public:
  static PatternConst* create(const InsNormal* ins);

  std::string printPattern() const {
    return "Const";
  }
};

