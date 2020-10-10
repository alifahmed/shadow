#include "PatternDominant.h"
#include "InsNormal.h"
#include "PatternInfo.h"
#include "InsLoopBase.h"

using namespace std;

PatternDominant* PatternDominant::create(const InsNormal* ins){
  for(const auto &it : ins->patInfo->strideDist){
    if(it.second * ins->accSz > ins->patInfo->totalSz * 0.8){
      //found dominant stride
      int cnt = 0;
      for(const auto &li : ins->patInfo->loops){
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
      ss << "addr_" << ins->id << " = " << ins->patInfo->addr[0];   //base address
      for(const auto &li : ins->patInfo->loops){
        if(li.lp){
          if(li.m){
            ss << " + (loop" << li.lp->id << "*" << li.m << ")";
          }
        }
        else{
          break;
        }
      }
      ss << ";\n";
      ins->patInfo->loops[cnt-1].lp->extraStr.push_back(ss.str());
      return new PatternDominant(ins, it.first, "DomRep");
    }
  }
  return nullptr;
}

string PatternDominant::genHeader(UINT32 indent) const {
  stringstream ss;
  ss << _tab(indent) << "uint64_t addr_" << ins->id << " = " << ins->patInfo->addr[0] << ";\n";
  return ss.str();
}

string PatternDominant::genBody(UINT32 indent) const {
  if(domStride <= 0){
    cerr << "[ERROR] Non positive dominant stride, check." << endl;
    exit(-1);
  }
  stringstream ss;
  ss << ins->printReadWrite(indent, true);
  ss << _tab(indent) << "addr_" << ins->id << " += " << domStride << ";\n";   // increment by stride
  ss << _tab(indent) << "if(addr_" << ins->id << " >= " << ins->patInfo->addrRange.e <<
      ") addr_" << ins->id << " = " << ins->patInfo->addrRange.s << ";\n";    // enforce address range
  return ss.str();
}

string PatternDominant::printPattern() const {
  stringstream ss;
  ss << patStr << ":" << domStride;
  return ss.str();
}
