#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "network.h"


class UserInterface{
public:

  UserInterface(Network * nw);

  void welcome();

  void run();

  void displayMenu();

private:


  Network * network = new Network();


};



#endif
