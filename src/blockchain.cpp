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
    //check to see if there are any non-hex characters.
    //this can be placed in the following for loop to reduce time complexity
    if (hash.find_first_not_of("abcdef0123456789") != std::string::npos)
        return false;
    
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
    if (newBlock.index_ != blocks_[blocks_.size()-1].index_ + 1)
        return false;
    //check if timestamp is valid
    //if new time 20 min older than last time, or greater than the current time
    if (blocks_[blocks_.size()-1].timestamp_ - 1200 > newBlock.timestamp_ || time(0) < newBlock.timestamp_)
        return false;
    //check if prevhash matches last block's hash
    if (newBlock.prevHash_ != blocks_[blocks_.size()-1].hash_)
        return false;
    //check if hash is valid
    if (!isValidHash(newBlock))
        return false;
    //otherwise return true
    return true;
}

bool isValidHash(const Block& newBlock){
    //if the hash does not match the content, return false
    //the testing method, that uses a vector in place of a merkle tree, will be used for now.
    if(CalculateHash(newBlock.index_, newBlock.prevHash, newBlock.timestamp_, newBlock.data_, newBlock.difficulty_, newBlock.nonce_) != newBlock.hash_)
        return false;
    //if the hash does not match the difficulty, return false
    if(!HashMatchesDifficulty(newBlock.hash_, newBlock.difficulty_))
        return false;
    //otherwise, return true
    return true;
}

std::string CalculateHash(size_t index, std::string prevHash, std::time_t timestamp, std::vector<Transaction>& data, size_t difficulty, size_t nonce){
    std::string hashify = "";
    //in naivecoin, cryptojs is used. We should get crypto++ up and running. 
    return hashify;
}
