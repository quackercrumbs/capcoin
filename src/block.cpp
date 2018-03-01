#include "../lib/block.h"

Block::Block(size_t index, time_t timestamp, size_t difficulty, size_t nonce,
	std::string hash, std::string prevHash, vector<Transaction>& data): 
	index_{index}, timestamp_{timestamp}, difficulty_{difficulty}, nonce_{nonce},
	hash_{hash}, prevHash_{prevHash}, data_{std::move(data)} {}
