#include "../lib/userInterface.h"
#include <iostream>
// #include "../lib/network.h"


// UserInterface::UserInterface(Network){
//   network = Network;
// }

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
  std::cout << "O - Overview     S - Send     R - Receive     T - Transactions     H - Help     C - Chat (for testing)" << std::endl;
}

void UserInterface::run(){
  while(1){
    std::cout << std::endl;
    displayMenu();
    std::cout << "please make a selection" << std::endl;
    std::string selection;
    std::cin >> selection;

    if(selection == "O" || selection == "o" ){
      std::cout << "run overview" << std::endl;
    }
    else if(selection == "S" || selection == "s" ){
      std::cout << "run send" << std::endl;
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
    else if(selection == "C" || selection == "c" ){
      std::cout << "run chat" << std::endl;
    }
    else{
      std::cout << "input not valid" << std::endl;
    }


  }
}
