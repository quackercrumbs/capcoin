#include "../lib/block.h"
#include "../lib/blockchain.h"
#include "../lib/network.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Hello World!" << endl;

    Blockchain bc;
    Block genBlock = bc.GetLastBlock();
    cout << "HashMatchesDifficulty: " << bc.HashMatchesDifficulty("0012321321312321",2) << endl;
    cout << "Hello world" << endl;

    //test command line argument
    if( (argc > 1) && (strncmp (argv[1], "server", 6) == 0) ){

      Network network;
      network.startServer();
      //network.test();
      //cout << argv[1] << endl;
    }

    return 0;
}
