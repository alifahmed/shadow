#include <InsLoop.h>
#include <InsMem.h>
#include "PatternDominant.h"
#include "cln_utils.h"

using namespace std;
using namespace cln_utils;

PatternDominant* PatternDominant::create(const InsMem* ins){
  for(const auto &it : ins->strideDist){
    if(it.second * ins->accSz > ins->totalSz * 0.8){
      //found dominant stride
      int cnt = 0;
      for(const auto &li : ins->loops){
        if(li.lp){
          cnt++;
        }
        else{
          break;
        }
      }

      if(cnt == 0){ //no repeats
        return new PatternDominant(ins, it.first, "Dom");
      }

      //has repeat
      stringstream ss;
      ss << "addr_" << ins->id << " = " << encodeVAddr(ins->addr[0]);   //base address
      for(const auto &li : ins->loops){
        if(li.lp){
          if(li.m){
            ss << " + (loop" << li.lp->id << "*" << li.m << "LL)";
          }
        }
        else{
          break;
        }
      }
      ss << ";\n";
      ins->loops[cnt-1].lp->postfix.push_back(ss.str());
      return new PatternDominant(ins, it.first, "DomRep");
    }
  }
  return nullptr;
}

string PatternDominant::genHeader(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "int64_t addr_" << ins->id << " = " << encodeVAddr(ins->addr[0]) << ";\n";
  return ss.str();
}

string PatternDominant::genBody(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "//Dominant stride\n";
  ss << ins->printReadWrite(indent, true);
  ss << _tab(indent) << "addr_" << ins->id << " += " << domStride << "LL;\n";   // increment by stride
  // enforce address range
  if(domStride > 0){
    ss << _tab(indent) << "if(addr_" << ins->id << " >= " << encodeVAddr(ins->maxAddr) <<
          ") addr_" << ins->id << " = " << encodeVAddr(ins->minAddr) << ";\n";
  }
  else if(domStride < 0){
    ss << _tab(indent) << "if(addr_" << ins->id << " < " << encodeVAddr(ins->minAddr) <<
          ") addr_" << ins->id << " = " << encodeVAddr(ins->maxAddr - ins->accSz) << ";\n";
  }
  return ss.str();
}

string PatternDominant::printPattern() const {
  stringstream ss;
  ss << patStr << ":" << domStride;
  return ss.str();
}
