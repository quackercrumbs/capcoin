#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"

class Blockchain {
public:
	//Initalize the blockchain by loading data
	Blockchain ();
    size_t GetDifficulty();

	//possibly not necessary, might just ignore this function
	//Block GetLastBlock();


    //Imma try to put this into the block class as Validate()
    //If that doesnt work out, ill just uncomment
	//Checks if the new block is valid by comparing it to the previous block
	//bool IsValidNewBlock(const Block& newBlock);


	//Generates a new block
	Block GenerateNextBlock();

	//Pushes the new block onto the blockchain
	bool Push(Block& newBlock);

private:
	vector<Block> blocks_;
	friend class Block;
}

#endif
