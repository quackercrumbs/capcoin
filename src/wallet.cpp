#include "wallet.h"

#define WALLETDIR "wallet.capcoin"

/**
 *
 * key order:
 * privatekey - > publickey
 *
 * */

Wallet::Wallet(UnspentTxOutPool* UTXO):UTXO_pool(UTXO) {

    //check if wallet file present; init wallet address vectors
    initWallet();

    if(isWalletActive()){

        createWallet();
    }

    //verify validate addresses
    validateRawAddresses();
    initAddresses();

}

//todo:
//collaspe constructors
//still needed for offline use, no UTXO present
Wallet::Wallet():UTXO_pool{nullptr}{
    //check if wallet file present; init wallet address vectors
    initWallet();

    if(isWalletActive()){
        //todo: delete cout
        std::cout << "no wallet";
        createWallet();
    }
    //verify validate addresses
    //convert raw keys to CC addresses
    validateRawAddresses();
    initAddresses();

}

void Wallet::validateRawAddresses(){

    for(int i = 0; i < rawKeyPairs.size(); i++){
        //todo: -hugo
        //validator function: stack based
    }

}

void Wallet::initWallet(){

    //open file
    std::ifstream walletFile(WALLETDIR);

    if(!walletFile.good()){
        //no wallet file
        valid = false;
        return;
    }

    //read in
    //each line is an address:private key \n public
    std::vector<std::string> addressPairsFromFile((std::istream_iterator<std::string>(walletFile)), \
                                                    std::istream_iterator<std::string>());

    //empty wallet file
    if(addressPairsFromFile.empty()){
        valid = true;
        return;
    }

    //ensure correct number of keypairs is present
    if(addressPairsFromFile.size()%2 != 0){
        //wallet file is corrupt, improper number of pairs
        valid = true;
        return;
    }

    //store address keypairs
    //set private facing rawkeypairs vect
    for(int i = 0; i < addressPairsFromFile.size(); i++){

        std::string privatekey = addressPairsFromFile[i];
        std::string publickey = addressPairsFromFile[++i];

        std::pair<std::string, std::string> kp = std::make_pair(privatekey, publickey);
        rawKeyPairs.push_back(kp);

    }

    valid = false;
    //close wallet file handler
    walletFile.close();

}

bool Wallet::isWalletActive(){
    return valid;
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
        rawKeyPairs.push_back(std::make_pair(prk, pbk));

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

void Wallet::createAddress(int quantity){

    makeKeyPairs(quantity);
    initAddresses(quantity);

}

void Wallet::send(double ccAmt, std::string toCCAddresses){

    Transaction* tx = createTransaction(toCCAddresses, ccAmt);

    //todo: -hugo
    //send to transaction pool

}

//hashes address, from keys to addresses
void Wallet::initAddresses(int quantity){

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

Transaction* Wallet::createTransaction(std::string& ccAddress, double& ccAmt){

    //todo: -hugo
    //error handling in Wallet::send

    updateWalletBalance();

    double unspentBal;
    std::vector<TxOut> unspentOutputs;
    std::vector<TxIn> tx_inputs;
    std::vector<TxOut> tx_outputs;

    if(0 == gatherUnspentOutputs(ccAmt, unspentOutputs, unspentBal)){
        //todo: -hugo
        //not able to fulfill request: low balance - handle or print
    }

    setTxInput(tx_inputs, unspentOutputs);

    setTxOutput(tx_outputs, ccAddress, ccAmt, unspentBal);

    Transaction* currTx = new Transaction(tx_inputs, tx_outputs);

    return currTx;

}

void Wallet::setTxInput(std::vector<TxIn> &txinputs, std::vector<TxOut> &txoutputs){

    for(int i = 0; i < txoutputs.size(); i++){

        std::string txinputAddress = txoutputs.at(i).GetAddress();
        TxIn t_txinput(txinputAddress);
        txinputs.push_back(t_txinput);
    }
}

//by default changeback address is first address owned (first address in wallet file)
int Wallet::setTxOutput(std::vector<TxOut> &txoutputs, std::string& ccAddress, double& ccAmt, double& unspentBal){

    //todo:make setter for TxOut
    TxOut t_txoutput(ccAddress, ccAmt);
    txoutputs.push_back(t_txoutput);

    if(unspentBal > 0){

        std::string selfCC_address;
        TxOut t_txoutput(selfCC_address, unspentBal);
        txoutputs.push_back(t_txoutput);
    }

}

std::vector<std::pair<std::string, double> >* Wallet::getWalletBalance(){

    return &walletBalances;
}

//sets balances
void Wallet::updateWalletBalance(){

    for(int i = 0; i < walletAddressKeyPairs.size(); i++){

        std::string ccPublicAddress = walletAddressKeyPairs[i].first;

        //todo:implement UTXO cc address based search
        //returns
        //UTXO_pool.search(publickey);
        //walletAddressKeyPairs[i].second = UTXO_pool.search(publickey);

    }
}

int Wallet::gatherUnspentOutputs(double& ccAmt, std::vector<TxOut>& vtxOut, double& unSpentBal){

    double balanceSoFar = 0.00;

    std::string txOutAddress;
    double txOutAddrBal;

    //loop through wallet balances until the aggregate funds of addr can cover the ccAmt requested
    for(int i = 0; i < walletBalances.size(); i++) {

        //track the quantity available so far
        balanceSoFar += walletBalances[i].second;

        //push ith entry of wallBal into txOut vec
        txOutAddress = walletBalances[i].first;
        txOutAddrBal = walletBalances[i].second;
        vtxOut.push_back(TxOut(txOutAddress, txOutAddrBal));

        //check if threshold reached
        if (balanceSoFar >= ccAmt) {

            //ensure tx will be all consuming
            unSpentBal = balanceSoFar - ccAmt;

            txOutAddress = walletBalances[i].first;
            txOutAddrBal = walletBalances[i].second;
            vtxOut.push_back(TxOut(txOutAddress, txOutAddrBal));

            //vxt initialize, success
            return 1;
        }
    }
    //failed to find enough addrBals to fulfil order
    return 0;
}

Wallet::~Wallet(){

  std::ofstream walletOut(WALLETDIR, std::ios_base::out);
  for (int i = 0; i < rawKeyPairs; i++){
    walletOut << rawKeyPairs[i].first << rawKeyPairs[i].second << "\n" ;
  }
  walletOut.close();

}

//void Wallet::shutdownWallet(){
//    //receives kill request
//    //stop/kill requests
//    //flush changes saves to disk
//}
