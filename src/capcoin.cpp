#include "userInterface.h"
#include "network.h"
#include "block.h"
#include "blockchain.h"

#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    Blockchain bc;
    Block genBlock = bc.GetLastBlock();

    UserInterface ui;


    //create network, connect as server or client
    Network network;
    if( (argc > 1) && (strncmp (argv[1], "server", 6) == 0) ){
      network.startServer();
    }
    else{
      //network.startClient();
    }

    ui.welcome();
    //ui.run();

    network.startClient();


    while(1){
      std::cout << std::endl;
      std::cout << "O - Overview     S - Send     R - Receive     T - Transactions     H - Help     C - Chat (for testing)" << std::endl;
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
        network.broadcastMessage("test");
      }
      else if(selection == "H" || selection == "h" ){
        std::cout << "run help" << std::endl;
      }
      else if(selection == "C" || selection == "c" ){
        network.listen();
      }
      else{
        std::cout << "input not valid" << std::endl;
      }
    }




    return 0;
}
