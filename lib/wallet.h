#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include "ecc.h"
#include "picosha2.h"
#include "transaction.h"
#include "utxoutpool.h"


class Wallet{

public:

    Wallet();
    ~Wallet();
    Wallet(UnspentTxOutPool* UTXO);
    void send(double ccAmt, std::string toCCAddresses);
    bool isWalletActive();
    //void Wallet::shutdownWallet();

private:

    bool valid;
    std::string myAddress;
    Transaction* createTransaction(std::string& ccAddress, double& ccAmt);
    void makeKeyPair();

    void initWallet();
    void validateRawAddress();

    // returns 1 if unspentBal >= 0, and enough vtxOut were found to send ccAmt; returns 0 otherwise
    int getUnspentTx(const double& ccAmt, std::vector<UnspentTxOut>& vtxOut, double& unspentBal);

    void setTxInput(std::vector<TxIn> &txinputs, std::vector<UnspentTxOut> &txoutput);
    void setTxOutput(std::vector<TxOut> &txoutputs, std::string& ccAddress, double& ccAmt, double& unspentBal);

    void updateWalletBalance();
    void writeWalletToDisk();
    UnspentTxOutPool* UTXO_pool;

    std::pair<std::string, std::string> keyPair;
    double balance_;

    // don't need this
    std::vector< std::pair<std::string, std::string> > rawKeyPairs;
    std::vector< std::pair<std::string, std::string> > walletAddressKeyPairs;
    std::map< std::string, double > walletBalances;

};

#endif //WALLET_H
