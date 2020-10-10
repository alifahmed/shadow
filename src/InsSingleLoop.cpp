#include "InsSingleLoop.h"

using namespace std;

string InsSingleLoop::printDot(UINT32 indent) const {
    stringstream out;
    out << "<br />" << _tab(indent) << "loop" << id << ": " << loopCnt;
    for(InsBase* it :ins){
      out << it->printDot(indent+1);
    }
    return out.str();
  }


string InsSingleLoop::printCodeBody(UINT32 indent) const {
    stringstream out;
    out << _tab(indent) << "for(uint64_t loop" << id << " = 0; loop" << id << " < " << loopCnt << "ULL; loop" << id << "++){\n";
    for(const auto &str : extraStr){
      out << _tab(indent+1) << str;
    }
    for(InsBase* base : ins){
      out << base->printCodeBody(indent+1);
    }
    out << _tab(indent) << "}\n";
    return out.str();
  }
