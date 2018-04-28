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



/*
 * AddressFormat:
 * 4 char prefix[ CC (for capcoin) + XX (place for future stuff, default 00) ] + address + 4 char checksum
 *
 * example address:
 * CC00BvBMSEYstWetqTFn5Au4m4GFg7xJaNvn2
 * similar to bitcoin, but our own
 * */

//todo:separate thread writes newly formed keypairs to wallet file ((appends))

class Wallet{


public:

    Wallet();
    Wallet(UnspentTxOutPool& UTXO);
    Transaction* createTransaction(std::vector<TxIn>& tx_inputs, std::vector<TxOut>& tx_outputs);
    std::vector<std::pair<std::string, double> > getWalletBalance();
    void createAddress(int quantity);

    bool isEmpty();
    //void Wallet::shutdownWallet();

private:

    bool empty;
    void initAddresses(int quantity=0);
    void makeKeyPairs(int quantity=0);
    void createWallet();
    void initWallet();
    void validateAddresses();

    void updateWalletBalance();
    void writeWalletToDisk();
    UnspentTxOutPool* UTXO_pool;
    std::vector< std::pair<std::string, std::string> > rawKeyPairs;
    std::vector< std::pair<std::string, std::string> > walletAddressKeyPairs;
    std::vector< std::pair<std::string, double> > walletBalances;


};



#endif //WALLET_H
