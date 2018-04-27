#include "wallet.h"

#include <stdint.h>
#include "ecc.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>


#define WALLETDIR "wallet.txt"

Wallet::Wallet(){

    std::string walletaddr;
    uint8_t p_publicKey[ECC_BYTES+1], p_privateKey[ECC_BYTES];

    //open wallet
    std::ifstream inWallet(WALLETDIR);
    if(!inWallet.good()){
        //no wallet - create one

        //initKeyPair(p_publicKey, p_privateKey);
    }

    //read into memory
    std::vector<std::string> contents((std::istream_iterator<std::string>(inWallet)), std::istream_iterator<std::string>());
    inWallet.close();

    //verify valid addr
        //if invalid message







}



void Wallet::createWallet(){


}

//todo: error flag
void Wallet::initKeyPair(uint8_t p_publicKey[ECC_BYTES+1], uint8_t p_privateKey[ECC_BYTES]){

    if (0 == ecc_make_key(p_publicKey, p_privateKey)){
        std::cout << "Unable to create keys. \n";
    }

}
