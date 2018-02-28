#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <sstream>

class TxIn{
public:
    TxIn(std::string id, std::string sig, size_t index);
    std::string GetVal();
private:
    const std::string id_;
    const std::string sig_;
    const size_t index_;
};

class TxOut{
public:
    TxOut(std::string address, double amount);
    std::string GetVal();
private:
    const std::string address_;
    const double amount_;
};

class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs);
private:
    std::string id_;
    //TxIn* txIns_;
    const std::vector<TxIn> txIns_;
    //TxOut* txOuts_;
    const std::vector<TxOut> txOuts_;
};

class UnspentTxOut {
public:
    constructor(string txOutId, string  address, size_t txOutIndex, size_t amount);
private:
    const string txOutId;
    const string address;
    const size_t txOutIndex;
    const size_t amount;
}

#endif
