#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <memory>
#include "ecc.h"
#include "transaction.h
#include "utxoutpool.h"

/*
 * AddressFormat:
 * 4 char prefix[ CC (for capcoin) + XX (place for future stuff, default 00) ] + address + 4 char checksum
 *
 * example address:
 * CC00BvBMSEYstWetqTFn5Au4m4GFg7xJaNvn2
 * similar to bitcoin, but our own
 * */



#include "json.hpp"
namespace wallet{

    void to_json(nlohmann::json& j, const AddresskeyPair& kp) {
        j = nlohmann::json{{"publickey", kp.getPublicKey_base58()}, {"privatekey", kp.getPrivateKey_base58()}, {"test", kp.validate()}};
    }

    void from_json(const nlohmann::json& j, AddresskeyPair& kp) {
        kp.setPublicKey(j.at("publickey").get<std::string>());
        kp.setPrivateKey(j.at("privatekey").get<std::string>());
        kp.setValidity(j.at("test").get<bool>());
    }
}




//todo:seperate thread writes newly formed keypairs to wallet file ((appends))

class Wallet{

public:

    Wallet();
    bool isEmpty();
    Transaction* createTransaction(const UnspentTxOutPool& UTXO_pool, \
                                                    std::vector<TxIn>& tx_inputs, \
                                                    std::vector<TxOut>& tx_outputs);
    //may make of type address
    std::vector<double> getWalletBalance();
    void Wallet::shutdownWallet();

private:

    bool empty;
    void createWallet();
    void initAddresses(); //fills address vector wallet address called on check after call to getWalletBalances
    void initKeyPair(uint8_t p_publicKey[ECC_BYTES+1], uint8_t p_privateKey[ECC_BYTES]);
    void initWallet();
    void initBalances();
    void createAddress();
    void updateWalletBalance();

    std::vector<AddresskeyPair> walletAddressKeyPairs;

    //std::vector<keyPair> walletkeyPairs;
    std::vector<double*> walletBalances;



};



#endif //WALLET_H

