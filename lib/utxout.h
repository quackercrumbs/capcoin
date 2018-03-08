#ifndef UNSPENTTXOUT_H
#define UNSPENTTXOUT_H

class UnspentTxOut {
public:
    UnspentTxOut(std::string txOutId, std::string address, size_t txOutIndex, size_t amount);

    std::string GetId();
    std::string GetAddress();
    size_t GetIndex();
    size_t GetAmount();

private:
    const std::string txOutId_;
    const std::string address_;
    const size_t txOutIndex_;
    const size_t amount_;
}

#endif