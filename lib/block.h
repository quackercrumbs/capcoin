#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include <string>
#include <vector>
#include <ctime> 

class Block {
public:
    Block   (size_t index, time_t timestamp, size_t difficulty, size_t nonce,
            std::string hash, std::string prevHash, std::vector<Transaction> &data);

    size_t GetIndex() const;
    time_t GetTimestamp() const;
    size_t GetDifficulty() const;
    size_t GetNonce() const;
    std::string GetHash() const;
    std::string GetPreviousHash() const;
    std::vector<Transaction> GetData() const;

private:
    const size_t index_;
    const time_t timestamp_;
    const size_t difficulty_;
    const size_t nonce_;
    const std::string hash_;
    const std::string prevHash_;
    const std::vector<Transaction> data_;
};

#endif
