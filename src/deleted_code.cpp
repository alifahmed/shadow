

/*******************************************************************************
 * Pattern Refs
 ******************************************************************************/
/*class PatternRefs : public PatternBase{
  typedef struct {
    INT64 stride;
    ADDRINT offset;
    ADDRINT mod;
  } StrideInfo;

private:
  PatternRefs();
  PatternRefs(const InsNormal* _ins, vector<StrideInfo> &infoList, UINT64 _maxHop) : PatternBase(_ins, PatType::PatTypeRefs), maxHop(_maxHop){
    this->strideInfoList = infoList;
  }
  vector<StrideInfo> strideInfoList;
  UINT64 maxHop = 0;

public:
  static PatternRefs* create(const InsNormal* ins){
    const auto &strideRefs = ins->patInfo->strideRef;

    vector<StrideInfo> infoList;

    UINT64 maxHop = 1;
    for(auto sset : strideRefs){
      const INT64 stride = sset.first;
      set<ADDRINT> &refs = sset.second;
      if(refs.size() == 1) {
        StrideInfo info;
        info.stride = stride;
        info.mod = -1;
        info.offset = 0;
        infoList.push_back(info);
        continue;
      }

      UINT64 hop = numMod(refs);
      if(hop > maxHop){
        maxHop = hop;
      }
      if(maxHop > 20){
        return nullptr;
      }
    }
    return new PatternRefs(ins, infoList, maxHop);
  }

  void shiftAddress(INT64 offset){
    for(auto &it : strideInfoList){
      it.offset += offset;
    }
  }

  string printPattern(){
    stringstream ss;
    ss << "Refs: " << maxHop;
    return ss.str();
  }
};*/



/*******************************************************************************
 * Pattern Tile
 ******************************************************************************/
/*class PatternTile : public PatternBase{
  typedef struct {
    INT64 stride;
    ADDRINT offset;
    ADDRINT mod;
  } StrideInfo;

private:
  PatternTile();
  PatternTile(const InsNormal* _ins, vector<StrideInfo> &infoList, UINT64 _maxHop) : PatternBase(_ins, PatType::PatTypeTile), maxHop(_maxHop){
    this->strideInfoList = infoList;
  }
  vector<StrideInfo> strideInfoList;
  UINT64 maxHop;

public:
  static PatternTile* create(const InsNormal* ins){
    const auto &strideAddr = ins->patInfo->strideAddr;

    set<ADDRINT> unionSet;
    UINT64 totPoints = 0;
    for(auto it : strideAddr){
      totPoints += it.second.size();
      unionSet.insert(it.second.begin(), it.second.end());
    }
    if(totPoints != unionSet.size()){
      return nullptr;   //different stride at same address
    }

    vector<StrideInfo> infoList;

    UINT64 maxHop = 1;
    for(auto sset : strideAddr){
      const INT64 stride = sset.first;
      set<ADDRINT> &addr = sset.second;
      if(addr.size() == 1) {
        StrideInfo info;
        info.stride = stride;
        info.mod = -1;
        info.offset = 0;
        infoList.push_back(info);
        continue;
      }

      UINT64 hop = numMod(addr);
      if(hop > maxHop){
        maxHop = hop;
      }
      if(maxHop > 20){
        return nullptr;
      }
    }
    return new PatternTile(ins, infoList, maxHop);
  }

  void shiftAddress(INT64 offset){
    for(auto &it : strideInfoList){
      it.offset += offset;
    }
  }

  string printPattern(){
    stringstream ss;
    ss << "Tile: " << maxHop;
    return ss.str();
  }
};*/



//check if a=>b can form a loop
/*bool isConvLoop(set<InsBlock*> &cfg, InsBlock* root, InsBlock* a, InsBlock* b){



  //do some trivial checks
  if(a->inEdges.size() != 2) return false;
  if(b->outEdges.size() != 2) return false;
  if(a->inEdges.find(b) == a->inEdges.end()) return false;
  if(b->outEdges.find(a) == b->outEdges.end()) return false;

  InsBlock* s = nullptr;
  InsBlock* e = nullptr;
  for(InsBlock* aa : a->inEdges){
    if(aa != b){
      s = aa;
    }
  }
  for(InsBlock* bb : b->outEdges){
    if(bb != a){
      e = bb;
    }
  }

  if(a == b){
    //determine loop count
    UINT64 k = 0;
    UINT64 m = 0;
    for(auto it : b->outEdgesStack){
      if(it.first == a){
        m += it.second;
      }
      else{
        k += it.second;
      }
    }
    m += k;
    if(m % k) {
      return false;   //not divisable
    }
    m = m / k;  //m is now loop count

    //create replacement block
    InsBlock* r = new InsBlock();
    blockList.push_back(r);
    r->id = __blockId++;
    r->outEdges.insert(e);
    r->outEdgesStack.push_back({e,k});
    r->inEdges.insert(s);

    //create loop instruction
    InsLoop* lp = new InsLoop();
    baseList.push_back(lp);
    lp->id = __loopId++;
    lp->loopCnt = m;
    lp->cfg.insert(a);

    //add lp to r
    r->ins.push_back(lp);

    //at this point, r and lp are done

    //fix s
    s->outEdges.erase(a);
    s->outEdges.insert(r);
    for(auto &it : s->outEdgesStack){
      if(it.first == a){
        it.first = r;
      }
    }

    //fix e
    e->inEdges.erase(b);
    e->inEdges.insert(r);

    //fix a & b
    a->inEdges.clear();
    b->outEdges.clear();
    b->outEdgesStack.clear();

    //fix incoming cfg
    cfg.erase(a);
    cfg.insert(r);

    return true;
  }

  //a and b are different
  set<InsBlock*> visitedByRoot;
  set<InsBlock*> visitedByA;

  s->outEdges.erase(a);
  colorCFG(root, visitedByRoot);
  colorCFG(e, visitedByRoot);
  s->outEdges.insert(a);


  visitedByA.insert(b);
  colorCFG(a, visitedByA);

  vector<InsBlock*> overlap;
  overlap.reserve(max(visitedByA.size(), visitedByRoot.size()));
  vector<InsBlock*>::iterator oit;
  oit = set_intersection(visitedByA.begin(), visitedByA.end(), visitedByRoot.begin(), visitedByRoot.end(), overlap.begin());
  if(oit != overlap.begin()){ //has overlap
    return false;
  }

  //determine loop count
  UINT64 k = 0;
  UINT64 m = 0;
  for(auto it : b->outEdgesStack){
    if(it.first == a){
      m += it.second;
    }
    else{
      k += it.second;
    }
  }
  m += k;
  if(m % k) {
    return false;   //not divisable
  }
  m = m / k;  //m is now loop count

  //create replacement block
  InsBlock* r = new InsBlock();
  blockList.push_back(r);
  r->id = __blockId++;
  r->outEdges.insert(e);
  r->outEdgesStack.push_back({e,k});
  r->inEdges.insert(s);

  //create loop instruction
  InsLoop* lp = new InsLoop();
  baseList.push_back(lp);
  lp->id = __loopId++;
  lp->loopCnt = m;
  lp->cfg = visitedByA;

  //add lp to r
  r->ins.push_back(lp);

  //at this point, r and lp are done

  //fix s
  s->outEdges.erase(a);
  s->outEdges.insert(r);
  for(auto &it : s->outEdgesStack){
    if(it.first == a){
      it.first = r;
    }
  }

  //fix e
  e->inEdges.erase(b);
  e->inEdges.insert(r);

  //fix a & b
  a->inEdges.clear();
  b->outEdges.clear();
  b->outEdgesStack.clear();

  //fix incoming cfg
  cfg = visitedByRoot;
  cfg.insert(r);

  //compress new CFG
  compressCFG(lp->cfg);

  return true;
}*/

/*
bool compressLoop(set<InsBlock*> &cfg){
  bool isChanged = false;
  for(InsBlock* blk : cfg){
    if(blk->outEdgesStack.size() < 2) continue;
    if(!(blk->outEdgesStack.size() % 2)){
      bool isLoop = true;
      uint64_t pred_iter = blk->outEdgesStack[0].second;
      for(uint64_t i = 0; i < blk->outEdgesStack.size(); i++){
        if(!(i % 2)){
          //even index
          if((blk->outEdgesStack[i].second != pred_iter) || (blk->outEdgesStack[i].first != blk)){
            isLoop = false;
            break;
          }
        }
        else{
          //odd index
          if(blk->outEdgesStack[i].second != 1){
            isLoop = false;
            break;
          }
        }
      }
      if(isLoop){
        //fix out edges
        vector< pair<InsBlock*, UINT64> > old_edges = blk->outEdgesStack;
        blk->outEdgesStack.clear();
        blk->outEdgesStack.push_back({old_edges[1].first, 0});
        for(auto it : old_edges){
          InsBlock* nextBlk = it.first;
          if(nextBlk != blk){
            if(blk->outEdgesStack.back().first == nextBlk){
              blk->outEdgesStack.back().second++;
            }
            else{
              blk->outEdgesStack.push_back({nextBlk, 1});
            }
          }
        }

        InsLoop* loop = new InsLoop();
        baseList.push_back(loop);

        static UINT64 loopId = 0;
        loop->loopCnt = pred_iter + 1;
        loop->ins = blk->ins;    //copy
        loop->id = loopId++;
        blk->ins.clear();

        blk->ins.push_back(loop);
        blk->inEdges.erase(blk);
        blk->outEdges.erase(blk);
        for(InsBase* bs : loop->ins){
          bs->parentLoop = loop;
        }
        isChanged = true;
      }
    }
  }
  return isChanged;
}*/


/*bool numModFixedHop(const set<ADDRINT> &num, UINT64 hop){
  UINT64 maxSz = num.size();
  UINT64 diff[hop];
  UINT64 prev[hop];
  for(UINT64 i = 0; i < hop; i++){
    diff[i] = 0xFFFFFFFFFFFFFFFFULL;
    prev[i] = 0xFFFFFFFFFFFFFFFFULL;
  }

  auto it = num.begin();
  for(UINT64 i = 0; i < maxSz; i++){
    UINT64 idx = i % hop;
    UINT64 c = *it++;
    UINT64 p = prev[idx];
    prev[idx] = c;
    if(p != 0xFFFFFFFFFFFFFFFFULL){
      if(diff[idx] == 0xFFFFFFFFFFFFFFFFULL){
        diff[idx] = c - p;
        continue;
      }
      if((c - p) != diff[idx]){
        return false;
      }
    }
  }
  return true;
}

UINT64 numMod(const set<ADDRINT> &num){
  if(num.size() < 3) return 1;
  for(int hop = 1; hop < 5; hop++){
    if(numModFixedHop(num, hop)){
      return hop;
    }
  }
  return 10000;
}*/


//void printInsLabel(ofstream &out, const vector<InsBase*> &insts, UINT32 indent, stack<set<InsBlock*>> &cfgStack){
//  for(InsBase* it : insts){
//    //if(!firstLine){
//      out << "<br />";
//    //}
//    firstLine = false;
//    for(UINT32 i = 0; i < indent; i++){
//      out << "  ";
//    }
//    it->printDot(out, indent);
//    if(it->type == InsType::InsTypeNormal){
//      /*InsNormal* ins = it->insNormal;
//      out << setw(4) << ins->id << ":";
//      if(ins->accType == AccessType::AccessTypeRead){
//        out << "RD ";
//      }
//      else if(ins->accType == AccessType::AccessTypeWrite){
//        out << "WR ";
//      }
//      out << ins->patInfo->pat->printPattern();
//      out << " A" << ins->accSz << " [" << ins->patInfo->addrRange.s << ":" << ins->patInfo->addrRange.e << ")";*/
//      InsNormal* ins = static_cast<InsNormal*>(it);
//      out << ins->id << ": ";
//      out << ins->hashedRoot->root->srcLine;// << ", " << ins->patInfo->pat->printPattern();
//    }
//    else if(it->type == InsType::InsTypeLoop){
//      InsLoop* loop = static_cast<InsLoop*>(it);
//      InsBlock* s;
//      InsBlock* e;
//      findCFGStartEnd(loop->cfg, &s, &e);
//      out << "loop" << loop->id << ": " << loop->loopCnt << " Block: " << s->id;
//      cfgStack.push(loop->cfg);
//      //printInsLabel(out, loop->ins, indent+1);
//    }
//  }
//}

/*void printDotCFG(ofstream &out, const set<InsBlock*> &cfg, stack<set<InsBlock*>> &cfgStack){
  for(InsBlock* ib : cfg){
    if(ib->id == 0) {
      out << "\tB0 [label=\"START\",fillcolor=yellow,style=filled];\n";
    }
    else if(ib->id == 1) {
      out << "\tB1 [label=\"END\",fillcolor=yellow,style=filled];\n";
    }
    else {
      out << "\tB" << ib->id << " [shape=plain, fontname=\"Courier\", label=< <table>";
      out << "<TR><TD balign=\"left\" border=\"0\">";
      firstLine = true;
      out << "Block: " << ib->id;
      printInsLabel(out, ib->ins, 0, cfgStack);
      out << "</TD></TR> </table> >];\n";
    }
    map<InsBlock*, UINT64> outBlocks;
    for(auto it : ib->outEdgesStack){
      outBlocks[it.first] += it.second;
    }

    for(auto it : outBlocks){
      InsBlock* o = it.first;
      out << "\tB" << ib->id;// << ":o" << cnt;
      out << " -> B" << o->id;// << ":i";
      out << " [label=\"" << it.second << "\"];\n";
    }
  }
}*/
