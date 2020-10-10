#include "InsBlock.h"
#include "InsBase.h"

using namespace std;

string InsBlock::printDot(UINT32 indent){
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
