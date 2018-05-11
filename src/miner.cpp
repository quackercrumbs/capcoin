#include "miner.h"

Miner::Miner(Blockchain* chain, TransactionPool* txpool, bool* killMiner,  std::string address):chain_{chain}, txpool_{txpool}, killMiner_{killMiner}, address_{address}{};


void Miner::mine_loop() {
    std::cout << "[miner]: Miner listener activated." << std::endl;
    while(true) {
        //Create a coinbase transaction for the miner, aka the reward
        TxIn coinbaseIn("","",chain_->GetHeight());
        TxOut coinbaseOut(address_, 50);
        std::vector<TxIn> ins{coinbaseIn};
        std::vector<TxOut> outs{coinbaseOut};
        Transaction coinbaseTx{ins,outs};

        //Collection of transactions that will be placed in the mined block
        std::vector<Transaction> txSupply{coinbaseTx};

        //start a timer
        time_t start = time(0);

        //This loop packages transaction for the block
        //When packaging is completed, mining will commence
        //Loop runs when the signal to kill miner is off.
        while(!*killMiner_){
            //if > 20 txns in pool, package 20 and generate a block
            //if 20 > n > 0 txns in pool, and 200 seconds pass, package 
            //however many there are into a block.
            int size = txpool_->size() > 20 ? 20 : txpool_->size();
            if(size == 20 || (time(0)-5 > start && size > 0)){
                  //Package transactions into txSupply
                  for(int i = 0; i < size; i++){
                    txSupply.push_back(txpool_->front());
                    txpool_->pop();
                  }
                  // Mine the block
                  chain_->GenerateNextBlock(killMiner_, txSupply);
            }
        }
        //If there was a signal to kill the miner and there are transactions 
        //from the pool in the packaged transactions
        //put packaged transaction back into pool
        if(*killMiner_ && txSupply.size() > 1) {
            std::cout << "[miner]: Putting back transactions into mempool." << std::endl;
            for(int i = txSupply.size(); i > 1; i--) {
                txpool_->push(txSupply[i]);
                txSupply.pop_back();
            }
            std::cout << "[miner]: All transactions have been placed back into mempool.";
            std::cout << std::endl;
            *killMiner_ = false;
        }
    }

}

std::thread Miner::mineThread() {
    return std::thread([=] {
                mine_loop();
            });
}


