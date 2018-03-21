#include "../lib/transactionpool.h"

bool TransactionPool:: AddTxn(Transaction& beta){
  //check if already in the pool
  if (!HasTxn(beta))
    return false;
  //check if valid
  if (!beta.Validate())
    return false;
  pool_.push_back(beta);  
}

bool TransactionPool:: HasTxn(Transaction& beta){
  for(Transaction x : pool_){
    if (x == beta)
      return true;
  }
  return false
}

