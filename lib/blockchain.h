#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "transaction.h"
#include "block.h"
#include <string>
#include <time.h>


class Blockchain {
public:
	//Initalize the blockchain by loading data
	Blockchain ();

    //Returns the current mining difficulty
    size_t GetDifficulty();

	//possibly not necessary, might just ignore this function
	//Block GetLastBlock();

    //Imma try to put this into the block class as Validate()
    //If that doesnt work out, ill just uncomment
	//Checks if the new block is valid by comparing it to the previous block
	//bool IsValidNewBlock(const Block& newBlock);

    //Calculates the hash of the block's data.
    std::string CalculateHash(size_t index, std::string prevHash, std::time_t timestamp, std::vector<Transaction>& data, size_t difficulty, size_t nonce);

    //Checks if the provided hash matches the current mining difficulty
    bool HashMatchesDifficulty(std::string hash, size_t difficulty);

	//Generates a new block
	Block GenerateNextBlock();

	//Pushes the new block onto the blockchain
	bool Push(Block& newBlock);

    //Returns the latest block on the chain
    Block GetLastBlock();

private:
	vector<Block> blocks_;
	friend class Block;
}

#endif
