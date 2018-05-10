#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <stdint.h>

#include "ecc.h"
#include "picosha2.h"
#include "transaction.h"
#include "utxoutpool.h"

#include "ecc.h"
#include "transaction.h"

class Wallet{

public:

    ~Wallet();
    Wallet(UnspentTxOutPool* UTXO);
    void send(double ccAmt, std::string toCCAddresses);
    bool isWalletActive();
    std::string GetAddress();
    //void Wallet::shutdownWallet();

    // originally private
    Transaction* createTransaction(std::string& ccAddress, double& ccAmt);

private:

    bool valid;
    bool walletFileIsValid();

    std::string myAddress;

    void makeKeyPair();

    void initWallet();
    void validateKeyPairs();

    // returns 1 if unspentBal >= 0, and enough vtxOut were found to send ccAmt; returns 0 otherwise
    int getUnspentTx(const double& ccAmt, std::vector<UnspentTxOut>& vtxOut, double& unspentBal);

    void setTxInput(std::vector<TxIn> &txinputs, std::vector<UnspentTxOut> &txoutput);
    void setTxOutput(std::vector<TxOut> &txoutputs, std::string& ccAddress, double& ccAmt, double& unspentBal);

    void updateWalletBalance();
    void writeWalletToDisk();
    UnspentTxOutPool* UTXO_pool;

    std::pair<std::string, std::string> keyPair;
    double balance_;

};

std::string keyToHexString(uint8_t* key, size_t no_bytes);
void keyToBytes(const std::string& hexKey, uint8_t* key);

#endif //WALLET_H
