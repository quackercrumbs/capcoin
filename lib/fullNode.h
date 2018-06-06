#ifndef FULLNODE_H
#define FULLNODE_H
#include "blockchain.h"
//#include "network.h"
#include "networkmanager.h"
#include "wallet.h"
#include "transactionpool.h"

class FullNode{
public:

  FullNode(Blockchain * bc, NetworkManager * nw, Wallet * w, TransactionPool* txpool, bool* killMiner);

  void welcome();

  void run();

  bool updateChain();

  bool updateTransactionPool();

  bool requestHeight();

  void displayMenu();

  void displayLastBlock();

  void displayBlockchain();

  void displayTransactionPool();

private:

  Blockchain * blockchain;
  NetworkManager* network;
  Wallet * wallet;
  TransactionPool * txpool;
  bool* killMiner_;
};

#include "../src/fullNode.cpp"

#endif
