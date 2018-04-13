#ifndef FULLNODE_H
#define FULLNODE_H
#include "blockchain.h"
#include "network.h"


class FullNode{
public:

  FullNode(Blockchain * bc, Network * nw);

  void welcome();

  void run();

  void displayMenu();

private:

  Blockchain * blockchain = new Blockchain();
  Network * network = new Network();


};



#endif
