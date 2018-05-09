#include "miner.h"

Miner::Miner(Blockchain* chain, std::string address):chain_{chain}, address_{address}{};

void Miner::mine(TransactionPool& pool){
  //create a vector to store the first 20 transactions.
  std::vector<Transaction> txSupply;
  //start a timer
  time_t start = time(0);
  while(true){
    //if > 20 txns in pool, package 20 and generate a block
    //if 20 > n > 0 txns in pool, and 200 seconds pass, package however many there are into a block.
    int size = pool.size() > 20 ? 20 : pool.size();

    if(size == 20 || (time(0)-200 > start && size > 0)){
      for(int i = 0; i < size; i++){
        txSupply.push_back(pool.front());
        pool.pop();
      }
      chain_->GenerateNextBlock(txSupply);
    }
  }
}

