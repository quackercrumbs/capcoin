#include "wallet.h"

#define WALLETDIR "wallet.capcoin"

Wallet::Wallet(){

    //check if wallet file present; init wallet address vectors
    initWallet();

    if(isEmpty()){
        //todo: delete cout
        std::cout << "no wallet";
        createWallet();
    }

    //verify validate addresses
    //initAddresses();

}


void Wallet::initWallet() {

    //open file
    std::ifstream walletFile(WALLETDIR);

    if(!walletFile.good()){
        //no wallet file
        empty = true;
        return;
    }

    //read in
    //each line is an address:private key \n public
    std::vector<std::string> addressPairsFromFile((std::istream_iterator<std::string>(walletFile)), std::istream_iterator<std::string>());

    //empty wallet file
    if(addressPairsFromFile.empty()){
        empty = true;
        return;
    }

    //ensure correct number of keypairs is present
    if(addressPairsFromFile.size()%2 != 0){
        //wallet file is corrupt, improper number of pairs
        empty = true;
        return;
    }

    //store address keypairs
    //set public facing walletaddress
    for(int i = 0; i < addressPairsFromFile.size(); i++){

        std::string privatekey = addressPairsFromFile[i];
        std::string publickey = addressPairsFromFile[++i];

        std::pair<std::string, std::string> kp = std::make_pair(privatekey, publickey);
        walletAddressKeyPairs.emplace_back(kp);

        std::pair<std::string, double> addrBal = std::make_pair(publickey, 0.00);
        walletBalances.emplace_back(std::make_pair(publickey, 0.00));

    }

    empty = false;
    //close wallet file handler
    walletFile.close();

}

bool Wallet::isEmpty() {
    return empty;
}

//appends an address to wallet file
//todo: overload function createAddress(int numAddr) - create numAddr
//todo: overload createAddress(int numAddr, private key index or key itself) support HD WALLET
void Wallet::createAddress(int quantity) {

    uint8_t p_publicKey[ECC_BYTES+1], p_privateKey[ECC_BYTES];
    //creates keys
    //hashes
    //store in key vector

}



void Wallet::createWallet(){

    uint8_t p_publicKey[ECC_BYTES+1];
    uint8_t p_privateKey[ECC_BYTES];

    if(0 == ecc_make_key(p_publicKey, p_privateKey)){
        //unable to create address
        //handle
    }

    //rawKeyPairs.emplace_back(std::make_pair(p_publicKey, p_privateKey));
    initKeyPair();
    writeWalletToDisk();
}

void Wallet::writeWalletToDisk(){

    std::ofstream walletFile(WALLETDIR, std::ios_base::out);

    for(int i = 0; i < walletAddressKeyPairs.size(); i++){

        walletFile << walletAddressKeyPairs[i].first << "\n" \
                << walletAddressKeyPairs[i].second << "\n";
    }
}

//todo: error flag
void Wallet::initKeyPair(){
//
//    if (0 == ecc_make_key(p_publicKey, p_privateKey)){
//        std::cout << "Unable to create keys. \n";
//    }

}

//todo: user specifies from which (from) addresses to choose from
//most likely called by a more abstracted public function
Transaction* Wallet::createTransaction(const UnspentTxOutPool& UTXO_pool, \
                                                    std::vector<TxIn>& tx_inputs, \
                                                    std::vector<TxOut>& tx_outputs){

//    updateWalletBalance();
//
//    //perform greedy algorithm
//    std::sort(walletBalances.begin(), walletBalances.end());
//
//    double totalToSend = 0;
//    double currentAmount = 0;
//
//    for(auto i = 0; i < tx_outputs.size(); i++){
//        totalToSend += tx_outputs[i].GetAmount();
//    }
//
//    //begin setting outs - chosen via greedy method
//    for(auto i = 0; walletBalances.size(); i++){
//
//        currentAmount += walletBalances[i];
//        if (totalToSend < currentAmount) {
//            //take care of left over
//            //tx leftover back to wallet
//
//        } else {
//            tx_inputs[i].setAddress(walletAddressKeyPairs[i].getPublicKey_base58());
//            tx_inputs[i].setAmount(walletAddressKeyPairs[i].getBalance());
//            tx_inputs[i].sign(walletAddressKeyPairs[i].sign);
//        }
//
//        totalToSend -= currentAmount;
//
//    }

    Transaction* createdTransaction = new Transaction(tx_inputs, tx_outputs);

    return createdTransaction;

//    const findTxOutsForAmount = (amount: number, myUnspentTxOuts: UnspentTxOut[]) => {
//        let currentAmount = 0;
//        const includedUnspentTxOuts = [];
//        for (const myUnspentTxOut of myUnspentTxOuts) {
//            includedUnspentTxOuts.push(myUnspentTxOut);
//            currentAmount = currentAmount + myUnspentTxOut.amount;
//            if (currentAmount >= amount) {
//                const leftOverAmount = currentAmount - amount;
//                return {includedUnspentTxOuts, leftOverAmount}
//            }
//        }
//        throw Error('not enough coins to send transaction');
//    };


}

void Wallet::initAddresses() {

//    //check base58 encoding
//    for(auto& i : walletkeyPairs){
//        if(Base58::base58().is_valid(i.getPrivateKey_base58()) && Base58::base58().is_valid(i.getPublicKey_base58())){
//            i.setValidity(true);
//        } else
//            i.setValidity(false);
//
//    }
//    //todo:set type (i.e: normal, hierarchical, etc.)
//
//    //pull balances
//    initBalances();

}

//void Wallet::shutdownWallet(){
//    //receives kill request
//    //stop/kill requests
//    //flush changes saves to disk
//}

std::vector<std::pair<std::string, double> > Wallet::getWalletBalance(){

    std::vector<std::pair<std::string, double> > a;
    return a;
}

void Wallet::updateWalletBalance(){
    //todo: search db, rematch, sum, and store value in private member vect
}

void Wallet::initBalances(){

//    for(auto i; i < walletAddressKeyPairs.size(); i++){
//
//        AddresskeyPair* kp = &walletAddressKeyPairs[i];
//        auto wallet_address_base_58 = kp->getPublicKey_base58();
//
//        double cbalance = 0;
//        //todo: search unspentpool for wallet_address_ match and sum for balance
//        //store and populate <double>walletbalances
//        kp->setBalance(cbalance);
//        //links addresskeypairs with balance vector
//        walletBalances[i] = kp->getBalance();
//
//
//    }

}
