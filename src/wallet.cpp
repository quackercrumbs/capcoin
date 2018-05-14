#include "wallet.h"

#define WALLETDIR "wallet.capcoin"

/* key order:
 * privatekey - > publickey
*/

Wallet::Wallet(TransactionPool* txpool, UnspentTxOutPool* UTXO): txpool_(txpool), utxopool_(UTXO) {


    if( !walletFileIsValid() ){
      // no valid wallet file found.  Create Key pairs, and save to new wallet file
      makeKeyPair();
      writeWalletToDisk();
      initWallet();
    }
    else{
      // wallet file is found, initialize
      initWallet();
    }

    validateKeyPairs();

    myAddress = keyPair.second;

    // std::cout << "keypairs: "<< keyPair.first << " => " << keyPair.second << std::endl;
    // std::cout << "picosha2: "<< picosha2::hash256_hex_string(keyPair.first) << " => " << picosha2::hash256_hex_string(keyPair.second) << std::endl;

    // walletFileIsValid();


    //check if wallet file present; init wallet address vectors
    //

}

std::string Wallet::GetAddress() {
  return myAddress;
}

double Wallet::Balance() {
  updateWalletBalance();
  return balance_;
}

bool Wallet::walletFileIsValid(){

  std::ifstream walletFile(WALLETDIR);
  if( !walletFile.good() ){
      std::cout << "no valid wallet file found" << std::endl;
      return false;
  }
  std::cout << "wallet file is valid.  " << std::endl;
  unsigned int count = 0;
  char c;
  while(walletFile.get(c))
    count++;
  std::cout << "File is " << count << " bytes." << std::endl;
  std::cout << "Size of char: "<< sizeof(char) << std::endl;
  std::cout << "ECC: "<< ECC_BYTES<< std::endl;
  walletFile.close();
  return true;

}

void Wallet::makeKeyPair(){
    uint8_t p_publicKey[ECC_BYTES+1];
    uint8_t p_privateKey[ECC_BYTES];
    if(0 == ecc_make_key(p_publicKey, p_privateKey)){
        // handle error
        std::cerr << "unable to create address" << std::endl;
        return;
    }
    std::string pbk = /*(char *)p_publicKey; */ keyToHexString(p_publicKey, ECC_BYTES+1);
    std::string prk = /*(char *)p_privateKey; */ keyToHexString(p_privateKey, ECC_BYTES);
    // std::cout << "keys:  " << pbk << prk << std::endl;
    keyPair = std::make_pair(prk, pbk);
}

std::string Wallet::makeSignature(std::string hash) {
  uint8_t p_privateKey[ECC_BYTES];
  keyToBytes(keyPair.first, p_privateKey);

  uint8_t p_hash[ECC_BYTES];
  keyToBytes(hash, p_hash);

  uint8_t p_signature[ECC_BYTES*2];

  ecdsa_sign(p_privateKey, p_hash, p_signature);

  std::string hexString = keyToHexString(p_signature, ECC_BYTES*2);

  return hexString;
}

bool Wallet::validateSignature(std::string publicKey, std::string hash, std::string signature)
{
  uint8_t p_publicKey[ECC_BYTES+1];
  keyToBytes(publicKey, p_publicKey);

  uint8_t p_hash[ECC_BYTES];
  keyToBytes(hash, p_hash);

  uint8_t p_signature[ECC_BYTES*2];
  keyToBytes(signature, p_signature);

  return ecdsa_verify(p_publicKey, p_hash, p_signature);
}

void Wallet::validateKeyPairs(){

  uint8_t p_publicKey[ECC_BYTES+1];
  uint8_t p_privateKey[ECC_BYTES];

  /*
  for(int i=0; i < ECC_BYTES; i++)
    p_privateKey[i] = keyPair.first[i];
  for(int i=0; i < ECC_BYTES+1; i++)
    p_publicKey[i] = keyPair.second[i];
  */

  keyToBytes(keyPair.first, p_privateKey);
  keyToBytes(keyPair.second, p_publicKey);

  uint8_t p_hash[ECC_BYTES];
  uint8_t p_signature[ECC_BYTES*2];

  for(int i=0; i<ECC_BYTES; i++)
    p_hash[i]=i;

    // creates a signature
   ecdsa_sign(p_privateKey, p_hash, p_signature);
   // verifies signature
  if( ecdsa_verify(p_publicKey, p_hash, p_signature) == 0 )
    std::cerr << "error: signature unverified" << std::endl;
  else
    std::cerr << "signature verified!!!!" << std::endl;
}

void Wallet::initWallet(){

    //open file
    std::ifstream walletFile(WALLETDIR);


    //read in
    //each line is an address:private key \n public
    std::vector<std::string> addressPairsFromFile( (std::istream_iterator<std::string>(walletFile)), \
                                                    std::istream_iterator<std::string>());
    // std::string prk, pbk;
    // for(int i=0; i<ECC_BYTES; i++)
    //   prk += walletFile.get();
    // for(int i=ECC_BYTES; i<=2*ECC_BYTES; i++)
    //   pbk += walletFile.get();
    // std::vector<std::string> addressPairsFromFile{prk, pbk};

    //empty wallet file
    if(addressPairsFromFile.empty()){
        valid = false;
        // no address pairs
        return;
    }

    //ensure correct number of keypairs is present
    if(addressPairsFromFile.size() != 2){
        //wallet file is corrupt, improper number of pairs
        valid = false;
        for(auto address: addressPairsFromFile)
          std::cout << "wallet: " << address << std::endl;
        std::cerr << "error: wallet file corrupt" << std::endl;
        return;
    }

    std::string privatekey = addressPairsFromFile[0];
    std::string publickey = addressPairsFromFile[1];

    keyPair = std::make_pair(privatekey, publickey);



    valid = true;
    //close wallet file handler
    walletFile.close();

}

bool Wallet::isWalletActive(){
    return valid;
}

void Wallet::writeWalletToDisk(){
    std::ofstream walletFile(WALLETDIR, std::ios_base::out);
    walletFile << keyPair.first << "\n" << keyPair.second;
    // std::cout << "writeWalletToDisk ran" << std::endl;
}

void Wallet::send(double ccAmt, std::string toCCAddresses){

    Transaction* tx = createTransaction(toCCAddresses, ccAmt);

    if(tx == nullptr){
      std::cerr << "error: failed to create transaction." << std::endl;
      return;
    }

    utxopool_->AddTxn(*tx);

}

Transaction * Wallet::createTransaction(std::string& ccAddress, double& ccAmt){

    //todo:
    //error handling in Wallet::send

    updateWalletBalance();

    double unspentBal=0.0;
    std::vector<UnspentTxOut> unspentOutputs;
    std::vector<TxIn> tx_inputs;
    std::vector<TxOut> tx_outputs;

    if(0 == getUnspentTx(ccAmt, unspentOutputs, unspentBal)){
        // balance too low, or UTxOs unavailable
        std::cerr << "error: funds currently unavailable for this transaction." << std::endl;
        return nullptr;
    }

    updatePending();
    if((ccAmt + pending_) > balance_){
      // not enough with outgoing pending transactions in the pool
      std::cerr << "error: funds present, but not enough including pending transactions." << std::endl;
      return nullptr;
    }

    setTxInput(tx_inputs, unspentOutputs);

    setTxOutput(tx_outputs, ccAddress, ccAmt, unspentBal);

    Transaction * currTx = new Transaction(tx_inputs, tx_outputs);

    return currTx;

}

void Wallet::setTxInput(std::vector<TxIn> &txinputs, std::vector<UnspentTxOut> &txoutputs){

    for(int i = 0; i < txoutputs.size(); i++){

        UnspentTxOut txoutput = txoutputs.at(i);

        std::string txinputId = txoutput.GetId();
        std::string txinputSignature = makeSignature(txoutput.Hash());
        size_t txinputIndex =  txoutput.GetIndex();

        TxIn t_txinput(txinputId, txinputSignature, txinputIndex);
        txinputs.push_back(t_txinput);
    }
}

//by default changeback address is first address owned (first address in wallet file)
void Wallet::setTxOutput(std::vector<TxOut> &txoutputs, std::string& ccAddress, double& ccAmt, double& unspentBal){

    //todo:make setter for TxOut
    TxOut t_txoutput(ccAddress, ccAmt);
    txoutputs.push_back(t_txoutput);

    // note: balance can be zero
    if(unspentBal >= 0){

        std::string selfCC_address = myAddress;
        TxOut t_txoutput(selfCC_address, unspentBal);
        txoutputs.push_back(t_txoutput);
    }

}

//sets balances
void Wallet::updateWalletBalance(){

  balance_ = utxopool_->balance(myAddress);

}

void Wallet::updatePending(){
  TransactionPool tp(*txpool_);

  double spent = 0;
  while(tp.size() != 0){
    Transaction t = tp.front();
    tp.pop();

    std::string address = t.GetTxOuts().back().GetAddress();
    if(address != myAddress)
      continue;

    std::vector<TxOut> txouts{t.GetTxOuts()};
    // ignore the change returned in last TxOut
    for(int i=0; i<txouts.size()-1; i++)
      spent += txouts[i].GetAmount();
  }
  pending_ = spent;
}

int Wallet::getUnspentTx(const double& ccAmt, std::vector<UnspentTxOut>& vtxOut, double& unSpentBal){

    std::string txOutAddress;
    if(balance_ < ccAmt)
      return 0;

    std::map<unsigned int, bool> usedTxns;

    TransactionPool tmp_pool(*txpool_);
    while(tmp_pool.size() != 0) {
      Transaction t = tmp_pool.front();
      tmp_pool.pop();
      if(t.GetTxOuts().back().GetAddress() == myAddress)
        for(auto in: t.GetTxIns())
          usedTxns[in.GetIndex()] = true;
    }

    std::vector<unsigned int> unusedTxns;

    if(utxopool_->operator[](myAddress) != nullptr) {
      auto uTxOuts = *(utxopool_->operator[](myAddress));
      for(auto tx: uTxOuts) {
        auto search = usedTxns.find(tx.GetIndex());
        if(search == usedTxns.end()) {
          unSpentBal += tx.GetAmount();
          vtxOut.push_back(tx);
        }
        if(unSpentBal >= ccAmt){
          unSpentBal -= ccAmt;
          return 1;
        }
      }
    }
    //failed to find enough addrBals to fulfill order
    return 0;
}

void Wallet::test() {
  UnspentTxOutPool * realPool, testPool;

  realPool = utxopool_;
  utxopool_ = &testPool;

  std::string seed = "";
  std::string toAddress = picosha2::hash256_hex_string(seed);
  double initial = 50.00;

  UnspentTxOut u("0", myAddress, 0, initial);

  utxopool_->insert(u);

  for(int i=0; i<50; i++)
    send(1.0, toAddress);

  if(utxopool_->balance(toAddress) != initial)
    std::cerr << "error: bulk transaction test failed" << std::endl;

  for(int i=0; i<50; i++) {
    std::stringstream ss;
    ss << i+1;
    UnspentTxOut u(ss.str(), myAddress, 0, 1.00);
    utxopool_->insert(u);
  }

  send(initial, toAddress);

  if(utxopool_->balance(toAddress) != initial*2)
    std::cerr << "error: multi-input transaction test failed" << std::endl;

  // clean up
  utxopool_ = realPool;

}

Wallet::~Wallet(){

    // std::ofstream walletOut(WALLETDIR, std::ios_base::out);
    //   walletOut << keyPair.first << keyPair.second;
    // walletOut.close();

}
