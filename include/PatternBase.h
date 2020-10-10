#pragma once

#include <cln_types.h>

class InsNormal;

class PatternBase{
private:
  PatternBase(){};

protected:
  PatternBase(const InsNormal* _ins, PatType _type) {
    this->ins = _ins;
    this->type = _type;
  }

public:
  PatType type;
  const InsNormal* ins;

  virtual ~PatternBase(){};
  virtual std::string genHeader(UINT32 indent) const {return ""; }
  virtual std::string genBody(UINT32 indent) const ;
  virtual std::string printPattern() const = 0;
};
