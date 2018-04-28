#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include "ecc.h"
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

//
//struct comparator {
//    bool operator() (const double& left, const double& right) const {return left<right;}
//};




class Wallet{


public:

    Wallet();
    bool isEmpty();

    Transaction* createTransaction(const UnspentTxOutPool& UTXO_pool, \
                                                    std::vector<TxIn>& tx_inputs, \
                                                    std::vector<TxOut>& tx_outputs);
    //may make of type address
    std::vector<std::pair<std::string, double> > getWalletBalance();
    //void Wallet::shutdownWallet();

private:

    bool empty;
    void createWallet();
    void initAddresses(); //fills address vector wallet address called on check after call to getWalletBalances
    void initKeyPair();
    void initWallet();
    void initBalances();
    void createAddress(int quanity);
    void updateWalletBalance();
    void writeWalletToDisk();

    std::vector< std::pair<uint8_t, uint8_t> > rawKeyPairs;

    std::vector< std::pair<std::string, std::string> > walletAddressKeyPairs;
    std::vector< std::pair<std::string, double> > walletBalances;



};



#endif //WALLET_H
