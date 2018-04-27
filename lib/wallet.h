#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <stdint.h>
#include <vector>

#include "ecc.h"
#include "transaction.h"

class Wallet{
public:

    Wallet();

    Transaction *createTransaction(std::string address="test", double amount=0) {
            std::vector<TxIn> in;
            std::vector<TxOut> out;
            in.push_back({"ADDRESSTEST0", "SIGNATURETEST0", 0});
            in.push_back({"ADDRESSTEST1", "SIGNATURETEST1", 1});
            in.push_back({"ADDRESSTEST2", "SIGNATURETEST2", 2});
            in.push_back({"ADDRESSTEST3", "SIGNATURETEST3", 3});
            in.push_back({"ADDRESSTEST4", "SIGNATURETEST4", 4});
            out.push_back({"ADDRESSTEST0", 20});
            out.push_back({"ADDRESSTEST1", 30});
            out.push_back({"ADDRESSTEST2", 40});
            out.push_back({"ADDRESSTEST3", 50});
            out.push_back({"ADDRESSTEST4", 60});
            auto a = new Transaction(in, out);
            return a;
    }

    double getBal();

private:

    void createWallet();
    void getAddress();
    void initAddresses();
    void initKeyPair(uint8_t p_publicKey[ECC_BYTES+1], uint8_t p_privateKey[ECC_BYTES]);
    std::string walletaddress;
    double balance();

};

#endif //WALLET_H
