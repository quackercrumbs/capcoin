#ifndef FULLNODE_H
#define FULLNODE_H
#include "blockchain.h"
//#include "network.h"
#include "networkmanager.h"

class FullNode{
public:

  FullNode(Blockchain * bc, NetworkManager * nw);

  void welcome();

  void run();

  bool updateChain();

  void displayMenu();

  void displayLastBlock();

  void displayBlockchain();



private:

  Blockchain * blockchain = new Blockchain();
  //Network * network = new Network();
  NetworkManager* network;

};

#include "../src/fullNode.cpp"

#endif
