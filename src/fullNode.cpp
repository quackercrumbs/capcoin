#include "../lib/fullNode.h"
#include <iostream>



FullNode::FullNode(Blockchain * bc, Network * nw){
  blockchain = bc;
  network = nw;
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
  std::cout << "O - Overview     S - Send     R - Receive     ";
  std::cout << "T - Transactions     H - Help     ";
  std::cout << "BC - Blockchain     LB - Last Block" << std::endl;
}

void FullNode::run(){
  while(1){
    std::cout << std::endl;
    displayMenu();
    std::cout << "please make a selection" << std::endl;
    std::string selection;
    std::cin >> selection;

    if(selection == "O" || selection == "o" ){

      // this screen will display the current balance, and any recent transactions

      std::cout << "***************************************************************************" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "*    Balance:                                                             *" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "*    Recent Transactions:                                                 *" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "***************************************************************************" << std::endl << std::endl;

      // display the last incoming message, as a string.  This is for testing purposes only
      std::cout << "last received is: " << network->getLastReceived() << std::endl;
    }
    else if(selection == "S" || selection == "s" ){

      bool correct = false;

      while(!correct){

        std::cout << "***************************************************************************" << std::endl;
        std::cout << "*                                                                         *" << std::endl;
        std::cout << "*    Please Enter a CapCoin Address to Send to                            *" << std::endl;
        std::cout << "*                                                                         *" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        std::string address;
        std::cin >> address;

        std::cout << "***************************************************************************" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Pay To: " << address << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Please enter amount to send" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        std::string amt;
        std::cin >> amt;

        std::cout << "***************************************************************************" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Pay To: " << address << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Amount: " << amt << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Is This Correct? (Y/N or X to Exit)" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        std::string response;
        std::cin >> response;

        if(response == "X" || response == "x"){
          break;
        }
        else if(response == "Y" || response == "y"){
          correct = true;
          std::cout << "***************************************************************************" << std::endl;
          std::cout << "*    Transaction Sent!" << std::endl;
          std::cout << "***************************************************************************" << std::endl;

        }
      }



      Block b = blockchain->GenerateNextBlock();

      // network->broadcastMessage(amt);

      network->broadcastBlock( b );

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
    else if(selection == "BC" || selection == "bc") {
      displayBlockchain();
    }
    else if(selection == "LB" || selection == "lb") {
      displayLastBlock();
    }
    else{
      std::cout << "input not valid" << std::endl;
    }


  }
}

void FullNode::displayLastBlock() {
    std::cout << "         ______________" << std::endl;
    std::cout << "========| Latest Block |========" << std::endl;
    std::cout << "         --------------" << std::endl;

    Block latest = blockchain->GetLastBlock();
    std::cout << latest << std::endl;
}

void FullNode::displayBlockchain() {
    std::cout << "         _________________" << std::endl;
    std::cout << "========| Full Blockchain |========" << std::endl;
    std::cout << "         -----------------" << std::endl;
    std::cout << *blockchain << std::endl;

}
