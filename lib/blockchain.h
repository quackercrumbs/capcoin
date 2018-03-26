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

	//Calculates the hash of the block's data.
	std::string CalculateHash(size_t index, std::string prevHash, std::time_t timestamp, const std::vector<Transaction>& data, size_t difficulty, size_t nonce);
	
	//Checks if the provided hash matches the current mining difficulty
	bool HashMatchesDifficulty(std::string hash, size_t difficulty);
	
	//Generates a new block
	Block GenerateNextBlock(std::vector<Transaction>& data);
	
	//Pushes the new block onto the blockchain
	bool Push(Block& newBlock);
	
	//Returns the latest block on the chain
	Block GetLastBlock();

private:
	std::vector<Block> blocks_;
	friend class Block;
};

#endif
