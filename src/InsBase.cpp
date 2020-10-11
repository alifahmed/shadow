#include <vector>
#include "InsBase.h"

using namespace std;

std::vector<InsBase*> InsBase::insList;

InsBase::InsBase(InsType _type, UINT64 _id) : id(_id), type(_type){
  insList.push_back(this);
}

void InsBase::deleteAll(){
  for(InsBase* ins : insList){
    delete ins;
  }
}
