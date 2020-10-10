#include "PatternBase.h"

class PatternSmallTile : public PatternBase{
private:
  PatternSmallTile(const InsNormal* _ins) : PatternBase(_ins, PatType::PatTypeSmallTile){};

public:
  static PatternSmallTile* create(const InsNormal* ins);

  std::string genHeader(UINT32 indent) const;
  std::string genBody(UINT32 indent) const;
  std::string printPattern() const;
};
