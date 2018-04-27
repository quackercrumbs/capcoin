#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <string>

//todo:seperate implementation

class keyPair {
public:
    keyPair() {

        //    uint8_t p_publicKey[ECC_BYTES+1];
        //    uint8_t p_privateKey[ECC_BYTES];
        //  generate keypair using ecc and set member variables

    }
    keyPair(std::string p_privateKey, std::string p_publicKey):publicKeystring(p_publicKey), privateKeystring(p_privateKey) {

    }

    std::string getPublicKey()const {
        return publicKeystring;

    }

    std::string getPrivateKey()const {
        return privateKeystring;
    }

    void setPublicKey(std::string& p_publicKey){
        publicKeystring = p_publicKey;
    }

    void setPrivateKey(std::string& p_privateKey){
        privateKeystring = p_privateKey;
    }

private:
    std::string publicKeystring;
    std::string privateKeystring;
    //todo:validate is possible with ecc function

};


#endif //KEYPAIR_H
