#include <InsMem.h>
#include "PatternSmallTile.h"
#include "cln_utils.h"

using namespace std;
using namespace cln_utils;

PatternSmallTile* PatternSmallTile::create(const InsMem* ins){
  if(ins->addrStrideMap.size() > MAX_SMALL_TILES){
    return nullptr;   //too many stride change points
  }

  //check validity
  for(auto it : ins->addrStrideMap){
    if(it.second == 0xDEADBEAF){
      return nullptr;
    }
  }

  //fits!!
  return new PatternSmallTile(ins);
}

string PatternSmallTile::genHeader(UINT32 indent) const {
  stringstream ss;
  if(ins->addrStrideMap.size() == 1){
    ss << _tab(indent) << "int64_t addr_" << ins->id << " = " << encodeVAddr(ins->addr[0]) << ";\n";
  }
  else{
    ss << _tab(indent) << "int64_t addr_" << ins->id << " = " << encodeVAddr(ins->addr[0]) << ", strd_" << ins->id << " = 0;\n";
  }
  return ss.str();
}

string PatternSmallTile::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "//Small tile\n";
  if(ins->addrStrideMap.size() == 1){
    ss << ins->printReadWrite(indent, true);
    ss << _tab(indent) << "addr_" << ins->id << " += " << ins->addrStrideMap.begin()->second << "LL;\n";
  }
  else{
    ss << ins->printReadWrite(indent, true);
    ss << _tab(indent) << "switch(addr_" << ins->id << ") {\n";
    for(auto it : ins->addrStrideMap){
      ss << _tab(indent+1) << "case " << encodeVAddr(it.first) << " : strd_" << ins->id << " = " << it.second << "LL; break;\n";
    }
    //ss << _tab(indent+1) << "default : strd_" << ins->id << " = 0;\n";
    ss << _tab(indent) << "}\n";
    ss << _tab(indent) << "addr_" << ins->id << " += strd_" << ins->id << ";\n";
  }
  return ss.str();
}

string PatternSmallTile::printPattern() const {
  stringstream ss;
  ss << "SmallTile" << ins->addrStrideMap.size();
  return ss.str();
}
