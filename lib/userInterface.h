#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "network.h"


class UserInterface{
public:

  // UserInterface(Network);

  void welcome();

  void run();

  void displayMenu();

private:

  Network network;


};



#endif
