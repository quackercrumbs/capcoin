#include "../lib/userInterface.h"
#include <iostream>



UserInterface::UserInterface(Blockchain * bc, Network * nw){
  blockchain = bc;
  network = nw;
}

void UserInterface::welcome(){
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "*************************                          ************************" << std::endl;
  std::cout << "*************************    WELCOME TO CAPCOIN    ************************" << std::endl;
  std::cout << "*************************                          ************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl << std::endl;

}

void UserInterface::displayMenu(){
  std::cout << "O - Overview     S - Send     R - Receive     T - Transactions     H - Help" << std::endl;
}

void UserInterface::run(){
  while(1){
    std::cout << std::endl;
    displayMenu();
    std::cout << "please make a selection" << std::endl;
    std::string selection;
    std::cin >> selection;

    if(selection == "O" || selection == "o" ){
      std::cout << "last received is: " << network->getLastReceived() << std::endl;
    }
    else if(selection == "S" || selection == "s" ){
      std::cout << "please enter amount to send" << std::endl;
      std::string amt;
      std::cin >> amt;
      network->broadcastMessage(amt);
    }
    else if(selection == "R" || selection == "r" ){
      std::cout << "run receive" << std::endl;
    }
    else if(selection == "T" || selection == "t" ){
      std::cout << "run transactions" << std::endl;

    }
    else if(selection == "H" || selection == "h" ){
      std::cout << "run help" << std::endl;
    }
    else{
      std::cout << "input not valid" << std::endl;
    }


  }
}
