#include "utxoutpool.h"

using namespace std;

UnspentTxOutPool:: UnspentTxOutPool(){}

UnspentTxOut* UnspentTxOutPool:: FindFromIn(const TxIn& input) const{
  UnspentTxOut* outptr = nullptr;
  // for(UnspentTxOut out: uTxOuts_){
  //   /*std::string x, y;
  //   x = out.txOutId_;
  //   y = input.GetId();
  //   size_t a = out.txOutIndex_, b = input.GetIndex();*/
  //   if (out.txOutId_ == input.GetId() && out.txOutIndex_ == input.GetIndex()){
  //     outptr = &out;
  //     break;
  //   }
  // }
  return outptr;
}

// returns true on successful insert, false if UtxOut already exists
bool UnspentTxOutPool:: AddTxn(UnspentTxOut& input){

  // auto res = uTxOuts_.insert( pair<string, UnspentTxOut>(input.GetAddress(), input) );
  // return res.second;
  return false;
}

std::ostream& operator<<(std::ostream& os, const UnspentTxOutPool& pool){
  cout << "--------------------------------------------------------------------" << endl;
  // for(auto it = pool.uTxOuts_.begin(); it!=pool.uTxOuts_.end(); it++)
  // {
  //   cout << "PublicKey: " << it->first << "\t\tAmount: " << it->second.GetAmount() << endl;
  //   cout << "--------------------------------------------------------------------" << endl;
  // }
  return os;
}
