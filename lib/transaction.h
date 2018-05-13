#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "ecc.h"
#include "picosha2.h"
#include "txin.h"
#include "txout.h"
#include "utxout.h"

// used for create & validating signatures
std::string keyToHexString(uint8_t* key, size_t no_bytes);
void keyToBytes(const std::string& hexKey, uint8_t* key);
bool validSignature(std::string&, std::string&, std::string&);

class UnspentTxOutPool;

class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs);
    Transaction(const Transaction& beta);
    std::vector<TxIn> GetTxIns() const;
    std::vector<TxOut> GetTxOuts() const;
    std::string hash() const;
    bool Validate(UnspentTxOutPool* source) const;
    bool operator == (const Transaction& beta) const;

    friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
private:
    std::string CalcHash() const;
    bool SignaturesValid(UnspentTxOutPool* source) const;
    bool OneToOne(UnspentTxOutPool* source) const;
    std::string id_;
    std::vector<TxIn> txIns_;
    std::vector<TxOut> txOuts_;
};

#include "utxoutpool.h"
#endif
