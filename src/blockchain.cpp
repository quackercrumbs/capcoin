#include "../lib/blockchain.h"
#include "../lib/block.h"
#include "../lib/transaction.h"
#include <bitset>

Blockchain::Blockchain(){
    //initialize the chain with the genesis block. 
    //Change addresses and hashes in future
    TxIn GenIn("", "", 0);
    TxOut GenOut("32ba5334aafcd8e7266e47076996b55", 50);
    std::vector<TxIn> TxIns{GenIn};
    std::vector<TxOut> TxOuts{GenOut};
    Transaction GenTxn(TxIns, TxOuts);
    std::vector<Transaction> GenTxns{GenTxn};
    Block Genesis(0, 1521001712, 0, 0, "cd4321ce128c5aab080299604b9ba347", "", GenTxns);
}


Block Blockchain::GetLastBlock(){
    return blocks_[length-1];
}

Block Blockchain::GenerateNextBlock(vector <Transaction>& data){
    size_t index = blocks_[length-1].index_ + 1;
    time_t timestamp = time(0);
    size_t difficulty = GetDifficulty();
    size_t nonce = 0;
    std::string hash_;
    std::string prevHash = blocks_[length-1].hash_;
    while (true) {
        hash = CalculateHash(index, prevHash, timestamp, data, difficulty, nonce);
        if (HashMatchesDifficulty(hash, difficulty)) {
            break;
        }
        nonce++;
    }
    Block newBlock(index, timestamp, difficulty, nonce, hash, prevHash, data);
    IsValidNewBlock(newBlock);
    blocks_.push_back(newBlock);
    //Broadcast new block
}

bool HashMatchesDifficulty(std::string hash, size_t difficulty){
    //create empty string
    std::string binString = "";
    int charToBin;
    std::stringstream output;
    //for each character in the length of hash
    for (unsigned int i = 0; i < hash.length(); i++){
        std::stringstream input;
        //take char, put into input
        input << hash[i];
        input >> std::hex >> charToBin;
        //convert to binary, then sent do output
        output << (std::bitset<4>)charToBin;
    }
    //binString takes entire binary form of hash
    output >> binString;
    //if the difficulty is x, find the first character in binString that is not 0
    int firstNot0 = binString.find_first_not_of("0");
    //if the character has index < x, return false
    return firstNot0 < difficulty? false : true;
}
    
size_t GetDifficulty(){
    //to avoid error, if less than 2 blocks, return a difficulty of 1
    if (blocks_.size() < 2)
        return 1;
    //if the time between the last two blocks is less than 10 min, increase difficulty
    if (blocks_[blocks_.size()-1].timestamp_ - blocks_[blocks_.size()-2].timestamp_ < 600)
        return blocks_[blocks_.size()-1].difficulty_ + 1;
    //if the time between the last two blocks is more than 15 min, decrease difficulty
    else if (900 < blocks_[blocks_.size()-1].timestamp_ - blocks_[blocks_.size()-2].timestamp_)
        return blocks_[blocks_.size()-1].difficulty_ - 1;
    //if in the 10-15 min range, keep difficulty
    else
         return blocks_[blocks_.size()-1].difficulty_;
}
    
bool IsValidNewBlock(const Block& newBlock){
    //check if index is valid
    
    //check if timestamp is valid
    
    //check if prevhash matches last block's hash
    
    //check if hash is valid
}
    
