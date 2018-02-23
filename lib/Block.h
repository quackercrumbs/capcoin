#include <time.h>
#include <Transaction.h>
#include <string>



class Block {
public:
    Block   (size_t index, time_t timestamp, size_t difficulty, size_t nonce,
            std::string currHash, std::string prevHash, Transaction* data):
            index_{index}, timestamp_{timestamp}, difficulty_{difficulty},
            nonce_{nonce}, currHash_{currHash}, prevHash_{prevHash},
            data_{data}{}

private:
    size_t index_;
    time_t timestamp_;
    size_t difficulty_;
    size_t nonce_;
    std::string currHash_;
    std::string prevHash_;
    Transaction* data_;
};
