#include "../lib/fullNode.h"
#include <iostream>



FullNode::FullNode(Blockchain * bc, Network * nw){
  blockchain = bc;
  network = nw;
}

bool FullNode::updateChain(){


  network->broadcastMessage("REQUEST");

  return false;
  /*
    //listen for responses, perhaps for a reply that states the size of the current chain
    //for(i = 0; i < current chain size; i++)
      //wait for a message, attempt to parse it into the chain.
      //if constant failures, that means that at some stage, a block was lost, break and try again

  }*/
}

void FullNode::welcome(){
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

void FullNode::displayMenu(){
  std::cout << "O - Overview     S - Send     R - Receive     T - Transactions     H - Help" << std::endl;
}

void FullNode::run(){
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

      //sending fake transaction
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
