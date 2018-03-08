#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <sstream>
#include "txin.h"
#include "txout.h"

class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs);

    std::string GetId();
    std::vector<TxIn> GetTxIns();
    std::vector<TxOut> GetTxOuts();

private:
    std::string id_;
    //TxIn* txIns_;
    const std::vector<TxIn> txIns_;
    //TxOut* txOuts_;
    const std::vector<TxOut> txOuts_;
};

#endif
