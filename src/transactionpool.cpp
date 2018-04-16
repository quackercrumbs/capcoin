#include "../lib/transactionpool.h"

bool TransactionPool:: HasTxn(Transaction& beta){
  for(Transaction x : pool_){
    if (x == beta)
      return true;
  }
  return false;
}

bool TransactionPool:: AddTxn(Transaction& beta, UnspentTxOutPool& source){
  //check if already in the pool
  if (!HasTxn(beta))
    return false;
  //check if valid
  if (!beta.Validate(source))
    return false;
  pool_.push_back(std::move(beta));
  return true;
}


