#ifndef FULLNODE_H
#define FULLNODE_H
#include "blockchain.h"
#include "network.h"
#include "wallet.h"

class FullNode{
public:

  FullNode(Blockchain * bc, Network * nw, Wallet * w);

  void welcome();

  void run();

  bool updateChain();

  void displayMenu();

  void displayLastBlock();

  void displayBlockchain();



private:

  Blockchain * blockchain = new Blockchain();
  Network * network = new Network();
  Wallet * wallet = new Wallet();

};



#endif
