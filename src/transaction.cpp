#include "../lib/transaction.h"

Transaction::Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs): txIns_{std::move(ins)}, txOuts_{std::move(outs)}{
  id_ = CalcHash();
}

std::string Transaction:: hash(){
    return id_;
}
Transaction::Transaction(const Transaction& beta){
  txIns_ = beta.txIns_;
  txOuts_ = beta.txOuts_;
  id_ = beta.id_;
}
  
bool Transaction:: operator == (const Transaction& beta) const{
  return id_ == beta.id_ ? true : false;
}

bool Transaction:: Validate() const{
  if(id_ != CalcHash())
    return false;
  if(!OneToOne())
    return false;
  for(TxIn x: txIns_)
    if(x 
  return true;
}

bool Transaction:: OneToOne(UnspentTxOutPool& source) const{
  double inAmt = 0, outAmt = 0;
  for (TxIn x: txIns_)
    inAmt = inAmt + source.FindFromIn(x).GetAmount();
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
