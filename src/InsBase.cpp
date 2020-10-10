#include <vector>
#include "InsBase.h"

using namespace std;

InsBase::InsBase(InsType type, UINT64 id){
  this->type = type;
  this->id = id;
  insList.push_back(this);
}

void InsBase::deleteAllInst(){
  for(InsBase* ins : insList){
    delete ins;
  }
}

vector<InsBase*> InsBase::insList;
