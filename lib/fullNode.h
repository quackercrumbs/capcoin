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

  Blockchain * blockchain = new Blockchain();
  NetworkManager* network;
  Wallet * wallet = new Wallet();
  TransactionPool * txpool = new TransactionPool();
  bool* killMiner_;
};

#include "../src/fullNode.cpp"

#endif
