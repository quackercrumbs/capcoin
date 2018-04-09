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
    // cout << "HashMatchesDifficulty: " << bc.HashMatchesDifficulty("0012321321312321",2) << endl;


    UserInterface ui;
    ui.welcome();



    //create network, connect as server or client
    Network network;
    if( (argc > 1) && (strncmp (argv[1], "server", 6) == 0) ){
      network.startServer();
    }
    else{
      // network.startClient();
    }


    ui.run();


    return 0;
}
