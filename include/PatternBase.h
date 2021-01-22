#pragma once

#include <cln_types.h>

class InsMem;

class PatternBase{
private:
  PatternBase(){};

protected:
  PatternBase(const InsMem* _ins, PatType _type) {
    this->ins = _ins;
    this->type = _type;
  }

public:
  PatType type;
  const InsMem* ins;

  virtual ~PatternBase(){};
  virtual std::string genHeader(UINT32 indent) const {return ""; }
  virtual std::string genBody(UINT32 indent) const ;
  virtual std::string printPattern() const = 0;
};
