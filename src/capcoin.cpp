#include "../lib/block.h"
#include "../lib/blockchain.h"
#include "../lib/network.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    Blockchain bc;
    Block genBlock = bc.GetLastBlock();
    cout << "HashMatchesDifficulty: " << bc.HashMatchesDifficulty("0012321321312321",2) << endl;

    // when new node starts up, this runs to connect to network, download or update blockchain
    //initialize(argv[1]);


    //create network
    Network network;


    if( (argc > 1) && (strncmp (argv[1], "server", 6) == 0) ){
      network.startServer();
    }
    else{
      network.startClient();
    }

    return 0;
}

// void initialize(char* arg){
//
// }
