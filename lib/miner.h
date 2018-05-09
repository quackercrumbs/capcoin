#ifndef MINER_H
#define MINER_H

#include "transactionpool.h"
#include "blockchain.h"

class Miner{
public:
  //Miner takes a blockchain to add blocks onto, as well as an address to reward coins to
  Miner(Blockchain* chain, std::string address);

  //To mine, we pass a vector of transactions
  void mine(TransactionPool& pool);

private:
  Blockchain* chain_;
  std::string address_;
};

#endif
