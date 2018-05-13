#include "blockchain.h"
#include "../lib/socket.h"
#include "../lib/network.h"

Blockchain::Blockchain(TransactionPool* pool, UnspentTxOutPool* utxopool)
  :txpool_{pool}, utxopool_{utxopool} {
    //initialize the chain with the genesis block.
    //Change addresses and hashes in future
    TxIn GenIn("", "", 0);
    TxOut GenOut("32ba5334aafcd8e7266e47076996b55", 50);
    std::vector<TxIn> TxIns{GenIn};
    std::vector<TxOut> TxOuts{GenOut};
    Transaction GenTxn(TxIns, TxOuts);
    std::vector<Transaction> GenTxns{GenTxn};

    Block Genesis(0, 1521001712, 8, 0, "", GenTxns);

    //Push genesis block onto blockchain
    blocks_.push_back(Genesis);
}

Blockchain::Blockchain(const std::vector<Block>& blocks)
  : blocks_{blocks} {}


Block Blockchain::GetLastBlock(){
    return blocks_[blocks_.size()-1];
}
std::vector<Block> Blockchain::GetChain(){
    return blocks_;
}

bool Blockchain::Push(Block& block){
  //verify block
  //if fails, return false
  if (block.GetIndex() != blocks_[blocks_.size()-1].GetIndex()+1 &&
  block.GetPreviousHash() != blocks_[blocks_.size()-1].GetHash())
    return false;
  for (auto i : block.GetData()){
	   txpool_->remove(i);
  }

  size_t noTxns = block.GetData().size();
  for(int i=1; i<noTxns; i++){
    Transaction t = block.GetData()[i];
    utxopool_->AddTxn(t);
  }

  //process coinbase last
  Transaction coinbaseTx = block.GetData().front();
  std::string minerAddress = coinbaseTx.GetTxOuts().back().GetAddress();
  double amount = coinbaseTx.GetTxOuts().back().GetAmount();

  UnspentTxOut u(coinbaseTx.hash(), minerAddress, utxopool_->GetIndex()+1, amount);
  utxopool_->insert(u);

  blocks_.push_back(block);

  return true;
}

bool Blockchain::GenerateNextBlock(bool* killMiner, std::vector <Transaction>& data){
    size_t index = blocks_[blocks_.size()-1].GetIndex() + 1;
    time_t timestamp = time(0);
    size_t difficulty = GetDifficulty();
    size_t nonce = 0;
    std::string hash_;
    std::string prevHash = blocks_[blocks_.size()-1].GetHash();
    std::cout << "[miner-bc]: Mining operation started ..." << std::endl;
    //Search for hash that matches difficulty, aka mining.
    while (true) {
        // Stop all mining operations upon kill signal
        if(*killMiner) {
            std::cout << "[miner-bc]: Mining operation halted. Due to kill signal." << std::endl;
			return false;
        }
        hash_ = CalculateHash(index, prevHash, timestamp, data, difficulty, nonce);
        if (HashMatchesDifficulty(hash_, difficulty))
			break;
        nonce++;
    }
    Block newBlock(index, timestamp, difficulty, nonce, prevHash, data);

    if(IsValidNewBlock(newBlock)) {
        std::cout << "[miner-bc]: Mining operation successful." << std::endl;
        // blocks_.push_back(newBlock);
        Push(newBlock);
    }
    else {
        std::cout << "[miner-bc]: Mining operation failed." << std::endl;
        return false;
    }
    //TODO : Broadcast new block

    return true;
}



bool Blockchain::HashMatchesDifficulty(std::string hash, size_t difficulty){
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

size_t Blockchain::GetDifficulty(){
    //to avoid error, if less than 2 blocks, return a difficulty of 1
    if (blocks_.size() < 2)
        return blocks_[0].GetDifficulty();
    //if the time between the last two blocks is less than 10 min, increase difficulty
    if (blocks_[blocks_.size()-1].GetTimestamp() - blocks_[blocks_.size()-2].GetTimestamp() < 600)
        return blocks_[blocks_.size()-1].GetDifficulty() + 1;
    //if the time between the last two blocks is more than 15 min, decrease difficulty
    else if (900 < blocks_[blocks_.size()-1].GetTimestamp() - blocks_[blocks_.size()-2].GetTimestamp())
        return blocks_[blocks_.size()-1].GetDifficulty() - 1;
    //if in the 10-15 min range, keep difficulty
    else
         return blocks_[blocks_.size()-1].GetDifficulty();
}

bool Blockchain::IsValidNewBlock(const Block& newBlock){
    //check if index is valid
    if (newBlock.GetIndex() != blocks_[blocks_.size()-1].GetIndex() + 1)
        return false;
    //check if timestamp is valid
    //if new time 20 min older than last time, or greater than the current time
    if (blocks_[blocks_.size()-1].GetTimestamp() - 1200 > newBlock.GetTimestamp() || time(0) < newBlock.GetTimestamp())
        return false;
    //check if prevhash matches last block's hash
    if (newBlock.GetPreviousHash() != blocks_[blocks_.size()-1].GetHash())
        return false;
    //check if hash is valid
    if (!IsValidHash(newBlock))
        return false;
    //otherwise return true
    return true;
}

bool Blockchain::IsValidHash(const Block& newBlock){
    //if the hash does not match the content, return false
    //the testing method, that uses a vector in place of a merkle tree, will be used for now.
    if(CalculateHash(newBlock.GetIndex(), newBlock.GetPreviousHash(), newBlock.GetTimestamp(), newBlock.GetData(), newBlock.GetDifficulty(), newBlock.GetNonce()) != newBlock.GetHash())
        return false;
    //if the hash does not match the difficulty, return false
    if(!HashMatchesDifficulty(newBlock.GetHash(), newBlock.GetDifficulty()))
        return false;
    //otherwise, return true
    return true;
}

size_t Blockchain::GetHeight() {
    return blocks_.size();
}

std::ostream& operator<<(std::ostream& os, const Blockchain& bc) {
    for(auto i = bc.blocks_.begin(); i != bc.blocks_.end(); ++i) {
        os << *i << std::endl;
    }
    return os;
}
