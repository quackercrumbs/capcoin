#ifndef UNSPENTTXOUT_H
#define UNSPENTTXOUT_H

#include <string>
#include <iostream>

class UnspentTxOut {
public:
    UnspentTxOut(std::string txOutId, std::string address, size_t txOutIndex, double amount);
    UnspentTxOut(const UnspentTxOut&);
    std::string GetId() const;
    std::string GetAddress() const;
    size_t GetIndex() const;
    double GetAmount() const;

    UnspentTxOut& operator = (const UnspentTxOut&);

private:
    const std::string txOutId_;
    const std::string address_;
    const size_t txOutIndex_;
    const double amount_;

    friend std::ostream& operator<<(std::ostream& os, const UnspentTxOut& u);
    friend class UnspentTxOutPool;
};

#endif
