#include "transaction.h"

Transaction::Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs): txIns_{std::move(ins)}, txOuts_{std::move(outs)}{
  id_ = CalcHash();
}

std::string Transaction:: hash(){
    return id_;
}

Transaction::Transaction(const Transaction& beta){
  for(TxIn x: beta.txIns_){
    TxIn temp = x;
    txIns_.push_back(temp);
  }
  for(TxOut y: beta.txOuts_){
    TxOut temp = y;
    txOuts_.push_back(temp);
  }
  id_ = beta.id_;
}

bool Transaction:: operator == (const Transaction& beta) const{
  return id_ == beta.id_ ? true : false;
}

bool Transaction:: Validate(UnspentTxOutPool& source) const{
  if(id_ != CalcHash() || !OneToOne(source) || !ValidTxIns(source))
    return false;
  return true;
}

bool Transaction:: ValidTxIns(UnspentTxOutPool& source) const{
  for (TxIn x: txIns_){
    UnspentTxOut* temp = source.FindFromIn(x);
    if (temp == nullptr) return false;
    //validate temp.GetAddress()
    //for this we need secp256k1
    //if (!validated) return false;
  }
  return true;
}
        
        
bool Transaction:: OneToOne(UnspentTxOutPool& source) const{
  double inAmt = 0, outAmt = 0;
  for (TxIn x: txIns_){
    UnspentTxOut* temp = source.FindFromIn(x);
    if (temp == nullptr) continue;
    inAmt = inAmt + temp->GetAmount();
  }
  for (TxOut y: txOuts_)
    outAmt = outAmt + y.GetAmount();
  return inAmt == outAmt ? true : false;
}

std::string Transaction:: CalcHash() const{
  std::string accuInTx = "", accuOutTx = "";
  //for each transaction in txIns_, append its id and index to accuInTx
  for (auto i : txIns_)
    accuInTx = accuInTx + i.GetVal();
  //for each transaction in txOuts_, append its address and amount to accuOutTx
  for (auto i : txOuts_)
    accuOutTx = accuOutTx + i.GetVal();
  //add the two strings and hash them for the id
  return picosha2::hash256_hex_string(accuOutTx);
}

std::vector<TxIn> Transaction::GetTxIns(){
    return txIns_;
}

std::vector<TxOut> Transaction::GetTxOuts(){
    return txOuts_;
}

std::ostream& operator<<(std::ostream& os, const Transaction& t) {
    os << "================ TRANSACTION ================" << std::endl;
    os << "id:" << t.id_ << std::endl;
    for(auto txin = t.txIns_.begin(); txin != t.txIns_.end(); ++txin) {
        // Replace with txin os override
        os << *txin << std::endl;
    }
    for(auto txout = t.txOuts_.begin(); txout != t.txOuts_.end(); ++txout) {
        // Replace with txouts os override
        os << *txout << std::endl;
    }
    os << "=============================================" << std::endl;
}
