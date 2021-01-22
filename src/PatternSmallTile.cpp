#include <InsMem.h>
#include "PatternSmallTile.h"
#include "PatternInfo.h"

using namespace std;

PatternSmallTile* PatternSmallTile::create(const InsMem* ins){
  if(ins->patInfo->addrStrideMap.size() > MAX_SMALL_TILES){
    return nullptr;   //too many stride change points
  }

  //check validity
  for(auto it : ins->patInfo->addrStrideMap){
    if(it.second == -1){
      return nullptr;
    }
  }

  //fits!!
  return new PatternSmallTile(ins);
}

string PatternSmallTile::genHeader(UINT32 indent) const {
  stringstream ss;
  if(ins->patInfo->addrStrideMap.size() == 1){
    ss << _tab(indent) << "int64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] - ins->patInfo->gap << ";\n";
  }
  else{
    ss << _tab(indent) << "int64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] - ins->patInfo->gap << ", strd_" << ins->id << " = 0;\n";
  }
  return ss.str();
}

string PatternSmallTile::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "//Small tile\n";
  if(ins->patInfo->addrStrideMap.size() == 1){
    ss << ins->printReadWrite(indent, true);
    ss << _tab(indent) << "addr_" << ins->id << " += " << ins->patInfo->addrStrideMap.begin()->second << ";\n";
  }
  else{
    ss << ins->printReadWrite(indent, true);
    ss << _tab(indent) << "switch(addr_" << ins->id << ") {\n";
    for(auto it : ins->patInfo->addrStrideMap){
      ss << _tab(indent+1) << "case " << it.first - ins->patInfo->gap << " : strd_" << ins->id << " = " << it.second << "; break;\n";
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
