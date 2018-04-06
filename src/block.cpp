#include "block.h"

std::string CalculateHash(size_t index, std::string prevHash, std::time_t timestamp, const std::vector<Transaction>& data, size_t difficulty, size_t nonce){
    std::string dataHash = "";
    std::stringstream accumu;
    for (Transaction i : data)
        accumu << i.hash();
    accumu >> dataHash;
    dataHash = picosha2::hash256_hex_string(dataHash);
    accumu.str(std::string());
    accumu << index << prevHash << timestamp << dataHash << difficulty << nonce;
    dataHash = "";
    accumu >> dataHash;
    dataHash = picosha2::hash256_hex_string(dataHash);
    return dataHash;
}

Block::Block(size_t index, time_t timestamp, size_t difficulty, size_t nonce,
	std::string prevHash, std::vector<Transaction>& data):
	index_{index}, timestamp_{timestamp}, difficulty_{difficulty}, nonce_{nonce},
	prevHash_{prevHash}, data_{std::move(data)},
    hash_{CalculateHash(index_, prevHash_, timestamp_, data_, difficulty_, nonce_)}{}

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
