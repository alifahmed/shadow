#include "cln_types.h"
#include "cln_utils.h"

using namespace std;

namespace cln_utils{

string printHash(){
  return "hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);\n";
}

}
