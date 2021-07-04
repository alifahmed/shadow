#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace cln_utils{

bool isRepeat(const std::vector<ADDRINT> &addr, size_t sz, size_t rep, INT64 &m);

//std::string printHash();

std::string encodeVAddr(ADDRINT vAddr);

}
