#include "userInterface.h"
#include "network.h"
#include "block.h"
#include "blockchain.h"

#include <string.h>
#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;


int main(int argc, char *argv[]) {

    // first, create all 4 parts of the node, Blockchain, Network, Miner and Wallet

    // create Blockchain
    Blockchain bc;
    Block genBlock = bc.GetLastBlock();



    //create Network
    Network nw;
    //connect as server or client
    ((argc > 1) && (strncmp (argv[1], "server", 6) == 0)) ? nw.startServer() : nw.startClient();
    //start listening for incoming messages, on another thread
    std::thread listenThread = nw.listenThread();



    // create Miner




    // create Wallet



    // then, create full node, using these 4 parts
    UserInterface ui (&nw);
    ui.welcome();

    // start the node
    ui.run();


    return 0;
}
