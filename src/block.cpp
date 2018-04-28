#include "block.h"

std::string CalculateHash(size_t index, std::string prevHash, std::time_t timestamp, const std::vector<Transaction>& data, size_t difficulty, size_t nonce){
    std::string dataHash = "";
    std::stringstream accumu;
    //Feed transaction hash into sstream
    for (Transaction i : data)
        accumu << i.hash();
    //store hash for transactions temporarily in dataHash
    accumu >> dataHash;
    dataHash = picosha2::hash256_hex_string(dataHash);
    //Clear string stream
    accumu.clear();
    accumu.str(std::string());
    //Feed block header and transaction hash to sstream
    accumu << index << prevHash << timestamp << dataHash << difficulty << nonce;
    dataHash = "";
    accumu >> dataHash;
    //Calculate hash of block
    dataHash = picosha2::hash256_hex_string(dataHash);
    return dataHash;
}

Block::Block(size_t index, time_t timestamp, size_t difficulty, size_t nonce, std::string hash,
	std::string prevHash, std::vector<Transaction>& data):
	index_{index}, timestamp_{timestamp}, difficulty_{difficulty}, nonce_{nonce},
	prevHash_{prevHash}, data_{std::move(data)},
    hash_{hash}{}

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

std::ostream& operator<<(std::ostream& os, const Block& b) {
    os << "----------- BLOCK --------------" << std::endl;
    os << "Index: " << b.index_ << std::endl;
    os << "Timestamp: " << b.timestamp_ << std::endl;
    os << "Difficulty: " << b.difficulty_ << std::endl;
    os << "Nonce: " << b.nonce_ << std::endl;
    os << "Previous Hash: " << b.prevHash_ << std::endl;
    os << "Hash: " << b.hash_ << std::endl;
    os << "---------------------------------" << std::endl;
    return os;
}
