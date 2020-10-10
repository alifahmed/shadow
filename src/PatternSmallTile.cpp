#include "PatternSmallTile.h"
#include "PatternInfo.h"
#include "InsNormal.h"

using namespace std;

PatternSmallTile* PatternSmallTile::create(const InsNormal* ins){
  if(ins->patInfo->addrStrideMap.size() > 5){
    return nullptr;   //too many if statement
  }

  //check validity
  for(auto it : ins->patInfo->addrStrideMap){
    if(it.second.size() != 1){
      return nullptr;
    }
  }

  //fits!!
  return new PatternSmallTile(ins);
}

string PatternSmallTile::genHeader(UINT32 indent) const {
  stringstream ss;
  if(ins->patInfo->addrStrideMap.size() == 1){
    ss << _tab(indent) << "uint64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] << ";\n";
  }
  else{
    ss << _tab(indent) << "uint64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] << ", strd_" << ins->id << " = 0;\n";
  }
  return ss.str();
}

string PatternSmallTile::genBody(UINT32 indent) const {
  stringstream ss;
  if(ins->patInfo->addrStrideMap.size() == 1){
    ss << ins->printReadWrite(indent, true);
    auto it = ins->patInfo->addrStrideMap.begin();
    ss << _tab(indent) << "addr_" << ins->id << " += " << *(it->second.begin()) << ";\n";
  }
  else{
    ss << ins->printReadWrite(indent, true);
    ss << _tab(indent) << "switch(addr_" << ins->id << ") {\n";
    for(auto it : ins->patInfo->addrStrideMap){
      ss << _tab(indent+1) << "case " << it.first << " : strd_" << ins->id << " = " << *(it.second.begin()) << "; break;\n";
    }
    //ss << _tab(indent+1) << "default : strd_" << ins->id << " = 0;\n";
    ss << _tab(indent) << "}\n";
    ss << _tab(indent) << "addr_" << ins->id << " += strd_" << ins->id << ";\n";
  }
  return ss.str();
}

string PatternSmallTile::printPattern() const {
  stringstream ss;
  ss << "SmallTile" << ins->patInfo->addrStrideMap.size();
  return ss.str();
}
