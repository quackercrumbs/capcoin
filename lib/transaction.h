#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <sstream>
#include "picosha2.h"
#include "txin.h"
#include "txout.h"

class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs);
    std::vector<TxIn> GetTxIns();
    std::vector<TxOut> GetTxOuts();
    std::string hash();
    bool operator < (const Transaction& beta) const;
    bool operator == (const Transaction& beta) const;
private:
    std::string id_;
    //TxIn* txIns_;
    const std::vector<TxIn> txIns_;
    //TxOut* txOuts_;
    const std::vector<TxOut> txOuts_;
};

#endif
