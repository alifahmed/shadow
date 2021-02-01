#include <InsMem.h>
#include "PatternBase.h"
#include "InsHashedRoot.h"
#include "InsRoot.h"


using namespace std;

string PatternBase::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "ID: " << ins->id << "\n";
  ss << _tab(indent) << "Type: ";
  if(ins->accType == AccessType::AccessTypeRead)        ss << "READ\n";
  else if(ins->accType == AccessType::AccessTypeWrite)  ss << "WRITE\n";
  else if(ins->accType == AccessType::AccessTypeRMW)    ss << "RMW\n";
  else                                                  ss << "Invalid\n";
  ss << _tab(indent) << "Code Line: " << ins->hashedRoot->root->srcLine << "\n";
  ss << _tab(indent);
  for(auto s : ins->strideDist){
    ss << "{" << s.first << ":" << s.second << "} ";
  }
  ss << "\n";
  ss << _tab(indent) << ins->pat->printPattern() << "\n";
  ss << _tab(indent) << ins->maxAddr - ins->minAddr << " [ " << ins->minAddr << " : " << ins->maxAddr << " ]\n";
  return ss.str();
}
