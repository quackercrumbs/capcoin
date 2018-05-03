#ifndef FULLNODE_H
#define FULLNODE_H
#include "blockchain.h"
//#include "network.h"
#include "networkmanager.h"
#include "wallet.h"
#include "transactionpool.h"

class FullNode{
public:

  FullNode(Blockchain * bc, NetworkManager * nw, Wallet * w, TransactionPool* txpool);

  void welcome();

  void run();

  bool updateChain();

  void displayMenu();

  void displayLastBlock();

  void displayBlockchain();

  void displayTransactionPool();

private:

  Blockchain * blockchain = new Blockchain();
  //Network * network = new Network();
  NetworkManager* network;
  Wallet * wallet = new Wallet();
  TransactionPool * txpool = new TransactionPool();
};

#include "../src/fullNode.cpp"

#endif
