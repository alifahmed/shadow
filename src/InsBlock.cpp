#include "InsBlock.h"
#include "InsBase.h"

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


  //too many edges.. for now, skip...
  out << _tab(indent) << "//Many edges... print first few...\n";
  for (int i = 0; i < 10; i++){
    out << _tab(indent) << "blk_" << outEdgesStack[i].first->id << " : " << outEdgesStack[i].second << "\n";
  }
  out << endl;

  //remove last edge
//  InsBlock* endBlock = outEdgesStack.back().first;
//  outEdgesStack.pop_back();
//
//
//
//  typedef struct{
//    float total = 0;
//    float cnt = 0;
//    vector< pair<const InsBlock*, UINT64> > nextBlks;
//  } BlkInfo;
//
//  vector<const InsBlock*> jumpSeq;
//  set<const InsBlock*> seenOut;
//
//  //get count of each out block
//  //also, get jump sequence
//  const InsBlock* lastBlock = NULL;
//  map<const InsBlock*,  BlkInfo> outInfo;
//  for(const auto it : outEdgesStack){
//    const InsBlock* ob = it.first;
//    outInfo[ob].total += it.second;
//    outInfo[ob].cnt++;
//
//    if(lastBlock){
//      if(outInfo[lastBlock].nextBlks.size() == 0){
//        outInfo[lastBlock].nextBlks.push_back({ob, it.second});
//      }
//      else if(outInfo[lastBlock].nextBlks.back().first != ob){
//        outInfo[lastBlock].nextBlks.push_back({ob, it.second});
//      }
//      else{
//        outInfo[lastBlock].nextBlks.back().second += it.second;
//      }
//    }
//    lastBlock = ob;
//
//    if(seenOut.find(ob) == seenOut.end()){
//      jumpSeq.push_back(ob);
//      seenOut.insert(ob);
//    }
//
//  }
//
//
//  for(const InsBlock* it : jumpSeq){
//    BlkInfo tmp = outInfo[it];
//    out << _tab(indent) << "//block" << it->id << " tol: " << tmp.total << "   cnt: " << tmp.cnt << "    avg: " << tmp.total / tmp.cnt << "  ";
//    for(auto s : tmp.nextBlks){
//      out << ", {" << s.first->id << ": " << s.second << "}";
//    }
//    out << "\n";
//  }
//
//  if (jumpSeq.size() == 2){
//    //special case
//
//  }
//
//
//
//  out << _tab(indent) << "static uint64_t out_" << id << " = 0;\n";
//  out << _tab(indent) << "out_" << id << "++;\n";
//  UINT64 total = 0;
//  UINT64 sz = outEdgesStack.size();
//  for(UINT64 i = 0; i < sz; i++){
//    total += outEdgesStack[i].second;
//    out << _tab(indent);
//    if(i){
//      out << "else ";
//    }
//    if(i != (sz - 1)){
//      out << "if (out_" << id << " <= " << total << ") ";
//    }
//    out << "goto block" << outEdgesStack[i].first->id << ";\n";
//  }
//  out << _tab(indent) << "goto block" << endBlock->id << "\n\n";

  return out.str();
}

void InsBlock::setParentLoop(InsLoopBase* pl){
  for(InsBase* i : ins){
    i->setParentLoop(pl);
  }
}


