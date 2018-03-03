#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include "transaction.h"
#include <string>
#include <vector>

class Block {
public:
    Block   (size_t index, time_t timestamp, size_t difficulty, size_t nonce,
            std::string hash, std::string prevHash, std::vector<Transaction> &data);

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
