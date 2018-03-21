#include "../lib/transactionpool.h"

void TransactionPool:: SharePool(const std::vector<Transactions>& beta){
  //for every txn in beta
  for(Transaction x : beta){
    int i = 0;
    //search for an identical txn
    while(i < pool_.length() && !(pool_[i] == x))i++;
    if (pool_[i] == x)
      continue;
    else{
      Transaction cpyTxn(x);
      pool_.push_back(cpyTxn);
    }
  }
}
