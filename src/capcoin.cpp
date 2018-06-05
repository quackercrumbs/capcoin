#include "fullNode.h"
//#include "network.h"
#include "block.h"
#include "blockchain.h"
#include "networkmanager.h"
#include "wallet.h"
#include "utxoutpool.h"
#include "transactionpool.h"
#include "miner.h"

#include <string.h>
#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;


int main(int argc, char *argv[]) {

  if ( argc < 2 ) {
    std::cout << "USAGE: ./bin/capcoin <port> [<initial>]" << std::endl;
    return 0;
  }
  unsigned short port = atoi(argv[1]);
 
  bool killMinerSignal = false;
  
  //Check if running as INITIAL node  
  if((argc == 3) && strcmp(argv[2],"initial") == 0){
    std::cout << "[capcoin]: You're running as the initial node." << std::endl;

    // create Transaction Pool
    TransactionPool txpool;

    // create UTxOutPool
    UnspentTxOutPool utxoutpool;

    // create Blockchain
    Blockchain bc(&txpool, &utxoutpool);

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
    
    std::cout << "[capcoin]: Generating a new block." << std::endl;
    bc.GenerateNextBlock(&killMinerSignal, GenTxns);


    TxIn in1a("a", "asdasdasd", 1);
    TxOut out1a("b", 50);

    TxIn in2a("c", "asdfasdfasdf", 2);
    TxOut out2a("d", 100);

    TxIn in3a("e", "asdfadf", 3);
    TxOut out3a("f", 150);
    
    std::vector<TxIn> insa{in1a, in2a, in3a};
    std::vector<TxOut> outsa{out1a, out2a, out3a};
    Transaction firsta(insa, outsa);
    std::vector<Transaction> GenTxns2{firsta};
    
    std::cout << "[node]: Generating a new block." << std::endl;
    bc.GenerateNextBlock(&killMinerSignal, GenTxns2);

    // create Network Manager
    // NetworkManager nw{port, &bc, &txpool, &utxoutpool, &killMinerSignal};
    NetworkManager nw{port, &bc, &txpool};
    nw.Init();
    nw.Run();

    //Infinite Loop
    while(1) {
    
    }

  }else{
    //client

    // create Transaction Pool
    TransactionPool txpool;
  
    // create UTxOutPool
    UnspentTxOutPool utxoutpool;
 
    // create Blockchain
    Blockchain bc(&txpool, &utxoutpool);
    Block genBlock = bc.GetLastBlock();

    // create network
    // NetworkManager nw{port, &bc, &txpool, &utxoutpool, &killMinerSignal};
    NetworkManager nw{port, &bc, &txpool};
    //connect as server or client
    nw.Init();

    // create Wallet
    Wallet wa(&txpool, &utxoutpool);

    std::string address = wa.GetAddress();

    // create Miner
    Miner miner (&bc,&txpool,&utxoutpool,&nw,&killMinerSignal,address);
    std::thread miner_thread = miner.mineThread();

    double amt = 2222222;
    TxIn dummyIn("", "", 0);
    TxOut dummyOut("22222222222222222222222222222222", amt);
    std::vector<TxIn> TxIns{dummyIn};
    std::vector<TxOut> TxOuts{dummyOut};

    Transaction dummy = {TxIns, TxOuts};

    double amt2 = 3333333;
    TxIn dummyIn2("", "", 0);
    TxOut dummyOut2("33333333333333333333333333333333", amt2);
    std::vector<TxIn> TxIns2{dummyIn2};
    std::vector<TxOut> TxOuts2{dummyOut2};

    Transaction dummy2 = {TxIns2, TxOuts2};

    // Push dummy transactions into pool
    txpool.push(dummy);
    txpool.push(dummy2);

    // Initalize Full Node with:
    // Blockchain, Network, Wallet, TxPool, Miner
    // TransactionPool
    FullNode node (&bc, &nw, &wa, &txpool, &killMinerSignal);

    node.updateChain();
    node.welcome();

    // start the node
    node.run();
  }

  return 0;
}
