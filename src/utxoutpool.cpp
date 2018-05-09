#include "utxoutpool.h"

using namespace std;

UnspentTxOutPool:: UnspentTxOutPool() : uTxOuts_{map<string, vector<UnspentTxOut>>{}}
  {}

UnspentTxOut* UnspentTxOutPool:: FindFromIn(const TxIn& input) const{
  UnspentTxOut* outptr = nullptr;
  for(auto it: uTxOuts_) {
    /*std::string x, y;
    x = out.txOutId_;
    y = input.GetId();
    size_t a = out.txOutIndex_, b = input.GetIndex();*/
    for(auto out: it.second)
      if (out.txOutId_ == input.GetId() && out.txOutIndex_ == input.GetIndex()){
        outptr = &out;
        break;
      }
  }
  return outptr;
}

// returns true on successful insert, false if UtxOut already exists
bool UnspentTxOutPool:: insert(UnspentTxOut& input){

  string address = input.GetAddress();

  auto search = uTxOuts_.find(address);

  if(search != uTxOuts_.end()) {
    uTxOuts_[address].push_back(input);
    return true;
  }

  vector<UnspentTxOut> uTxs{input};
  auto res = uTxOuts_.insert(
    pair<string, vector<UnspentTxOut> >(address, uTxs)
  );
  return res.second;
}

double UnspentTxOutPool:: balance(const string& publicKey) const {

  auto search = uTxOuts_.find(publicKey);

  // if address is found in pool, sum all UnspentTxOut
  if(search != uTxOuts_.end()) {
    double sum = 0.0;
    for(auto uTx: search->second)
      sum += uTx.GetAmount();
    return sum;
  }

  return -1.0;
}

std::vector<UnspentTxOut>* UnspentTxOutPool::operator[] (std::string& address) {
  auto search = uTxOuts_.find(address);

  if(search != uTxOuts_.end()) {
    return &search->second;
  }

  return nullptr;
}

std::ostream& operator<<(std::ostream& os, const UnspentTxOutPool& pool){
  cout << "--------------------------------------------------------------------" << endl;
  for(auto it = pool.uTxOuts_.begin(); it!=pool.uTxOuts_.end(); it++)
  {
    double amt = 0.0;
    for(auto utx : it->second)
      amt += utx.GetAmount();

    cout << "Address: " << it->first << "\tAmount: " << amt << endl;
    cout << "--------------------------------------------------------------------" << endl;
  }
  return os;
}
