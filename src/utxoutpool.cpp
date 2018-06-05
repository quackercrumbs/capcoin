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

void UnspentTxOutPool:: RemoveTxIns(const vector<TxIn>& txIns, const string& address) {
  auto search = uTxOuts_.find(address);

  if(search == uTxOuts_.end())
    return;

  map<string, size_t> toRemove;

  for(auto tx: txIns)
    toRemove.insert( make_pair<string, size_t>(tx.GetId(), tx.GetIndex()) );

  vector<UnspentTxOut> tempUTxOs = uTxOuts_[address];
  vector<UnspentTxOut> newUTxOs{};

  for(auto tx: tempUTxOs) {
    auto search = toRemove.find(tx.GetId());
    if(search != toRemove.end() && search->second == tx.GetIndex())
      continue;
    newUTxOs.push_back(tx);
  }

  uTxOuts_.erase(address);
  uTxOuts_[address] = newUTxOs;

}

void UnspentTxOutPool:: AddTxOuts(const vector<TxOut>& txOuts, const string& hash) {

  for(auto out: txOuts) {
    UnspentTxOut utxo(hash, out.GetAddress(), ++index_, out.GetAmount());
    insert(utxo);
  }

}

bool UnspentTxOutPool:: AddTxn(const Transaction& txn) {
  if(!txn.Validate(this)){
      cerr<< "error: invalid transaction" << endl;
     return false;

   }
  //  cout << "validated!!!" << endl;

  // by convention
  string address = txn.GetTxOuts().back().GetAddress();

  // Remove txIns_

  RemoveTxIns(txn.GetTxIns(), address);

  // Add txOuts_

  AddTxOuts(txn.GetTxOuts(), txn.hash());

  return true;
}

void UnspentTxOutPool:: UndoTxn(const Transaction& t){
  string address = t.GetTxOuts().back().GetAddress();
  string hash = t.hash();

  double amountSpent = 0.0;
  // remove a utxo for every txout
  for(auto out: t.GetTxOuts()){
    remove(address, hash);
    amountSpent += out.GetAmount();
  }

  double interval = amountSpent / t.GetTxIns().size();
  double amountLeft = amountSpent;

  int i=0;
  size_t noTxIns = t.GetTxIns().size();
  for(auto in: t.GetTxIns()){
    UnspentTxOut u(hash, address, in.GetIndex(), ((++i) == noTxIns) ? amountLeft : interval );
    insert(u);
    amountLeft -= interval;
  }
}

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
  uTxOuts_.insert(
    pair<string, vector<UnspentTxOut> >(address, uTxs)
  );
  if(input.GetIndex() > index_)
    index_ = input.GetIndex();
  return true;
}

bool UnspentTxOutPool:: remove(string& address, string& id) {
  auto search = uTxOuts_.find(address);

  if(search == uTxOuts_.end())
    return false;

  vector<UnspentTxOut> tempUTxOs = uTxOuts_[address];

  for(auto it = tempUTxOs.begin(); it!=tempUTxOs.end(); it++) {
    if(it->GetId() == id) {
      tempUTxOs.erase(it);
      break;
    }
  }

  uTxOuts_.erase(address);
  uTxOuts_[address] = tempUTxOs;

  return true;
}

bool UnspentTxOutPool:: pop(string& address) {
  auto search = uTxOuts_.find(address);

  if(search == uTxOuts_.end())
    return false;

  vector<UnspentTxOut> tempUTxOs = uTxOuts_[address];
  tempUTxOs.pop_back();
  uTxOuts_.erase(address);
  uTxOuts_[address] = tempUTxOs;

  return true;
}

double UnspentTxOutPool:: balance(const string& address) const {

  auto search = uTxOuts_.find(address);

  // if address is found in pool, sum all UnspentTxOut
  if(search != uTxOuts_.end()) {
    double sum = 0.0;
    for(auto uTx: search->second)
      sum += uTx.GetAmount();
    return sum;
  }

  return 0.0;
}

size_t UnspentTxOutPool:: GetIndex() const {
  return index_;
}

size_t UnspentTxOutPool:: size() const {
  return uTxOuts_.size();
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
