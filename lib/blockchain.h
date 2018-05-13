#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "transaction.h"
#include "transactionpool.h"
#include "utxoutpool.h"
#include "block.h"
#include "picosha2.h"
#include <string>
#include <ctime>
#include <bitset>


class Blockchain {
public:
	//Initalize the blockchain w/ a Genesis block
	Blockchain ();

	//Initalize the blockchain by loading data
	Blockchain (const std::vector<Block>& blocks);

	//Returns the current mining difficulty
	size_t GetDifficulty();

	//Checks if the new block is valid by comparing it to the previous block
	bool IsValidNewBlock(const Block& newBlock);

	bool IsValidHash(const Block& block);

	//Checks if the provided hash matches the current mining difficulty
	bool HashMatchesDifficulty(std::string hash, size_t difficulty);

	//Generates a new block
	bool GenerateNextBlock(bool* killMiner, std::vector<Transaction>& data, TransactionPool* pool, UnspentTxOutPool* utxopool);

	//Pushes the new block onto the blockchain
	bool Push(Block& block, TransactionPool* pool, UnspentTxOutPool* utxopool);

	//Returns the latest block on the chain
	Block GetLastBlock();

  //Return a copy of the block chain as a vector
  std::vector<Block> GetChain();

  //Returns the current height of the blockchain
  size_t GetHeight();

  friend std::ostream& operator<<(std::ostream& os, const Blockchain& b);

private:
	std::vector<Block> blocks_;
	friend class Block;
};

#endif
