#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "transaction.h"
#include "block.h"
#include "picosha2.h"
#include <string>
#include <ctime>
#include <bitset>


class Blockchain {
public:
	//Initalize the blockchain by loading data
	Blockchain ();

	//Returns the current mining difficulty
	size_t GetDifficulty();

	//Checks if the new block is valid by comparing it to the previous block
	bool IsValidNewBlock(const Block& newBlock);

	bool IsValidHash(const Block& block);

	//Checks if the provided hash matches the current mining difficulty
	bool HashMatchesDifficulty(std::string hash, size_t difficulty);

	//Generates a new block
	Block GenerateNextBlock(std::vector<Transaction>& data);

	//Pushes the new block onto the blockchain
	bool Push(Block& newBlock);

	//Returns the latest block on the chain
	Block GetLastBlock();
	
    //Return a copy of the block chain as a vector
    std::vector<Block> GetChain();

    
    friend std::ostream& operator<<(std::ostream& os, const Blockchain& b);

private:
	std::vector<Block> blocks_;
	friend class Block;
};

#endif
