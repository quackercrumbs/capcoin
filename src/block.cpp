#include "../lib/block.h"

Block::Block(size_t index, time_t timestamp, size_t difficulty, size_t nonce,
	std::string hash, std::string prevHash, std::vector<Transaction>& data): 
	index_{index}, timestamp_{timestamp}, difficulty_{difficulty}, nonce_{nonce},
	hash_{hash}, prevHash_{prevHash}, data_{std::move(data)} {}

size_t Block::GetIndex() const {
    return index_;
}

time_t Block::GetTimestamp() const {
    return timestamp_;
}

size_t Block::GetDifficulty() const {
    return difficulty_;
}

size_t Block::GetNonce() const {
    return nonce_;
}

std::string Block::GetHash() const {
    return hash_;
}

std::string Block::GetPreviousHash() const {
    return prevHash_;
}

std::vector<Transaction> Block::GetData() const {
    return data_;
}
