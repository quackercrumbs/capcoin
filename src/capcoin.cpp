#include "userInterface.h"
#include "network.h"
#include "block.h"
#include "blockchain.h"

#include <string.h>
#include <iostream>
#include <thread>

using namespace std;


int main(int argc, char *argv[]) {

    Blockchain bc;
    Block genBlock = bc.GetLastBlock();

    UserInterface ui;

    //create network, connect as server or client
    Network network;
    ((argc > 1) && (strncmp (argv[1], "server", 6) == 0)) ? network.startServer() : network.startClient();

    ui.welcome();

    //start listening for incoming messages, on another thread
    std::thread listenThread = network.listenThread();

    // main while loop for UI
    while(1){
      std::cout << std::endl;
      std::cout << "O - Overview     S - Send     R - Receive     T - Transactions     H - Help" << std::endl;
      std::cout << "please make a selection" << std::endl;
      std::string selection;
      std::cin >> selection;

      if(selection == "O" || selection == "o" ){
        std::cout << "last received is: " << network.getLastReceived() << std::endl;
      }
      else if(selection == "S" || selection == "s" ){
        std::cout << "please enter amount to send" << std::endl;
        string amt;
        cin >> amt;
        network.broadcastMessage(amt);
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

    return 0;
}
