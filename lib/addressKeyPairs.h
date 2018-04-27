#ifndef ADDRESSKEYPAIRS_H
#define ADDRESSKEYPAIRS_H



//todo:seperate implementation

class AddresskeyPair{
public:
    AddresskeyPair(std::shared_ptr<double> b_balance):publicKeystring(), privateKeystring(), valid(false), balance(b_balance){

    }

    AddresskeyPair():publicKeystring(), privateKeystring(), valid(false), balance(0){

    }


    std::string getPublicKey_base58()const {
        return publicKeystring;

    }

    std::string getPrivateKey_base58()const {
        return privateKeystring;
    }

    double& getBalance() const {
        return balance;
    }

    void setBalance(double& b_balance) {
        balance = b_balance;
    }

    bool validate()const {
        return valid;
    }

    void setPublicKey(std::string& p_publicKey){
        publicKeystring = p_publicKey;
    }

    void setPrivateKey(std::string& p_privateKey){
        privateKeystring = p_privateKey;
    }

    void setValidity(bool isValid) {
        valid = isValid;
    }

private:
    std::string publicKeystring;
    std::string privateKeystring;
    double& balance;
    //todo: validate self (validate keys)
    bool valid;

};


#endif //ADDRESSKEYPAIRS_H
