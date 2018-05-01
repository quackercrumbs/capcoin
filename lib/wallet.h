#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <stdint.h>
#include "ecc.h"


class Wallet{
public:

    Wallet();
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
