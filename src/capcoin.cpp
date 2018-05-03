#include "fullNode.h"
//#include "network.h"
#include "block.h"
#include "blockchain.h"
#include "networkmanager.h"
#include "wallet.h"
#include "transactionpool.h"

#include <string.h>
#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;


int main(int argc, char *argv[]) {

  if ( argc < 2 ) {
    std::cout << "USAGE: ./bin/capcoin.o <port> [<initial>]" << std::endl;
    return 0;
  }
  unsigned short port = atoi(argv[1]);

  //Check if running as INITIAL node  
  if((argc == 3) && strcmp(argv[2],"initial") == 0){
    std::cout << "You're running as the initial node." << std::endl;

    // create Blockchain
    Blockchain bc;

    //Test input data for generating a new block
    TxIn in1("a", "asdasdasd", 1);
    TxOut out1("b", 50);

    TxIn in2("c", "asdfasdfasdf", 2);
    TxOut out2("d", 100);

    TxIn in3("e", "asdfadf", 3);
    TxOut out3("f", 150);

    std::vector<TxIn> ins{in1, in2, in3};
    std::vector<TxOut> outs{out1, out2, out3};
    Transaction first(ins, outs);
    std::vector<Transaction> GenTxns{first};

    bc.GenerateNextBlock(GenTxns);

    TransactionPool txpool;

    //create Network
    NetworkManager nw{port, &bc, &txpool};
    nw.Init();
    nw.Run();

    //TODO: REMOVE LOOP?
    //Infinite Loop
    while(1) {
    
    }


  }else{
    //client

    // first, create all 4 parts of the node, Blockchain, Network, Miner and Wallet

    // create Blockchain
    Blockchain bc;
    Block genBlock = bc.GetLastBlock();
    
    // create Transaction Pool
    TransactionPool txpool;
   
    // create network
    NetworkManager nw{port, &bc, &txpool};
    //connect as server or client
    nw.Init();
 
    // create Miner


    // create Wallet
    Wallet w;

    // Initalize Full Node with:
    // Blockchain, Network, Wallet, TxPool, Miner
    // TransactionPool
    FullNode node (&bc, &nw, &w, &txpool);

    node.updateChain();
    node.welcome();


    // start the node
    node.run();
  }

  return 0;
}
