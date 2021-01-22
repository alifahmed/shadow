#pragma once

#include "cln_types.h"
#include "PatternBase.h"


class PatternDominant : public PatternBase{
private:
  PatternDominant(const InsMem* ins, INT64 _domStride, std::string _patStr) :
    PatternBase(ins, PatType::PatTypeDominant), domStride(_domStride), patStr(_patStr) {}
  INT64 domStride = 0;
  std::string patStr;

public:
  static PatternDominant* create(const InsMem* ins);

  std::string genHeader(UINT32 indent) const;
  std::string genBody(UINT32 indent) const;
  std::string printPattern() const;
};
