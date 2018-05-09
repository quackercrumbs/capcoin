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
