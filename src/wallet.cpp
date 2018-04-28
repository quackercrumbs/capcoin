#include "wallet.h"

#define WALLETDIR "wallet.capcoin"


/**
 *
 * key order:
 * privatekey - > publickey
 *
 * */

Wallet::Wallet(UnspentTxOutPool& UTXO):UTXO_pool{&UTXO}{
    //check if wallet file present; init wallet address vectors
    initWallet();

    if(isEmpty()){
        //todo: delete cout
        std::cout << "no wallet";
        createWallet();
    }
    //verify validate addresses
    validateAddresses();
    initAddresses();
}

Wallet::Wallet():UTXO_pool{nullptr}{
    //check if wallet file present; init wallet address vectors
    initWallet();

    if(isEmpty()){
        //todo: delete cout
        std::cout << "no wallet";
        createWallet();
    }
    //verify validate addresses
    //convert raw keys to CC addresses
    validateAddresses();
    initAddresses();

}

void Wallet::validateAddresses(){

    for(int i = 0; i < rawKeyPairs.size(); i++){
        //todo: some validator function
    }

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
    std::vector<std::string> addressPairsFromFile((std::istream_iterator<std::string>(walletFile)), \
                                                    std::istream_iterator<std::string>());

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
    //set private facing rawkeypairs vect
    for(int i = 0; i < addressPairsFromFile.size(); i++){

        std::string privatekey = addressPairsFromFile[i];
        std::string publickey = addressPairsFromFile[++i];

        std::pair<std::string, std::string> kp = std::make_pair(privatekey, publickey);
        rawKeyPairs.emplace_back(kp);

    }

    empty = false;
    //close wallet file handler
    walletFile.close();

}

bool Wallet::isEmpty() {
    return empty;
}

void Wallet::makeKeyPairs(int quantity){

    int idx;
    if(rawKeyPairs.empty())
        idx = 0;
    else {
        idx = rawKeyPairs.size();
        quantity += rawKeyPairs.size();
    }


    for( ; idx < quantity; idx++){

        uint8_t p_publicKey[ECC_BYTES+1];
        uint8_t p_privateKey[ECC_BYTES];

        if(0 == ecc_make_key(p_publicKey, p_privateKey)){
            //todo:
            //unable to create address
            //handle
        }

        std::string pbk = (char *)p_publicKey;
        std::string prk = (char *)p_privateKey;
        rawKeyPairs.emplace_back(std::make_pair(prk, pbk));

    }

}

void Wallet::createWallet(){

    makeKeyPairs(1);
    writeWalletToDisk();
}


void Wallet::writeWalletToDisk(){

    std::ofstream walletFile(WALLETDIR, std::ios_base::out);

    for(int i = 0; i < walletAddressKeyPairs.size(); i++){

        walletFile << walletAddressKeyPairs[i].first << "\n" \
                << walletAddressKeyPairs[i].second << "\n";
    }
}



void Wallet::createAddress(int quantity) {

    makeKeyPairs(quantity);
    initAddresses(quantity);

}



//todo: user specifies from which (from) addresses to choose from
//most likely called by a more abstracted public function
Transaction* Wallet::createTransaction(std::vector<TxIn>& tx_inputs, \
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

//hashes address, from keys to addresses
void Wallet::initAddresses(int quantity) {

    int idx;
    if(rawKeyPairs.empty())
        idx = 0;
    else {
        idx = quantity;
        quantity += rawKeyPairs.size();
    }
    for(; idx < quantity; idx++){

        walletAddressKeyPairs[idx].first = picosha2::hash256_hex_string( \
        picosha2::hash256_hex_string(rawKeyPairs[idx].first));

        walletAddressKeyPairs[idx].second = picosha2::hash256_hex_string( \
        picosha2::hash256_hex_string(rawKeyPairs[idx].second));

    }

    updateWalletBalance();

}

std::vector<std::pair<std::string, double> > Wallet::getWalletBalance(){

    return walletBalances;
}

//set balances
void Wallet::updateWalletBalance(){

    for(int i = 0; i < walletAddressKeyPairs.size(); i++){

        std::string publickey = walletAddressKeyPairs[i].first;

        //returns double
        //UTXO_pool.search(publickey);
        //walletAddressKeyPairs[i].second = UTXO_pool.search(publickey);

    }
    //todo: search db, rematch, sum, and store value in private member vect
}



//void Wallet::shutdownWallet(){
//    //receives kill request
//    //stop/kill requests
//    //flush changes saves to disk
//}