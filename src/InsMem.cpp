#include <InsMem.h>
#include <string>
#include <sstream>
#include "InsHashedRoot.h"
#include "InsRoot.h"
#include "PatternBase.h"

using namespace std;

string InsMem::printDot(UINT32 indent) const {
  if (isTop) {
    stringstream out;
    out << "<br />" << _tab(indent) << id << ": ";
    out << hashedRoot->root->srcLine; // << ", " << ins->patInfo->pat->printPattern();
    return out.str();
  } else {
    return "";
  }
}

string InsMem::printCodeBody(UINT32 indent) const {
  if (isTop) {
    stringstream ss;
    ss << pat->genBody(indent) << "\n";
    return ss.str();
  } else {
    return "";
  }
}

string InsMem::printReadWrite(UINT32 indent, bool useId) const {
  if (isTop) {
    stringstream ad;
    if (useId) {
      ad << "addr_" << id;
    } else {
      ad << "addr";
    }

    stringstream ss;
    if (accType == AccessType::AccessTypeRead) {
      ss << _tab(indent) << "READ_" << accSz << "b(" << ad.str() << ");\n";
    } else if (accType == AccessType::AccessTypeWrite) {
      ss << _tab(indent) << "WRITE_" << accSz << "b(" << ad.str() << ");\n";
    } else if (accType == AccessType::AccessTypeRMW) {
      ss << _tab(indent) << "RMW_" << accSz << "b(" << ad.str() << ");\n";
    } else {
      cerr << "[ERROR] Invalid access type for " << id << endl;
      return "";
    }
    return ss.str();
  } else {
    return "";
  }
}

void InsMem::setParentLoop(InsLoop *pl) {
  parentLoop = pl;
}

void InsMem::reset(){
	//InsBase
	parentLoop = nullptr;
	isTop = false;
	parentBlock = nullptr;

	//InsMem
	addr.clear();
	totalSz = 0;
	minAddr = 0xFFFFFFFFFFFFFFFFULL;
	maxAddr = 0;
	//loops.clear();
	pat = nullptr;
}

