#include <map>
#include "InsBlock.h"
#include "InsBase.h"
#include "cln_utils.h"

using namespace std;

std::vector<InsBlock*> InsBlock::blockList;
UINT64 InsBlock::_idCnt = 2;

InsBlock::InsBlock(){
  blockList.push_back(this);
  this->id = _idCnt++;
}

InsBlock::InsBlock(UINT64 id){
  blockList.push_back(this);
  this->id = id;
}

bool InsBlock::isOutOrderConst(std::vector<InsBlock*> &order) const {
  size_t outBlockCnt = outEdges.size();
  if(outEdgesStack.size() % outBlockCnt) return false;    //total elements in the out stack is not a multiple of out blocks

  order.clear();
  order.resize(outBlockCnt, nullptr);

  size_t idx = 0;
  for(auto it : outEdgesStack){
    if(order[idx] == nullptr){
      order[idx] = it.first;
    }
    else if(order[idx] != it.first){
      return false;
    }
    idx++;
    idx %= outBlockCnt;
  }
  return true;
}


map<InsBlock*, InsBlock::EdgeStat> InsBlock::calcEdgeStats() const {
  map<InsBlock*, EdgeStat> aa;
  for(auto it : outEdgesStack){
    aa[it.first].totCnt += it.second;
    aa[it.first].entryCnt++;
  }
  for(auto &it : aa) {
    UINT64 tot = it.second.totCnt;
    it.second.avgCnt = tot / it.second.entryCnt;
    it.second.remCnt = tot % it.second.entryCnt;
  }
  return aa;
}


string InsBlock::printDot(UINT32 indent) const {
    if(isUsed){
      stringstream ss;
      if(id == 0) {   //special case: start block
        ss << "\tB0 [label=\"START\",fillcolor=yellow,style=filled];\n";
      }
      else if(id == 1) {   //special case: end block
        ss << "\tB1 [label=\"END\",fillcolor=yellow,style=filled];\n";
      }
      else{
        //draw table start
        ss << "\tB" << id << " [shape=plain, fontname=\"Courier\", label=< <table>";
        ss << "<TR><TD balign=\"left\" border=\"0\">";
        ss << "Block: " << id;

        //draw instructions
        for(InsBase* it : ins){
          ss << it->printDot(indent);
        }

        //draw table end
        ss << "</TD></TR> </table> >];\n";
      }

      //draw outgoing edges
      map<InsBlock*, UINT64> outBlocks;
      for(auto it : outEdgesStack){
        outBlocks[it.first] += it.second;
      }

      for(auto it : outBlocks){
        InsBlock* o = it.first;
        ss << "\tB" << id;// << ":o" << cnt;
        ss << " -> B" << o->id;// << ":i";
        ss << " [label=\"" << it.second << "\"];\n";
      }

      return ss.str();
    }
    return "";
  }

UINT64 InsBlock::getId() const {
  return id;
}

void InsBlock::deleteAll(){
  for(InsBlock* blk : blockList){
    delete blk;
  }
}

string InsBlock::printDotAll(UINT32 indent) {
  stringstream ss;
  for(InsBlock* blk : blockList){
    if(blk->isUsed){
      ss << blk->printDot(indent);
    }
  }
  return ss.str();
}

UINT64 InsBlock::getNumBlocks(){
  return blockList.size();
}

std::string InsBlock::printCodeBody(UINT32 indent) const {
  stringstream out;

  out << "block" << id << ":\n";
  for(InsBase* base : ins){
    out << base->printCodeBody(indent);
  }

  if(outEdges.size() == 0){
    return out.str();
  }

  // simple if just one edge
  if(outEdgesStack.size() == 1){
    out << _tab(indent) << "goto block" << outEdgesStack[0].first->id << ";\n\n";
    return out.str();
  }


  // small number number of transitions. No need to find patterns
  if (outEdgesStack.size() < 10){
    out << _tab(indent) << "//Few edges. Don't bother optimizing\n";

    out << _tab(indent) << "static uint64_t out_" << id << " = 0;\n";
    out << _tab(indent) << "out_" << id << "++;\n";
    UINT64 total = 0;
    UINT64 sz = outEdgesStack.size();
    for(UINT64 i = 0; i < sz; i++){
      total += outEdgesStack[i].second;
      out << _tab(indent);
      if(i){
        out << "else ";
      }
      if(i != (sz - 1)){
        out << "if (out_" << id << " <= " << total << ") ";
      }
      out << "goto block" << outEdgesStack[i].first->id << ";\n";
    }
    out << "\n\n";
    return out.str();
  }


  //check order
  vector<InsBlock*> blkOrder;
  bool isOrdered = isOutOrderConst(blkOrder);
  if(isOrdered){
    out << _tab(indent) << "//Ordered...\n";
  }

  //print edge stats
  map<InsBlock*, EdgeStat> estat = calcEdgeStats();

  //check if remainder is zero for all
  bool isRemZero = true;
  for(auto it : estat){
    if(it.second.remCnt){
      isRemZero = false;
      break;
    }
  }

  //ordered, no remainder edges
  if(isOrdered && isRemZero){
    assert(estat.size() == blkOrder.size());
    UINT64 tot_cnt = 0;
    for(auto it : estat) {
      tot_cnt += it.second.avgCnt;
    }
    out << _tab(indent) <<  "static uint64_t out_" << id << " = 0;\n";
    out << _tab(indent) <<  "out_" << id << " = (out_" << id << " == " << (tot_cnt+1) << ") ? 1 : (out_" << id << " + 1);\n";
    UINT64 sz = estat.size();
    tot_cnt = 0;
    for(UINT64 i = 0; i < sz; i++){
      //get next block following the order
      InsBlock* nb = blkOrder[i];
      EdgeStat es = estat[nb];

      tot_cnt += es.avgCnt;
      out << _tab(indent);
      if(i){
        out << "else ";
      }
      if(i != (sz - 1)){
        out << "if (out_" << id << " <= " << tot_cnt << ") ";
      }
      out << "goto block" << nb->id << ";\n";
    }
    out << "\n\n";
    return out.str();
  }


  //too many edges.. for now, skip...
  out << _tab(indent) << "//Many edges... print first few...\n";
  const size_t lst_cnt = 6;
  for (size_t i = 0; i < lst_cnt; i++){
    out << _tab(indent) << "//blk_" << outEdgesStack[i].first->id << " : " << outEdgesStack[i].second << "\n";
  }
  out << _tab(indent) << "//...\n";
  out << _tab(indent) << "//...\n";
  size_t sz = outEdgesStack.size();
  for (size_t i = 0; i < lst_cnt; i++){
    out << _tab(indent) << "//blk_" << outEdgesStack[sz - lst_cnt + i].first->id << " : " << outEdgesStack[sz - lst_cnt + i].second << "\n";
  }
  //out << endl << endl;


  //Generic case. Use probability to jump to one of the out blocks.

  //get last entry from edge stack
  auto lastEntry = outEdgesStack[outEdgesStack.size()-1];

  //update estat to exclude last entry
  estat[lastEntry.first].totCnt -= lastEntry.second;

  //remove lastEntry block from estat if count becomes zero
  if(estat[lastEntry.first].totCnt == 0){
    estat.erase(lastEntry.first);
  }

  vector<InsBlock*> tmpBlks;
  for(auto it : estat){
    out << _tab(indent) << "static uint64_t out_" << id << "_" << it.first->id << " = " << it.second.totCnt << ";\n";
    tmpBlks.push_back(it.first);
  }

  //calculate total
  UINT64 cc = 0;
  out << _tab(indent) << "tmpRnd = ";
  for(auto it : estat){
    if(cc++){
      out << " + ";
    }
    out << "out_" << id << "_" << it.first->id;
  }
  out << ";\n";

  //check if total is not zero
  out << _tab(indent) << "if (tmpRnd) {\n";

  //calc hash
  out << _tab(indent+1) << cln_utils::printHash();
  out << _tab(indent+1) << "tmpRnd = hash % tmpRnd;\n";

  //add if conditions
  for(UINT64 i = 0; i < tmpBlks.size(); i++){
      out << _tab(indent+1);
      if(i){
        out << "else ";
      }
      if(i != (tmpBlks.size() -1)){
        out << "if (tmpRnd < (";
        for(UINT64 j = 0; j <= i; j++){
          if(j){
            out << " + ";
          }
          out << "out_" << id << "_" << tmpBlks[j]->id;
        }
        out << "))";
      }

      out << "{\n";
      out << _tab(indent+2) << "out_" << id << "_" << tmpBlks[i]->id << "--;\n";
      out << _tab(indent+2) << "goto block" << tmpBlks[i]->id << ";\n";
      out << _tab(indent+1) << "}\n";
    }

  //close tmpRnd != 0 check
  out << _tab(indent) << "}\n";

  //add default jump (last edge)
  out << _tab(indent) << "goto block" << lastEntry.first->id << ";\n";


  out << endl << endl;
  return out.str();
}

void InsBlock::setParentLoop(InsLoopBase* pl){
  for(InsBase* i : ins){
    i->setParentLoop(pl);
  }
}


