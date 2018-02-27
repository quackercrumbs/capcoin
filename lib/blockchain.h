#ifndef BLOCK_CHAIN_H
#define BLOCK_CHAIN_H

class Blockchain {
public:
	//Initalize the blockchain by loading data
	BlockChain ();

	//Checks if the new block is valid by comparing it to the previous block
	bool IsValidNewBlock(const Block& newBlock);

	//Generates a new block
	Block GenerateNextBlock();

	//Pushes the new block onto the blockchain
	bool Push(Block& newBlock);

private:
	vector<Block> blocks_;
}

#endif