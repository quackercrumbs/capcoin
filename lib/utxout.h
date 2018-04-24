#ifndef UNSPENTTXOUT_H
#define UNSPENTTXOUT_H

#include <string>

class UnspentTxOut {
public:
    UnspentTxOut(std::string txOutId, std::string address, size_t txOutIndex, double amount);
    std::string GetId();
    std::string GetAddress();
    size_t GetIndex();
    double GetAmount();

private:
    const std::string txOutId_;
    const std::string address_;
    const size_t txOutIndex_;
    const double amount_;

    friend class UnspentTxOutPool;
};

#endif
