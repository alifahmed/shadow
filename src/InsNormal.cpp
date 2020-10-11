#include <string>
#include <sstream>
#include "InsNormal.h"
#include "InsHashedRoot.h"
#include "InsRoot.h"

using namespace std;

char InsNormal::getMovSuffix() const {
  switch(accSz){
  case 1: return 'b';
  case 2: return 'w';
  case 4: return 'l';
  case 8: return 'q';
  default: return 'Z';    //invalid access size
  }
}

string InsNormal::printDot(UINT32 indent) const {
  stringstream out;
  out << "<br />" << _tab(indent) << id << ": ";
  out << hashedRoot->root->srcLine;// << ", " << ins->patInfo->pat->printPattern();
  return out.str();
}

string InsNormal::printCodeBody(UINT32 indent) const {
  stringstream ss;
  //ss << patInfo->pat->genBody(indent) << "\n";
  return ss.str();
}

string InsNormal::printReadWrite(UINT32 indent, bool useId) const {
  stringstream ad;
  if(useId){
    ad << "addr_" << id;
  }
  else{
    ad << "addr";
  }

  stringstream ss;
  if(accType == AccessType::AccessTypeRead){
    ss << _tab(indent) << "__asm__ __volatile__ (\"mov" << getMovSuffix() << " (%1,%2), %0\" : \"=r\"(tmp" << getMovSuffix() <<
        ") : \"r\"(gm), \"r\"(" << ad.str() << ") : \"memory\");\n";
  }
  else if(accType == AccessType::AccessTypeWrite){
    ss << _tab(indent) << "__asm__ __volatile__ (\"mov" << getMovSuffix() << " %2, (%0,%1)\" : : \"r\"(gm), \"r\"(" << ad.str() <<
        "), \"r\"(tmp" << getMovSuffix() << ") : \"memory\");\n";
  }
  else{
    cerr << "[ERROR] Unimplemented access type for " << id << endl;
    return "";
  }
  return ss.str();
}

void InsNormal::setParentLoop(InsLoopBase* pl){
    parentLoop = pl;
}

