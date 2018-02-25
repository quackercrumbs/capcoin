#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>

class TxIn{
public:
    TxIn    (std::string id, std::string sig, size_t index):
            id_{id}, sig_{sig}, index_{index}{}
private:
    const std::string id_;
    const std::string sig_;
    const size_t index_;
};

class TxOut{
public:
    TxOut   (std::string address, double amount):
            address_{address}, amount_{amount}{}
private:
    const std::string address_;
    const double amount_;
};


class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs):
                txIns_{std::move(ins)}, txOuts_{std::move(outs)}{
        //generate id
    }

private:
    std::string id_;
    //TxIn* txIns_;
    const std::vector<TxIn> txIns_;
    //TxOut* txOuts_;
    const std::vector<TxOut> txOuts_;
};

#endif
