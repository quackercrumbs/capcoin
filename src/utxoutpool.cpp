#include "utxoutpool.h"

UnspentTxOutPool:: UnspentTxOutPool(){}

UnspentTxOut* UnspentTxOutPool:: FindFromIn(const TxIn& input) const{
  UnspentTxOut* outptr = nullptr;
  for(UnspentTxOut out: uTxOuts_){
    /*std::string x, y;
    x = out.txOutId_;
    y = input.GetId();
    size_t a = out.txOutIndex_, b = input.GetIndex();*/
    if (out.txOutId_ == input.GetId() && out.txOutIndex_ == input.GetIndex()){
      outptr = &out;
      break;
    }
  }
  return outptr;
}

bool UnspentTxOutPool:: AddTxn(UnspentTxOut& input){
  uTxOuts_.push_back(input);
  return true;
}
