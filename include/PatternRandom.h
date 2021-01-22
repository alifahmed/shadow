#pragma once

#include "PatternBase.h"

class PatternRandom : public PatternBase{
private:
  PatternRandom(const InsMem* _ins) : PatternBase(_ins, PatType::PatTypeRandom) {}

public:
  static PatternRandom* create(const InsMem* _ins){
    return new PatternRandom(_ins);
  }

  std::string genBody(UINT32 indent) const;
  std::string printPattern() const {
    return "Random";
  }
};
