#include "utxoutpool.h"

using namespace std;

UnspentTxOutPool:: UnspentTxOutPool() : uTxOuts_{map<string, vector<UnspentTxOut>>{}}, index_{0}
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
        return outptr;
      }
  }
  return outptr;
}

string UnspentTxOutPool:: GetHash(const TxIn& input) const{
  string s;
  for(auto it: uTxOuts_) {
    /*std::string x, y;
    x = out.txOutId_;
    y = input.GetId();
    size_t a = out.txOutIndex_, b = input.GetIndex();*/
    for(auto out: it.second)
      if (out.txOutId_ == input.GetId() && out.txOutIndex_ == input.GetIndex()){
        return out.Hash();
      }
  }
  return s;
}

void UnspentTxOutPool:: RemoveFromIn(const TxIn& in, string& address) {

  // this function almost ruined my life.
  // don't try to erase from the vector.

  auto search = uTxOuts_.find(address);

  if(search != uTxOuts_.end()) {

    vector<UnspentTxOut> tempUTxOs = uTxOuts_[address];
    vector<UnspentTxOut> newUTxOs{};
    for(int i=0; i<tempUTxOs.size(); i++){
      UnspentTxOut u{*(tempUTxOs.begin() + i)};
      if(u.GetId() == in.GetId() && u.GetIndex() == in.GetIndex()){
        // uTxOuts_[address].erase(tempUTxOs.begin() + i);
        // break;
        continue;
      }
      newUTxOs.push_back(u);
    }
    // tempUTxOs = uTxOuts_[address];
    uTxOuts_.erase(address);
    uTxOuts_[address] = newUTxOs;
  }
}

bool UnspentTxOutPool:: AddTxn(const Transaction& txn) {
  if(!txn.Validate(*this)){
      cerr<< "error: invalid transaction" << endl;
     return false;

   }
  //  cout << "validated!!!" << endl;


  // by convention
  string address = txn.GetTxOuts().back().GetAddress();

  for(auto& in: txn.GetTxIns())
    RemoveFromIn(in, address);

  stringstream ss;
  int i=0;
  for(auto out: txn.GetTxOuts()) {
    ss.str("");
    ss << txn.hash() << i++;
    string newId = picosha2::hash256_hex_string(ss.str());
    UnspentTxOut utxo(newId, out.GetAddress(), ++index_, out.GetAmount());
    insert(utxo);
  }

  return true;
}

// returns true on successful insert, false if UtxOut already exists
bool UnspentTxOutPool:: insert(UnspentTxOut& input){

  string address = input.GetAddress();

  auto search = uTxOuts_.find(address);

  if(search != uTxOuts_.end()) {
    uTxOuts_[address].push_back(input);
    if(input.GetIndex() > index_)
      index_ = input.GetIndex();
    return true;
  }

  vector<UnspentTxOut> uTxs{input};
  auto res = uTxOuts_.insert(
    pair<string, vector<UnspentTxOut> >(address, uTxs)
  );
  if(!res.second && input.GetIndex() > index_)
    index_ = input.GetIndex();
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
