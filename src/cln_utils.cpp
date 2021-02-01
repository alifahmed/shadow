#include "cln_types.h"
#include "cln_utils.h"

using namespace std;

namespace cln_utils{

//string printHash(){
//  return "hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);\n";
//}

bool isRepeat(const std::vector<ADDRINT> &addr, size_t sz, size_t rep, INT64 &m) {
  if(rep == 1){
    m = 0;
    return true;
  }
  if (sz % rep){
    return false;
  }

  size_t elems = sz / rep;
  m = addr[elems] - addr[0];

  for (size_t i = 0; i < elems; i++) {
    ADDRINT ref = addr[i];
    for (size_t j = 1; j < rep; j++) {
      size_t idx = elems * j + i;
      if (addr[idx] != (ref + j * m)) {
        return false;
      }
    }
  }

  return true;
}

}
