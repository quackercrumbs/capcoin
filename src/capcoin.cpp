#include "fullNode.h"
#include "network.h"
#include "block.h"
#include "blockchain.h"
#include "wallet.h"
#include "utxoutpool.h"
#include "transactionpool.h"

#include <string.h>
#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;

bool killMiner = false;

int main(int argc, char *argv[]) {


  if((argc > 1) && (strncmp (argv[1], "server", 6) == 0)){
    //server


    // create Blockchain
    Blockchain bc;
    // Block genBlock = bc.GetLastBlock();



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

    

    bc.GenerateNextBlock(killMiner, GenTxns);

    //create Network
    Network nw;
    nw.runServer(&bc);

    //  network listen on seperate thread


    //FullNode node (&bc, &nw);
    // node.run();


  }else{
    //client

    // first, create all 4 parts of the node, Blockchain, Network, Miner and Wallet

    // create Blockchain
    Blockchain bc;
    Block genBlock = bc.GetLastBlock();

    // create Transaction Pool
    TransactionPool txpool;

    // create Network
    Network nw;
    //connect as client
    nw.startClient(&bc, &txpool);
    //start listening for incoming messages, on another thread
    std::thread listenThread = nw.listenThread();

    // create Miner

    // create Wallet
    UnspentTxOutPool utxoutpool;
    Wallet wa(&utxoutpool);

    // Initalize Full Node with:
    // Blockchain, Network, Wallet, Miner
    // TransactionPool
    FullNode node (&bc, &nw, &wa, &txpool);

    node.updateChain();
    node.welcome();

    // start the node
    node.run();
  }




    return 0;
}
