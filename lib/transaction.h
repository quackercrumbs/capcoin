#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <sstream>
#include "picosha2.h"
#include "txin.h"
#include "txout.h"
#include "utxout.h"

class UnspentTxOutPool;

class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs);
    Transaction(const Transaction& beta);
    std::vector<TxIn> GetTxIns();
    std::vector<TxOut> GetTxOuts();
    std::string hash();
    bool Validate(UnspentTxOutPool& source) const;
    bool operator == (const Transaction& beta) const;
private:
    std::string CalcHash() const;
    bool ValidTxIns(UnspentTxOutPool& source) const;
    bool OneToOne(UnspentTxOutPool& source) const;
    std::string id_;
    std::vector<TxIn> txIns_;
    std::vector<TxOut> txOuts_;
};

#include "utxoutpool.h"
#endif
