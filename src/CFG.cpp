#include <cassert>
#include "CFG.h"
#include "InsBlock.h"

using namespace std;

CFG::CFG(std::set<InsBlock*> blocks){

}

bool CFG::isElem(InsBlock* a){
  return blocks.find(a) != blocks.end();
}


bool CFG::dom(InsBlock* a, InsBlock* b){
  if(!isElem(a) || !isElem(b)) {
    return false;
  }

  if(a == b){
    return true;
  }

  return doms[b].find(a) != doms[b].end();
}



bool CFG::sdom(InsBlock* a, InsBlock* b){
  return dom(a, b) && (a != b);
}


bool CFG::idom(InsBlock* a, InsBlock* b){
  return true;
}


void CFG::domAll() {
  //make sure 's' is the starting node of CFG
  assert(isElem(s));
  assert(s->inEdges.size() == 0);

  for(InsBlock* blk : blocks){
    doms[blk] = blocks;
  }
  doms[s].clear();
  doms[s].insert(s);

  bool isChanged = true;
  while(isChanged){
    for(InsBlock* blk : blocks){
      if(blk != s){
        set<InsBlock*> D;
        for(InsBlock* p : blk->inEdges){
          if(D.size() == 0){
            D = doms[p];
          }
          else{
            set<InsBlock*> tmp;
            set_intersection(D.begin(), D.end(), doms[p].begin(), doms[p].end(), std::inserter(tmp, tmp.begin()));
            D = tmp;
          }
        }
        D.insert(blk);
        if(D != doms[blk]){
          isChanged = true;
          doms[blk] = D;
        }
      }
    }
    isChanged = false;
  }
}

bool CFG::isBackEdge(InsBlock* a, InsBlock* b){
  //check if a=>b constitutes an edge
  if(a->outEdges.find(b) == a->outEdges.end()){
    return false; //not a valid edge
  }

  return dom(b, a); //back edge if 'b' dominates 'a'
}




