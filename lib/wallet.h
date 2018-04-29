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

// required for further testing:
// check todo's
// -UTXO search method/UTXO rework
// -safe kill wallet, flush
// (currently only available in destructor, or safe exit)
// -TxIn/TxOut mutators
// -shared access to transactionpool
// -address pretty printer/maker
// -CC address validator, alternativly rawaddressvalidator
// -offline wallet usage (i.e no UTXO)
// -address disponal (corrupt, burned, etc.)

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
    ~Wallet();
    Wallet(UnspentTxOutPool* UTXO);
    void send(double ccAmt, std::string toCCAddresses);
    std::vector<std::pair<std::string, double> >* getWalletBalance();
    void createAddress(int quantity);

    bool isWalletActive();
    //void Wallet::shutdownWallet();

private:

    bool valid;
    Transaction* createTransaction(std::string& ccAddress, double& ccAmt);
    void initAddresses(int quantity=0);
    void makeKeyPairs(int quantity=0);
    void createWallet();
    void initWallet();
    void validateRawAddresses();

    int gatherUnspentOutputs(double& ccAmt, std::vector<TxOut>& vtxOut, double& unspentBal);

    void setTxInput(std::vector<TxIn> &txinputs, std::vector<TxOut> &txoutput);
    int setTxOutput(std::vector<TxOut> &txoutputs, std::string& ccAddress, double& ccAmt, double& unspentBal);

    void updateWalletBalance();
    void writeWalletToDisk();
    UnspentTxOutPool* UTXO_pool;
    std::vector< std::pair<std::string, std::string> > rawKeyPairs;
    std::vector< std::pair<std::string, std::string> > walletAddressKeyPairs;
    std::vector< std::pair<std::string, double> > walletBalances;


};



#endif //WALLET_H
