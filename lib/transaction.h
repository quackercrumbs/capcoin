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
    Transaction(Transaction& beta);
    std::vector<TxIn> GetTxIns();
    std::vector<TxOut> GetTxOuts();
    std::string hash();
    bool Validate() const;
    bool operator == (const Transaction& beta) const;
private:
    std::string CalcHash();
    std::string id_;
    const std::vector<TxIn> txIns_;
    const std::vector<TxOut> txOuts_;
};

#endif
