#ifndef FULLNODE_H
#define FULLNODE_H
#include "blockchain.h"
#include "network.h"
#include "wallet.h"
#include "transactionpool.h"

class FullNode{
public:

  FullNode(Blockchain * bc, Network * nw, Wallet * wa, TransactionPool* txpool, bool* killMiner);

  void welcome();

  void run();

  bool updateChain();

  void displayMenu();

  void displayLastBlock();

  void displayBlockchain();

  void displayTransactionPool();

private:

  Blockchain * blockchain;
  Network * network;
  Wallet * wallet;
  TransactionPool * txpool;
  bool* killMiner_;

};



#endif
