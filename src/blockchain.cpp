#include "../lib/blockchain.h"
#include "../lib/block.h"
#include "../lib/transaction.h"

Blockchain::Blockchain(){
    //create genesis block to initialize the chain
}

//
//Block Blockchain::GetLastBlock(){
//    return blocks_[length-1];
//}

Block Blockchain::GenerateNextBlock(vector <Transaction>& data){
    size_t index = blocks_[length-1].index_ + 1;
    time_t timestamp = time(0);
    size_t difficulty = GetDifficulty();
    size_t nonce = 0;
    std::string hash_;
    std::string prevHash = blocks_[length-1].hash_;
    while (true) {
        hash = calculateHash(index, prevHash, timestamp, data, difficulty, nonce);
        if (hashMatchesDifficulty(hash, difficulty)) {
            break;
        }
        nonce++;
    }
    Block newBlock(index, timestamp, difficulty, nonce, hash, prevHash, data);
    newBlock.Validate();
    blocks_.push_back(newBlock);
    //Broadcast new block
}

