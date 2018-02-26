#include "../lib/block.h"

Block::Block(size_t index, time_t timestamp, size_t difficulty, size_t nonce,
	std::string currHash, std::string prevHash, Transaction* data): 
	index_{index}, timestamp_{timestamp}, difficulty_{difficulty}, nonce_{nonce},
	currHash_{currHash}, prevHash_{prevHash}, data_{data} {}