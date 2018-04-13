#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "blockchain.h"
#include "network.h"


class UserInterface{
public:

  UserInterface(Blockchain * bc, Network * nw);

  void welcome();

  void run();

  void displayMenu();

private:

  Blockchain * blockchain = new Blockchain();
  Network * network = new Network();


};



#endif
