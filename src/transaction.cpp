#include "transaction.h"

Transaction::Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs): txIns_{std::move(ins)}, txOuts_{std::move(outs)}{
  id_ = CalcHash();
}

std::string Transaction:: hash() const{
    return id_;
}

Transaction::Transaction(const Transaction& beta){
  for(TxIn x: beta.txIns_){
    TxIn temp = x;
    txIns_.push_back(temp);
  }
  for(TxOut y: beta.txOuts_){
    TxOut temp = y;
    txOuts_.push_back(temp);
  }
  id_ = beta.id_;
}

bool Transaction:: operator == (const Transaction& beta) const{
  return id_ == beta.id_ ? true : false;
}

bool Transaction:: Validate(UnspentTxOutPool& source) const{
  if(id_ != CalcHash() || !OneToOne(source) || !SignaturesValid(source))
    return false;
  return true;
}

bool Transaction:: SignaturesValid(UnspentTxOutPool& source) const{

  // by convention: last txout is always to self
  std::string address = txOuts_.back().GetAddress();

  for (auto x: txIns_){

    std::string hash {source.GetHash(x)};
    std::string sig  = x.GetSignature();

    if(!validSignature(address, hash, sig)) {
      std::cerr << "error: invalid signature" << std::endl;
      return false;
    }

  }
  return true;
}


bool Transaction:: OneToOne(UnspentTxOutPool& source) const{
  double inAmt = 0, outAmt = 0;
  for (TxIn x: txIns_){
    UnspentTxOut* temp = source.FindFromIn(x);
    if (temp == nullptr) continue;

    UnspentTxOut t{*temp};
    double dt = t.GetAmount();
    inAmt = inAmt + dt;
  }
  for (TxOut y: txOuts_){
    outAmt = outAmt + y.GetAmount();
    // std::cout << y.GetAmount() << std::endl;
  }
  if(inAmt != outAmt){
    std::cerr << "error: not one to one" << std::endl;
    std::cerr << inAmt << " != " << outAmt << std::endl;
  }
  return inAmt == outAmt ? true : false;
}

std::string Transaction:: CalcHash() const{

  std::stringstream accuInTx, accuOutTx;
  std::string inHash, outHash;
 //for each transaction in txIns_, append its id (signature?) and index to accuInTx
  for (auto i : txIns_)
   accuInTx << i.GetId() << i.GetSignature() << i.GetIndex();
  inHash = picosha2::hash256_hex_string(accuInTx.str());
 //for each transaction in txOuts_, append its address and amount to accuOutTx
  for (auto i : txOuts_)
   accuOutTx << i.GetAddress() << i.GetAmount();
  outHash = picosha2::hash256_hex_string(accuOutTx.str());
 //add the two strings and hash them for the id
 return picosha2::hash256_hex_string(inHash + outHash);

}

std::vector<TxIn> Transaction::GetTxIns() const{
    return txIns_;
}

std::vector<TxOut> Transaction::GetTxOuts() const{
    return txOuts_;
}

std::ostream& operator<<(std::ostream& os, const Transaction& t) {
    os << "================ TRANSACTION ================" << std::endl;
    os << "id:" << t.id_ << std::endl;
    for(auto txin = t.txIns_.begin(); txin != t.txIns_.end(); ++txin) {
        // Replace with txin os override
        os << *txin << std::endl;
    }
    for(auto txout = t.txOuts_.begin(); txout != t.txOuts_.end(); ++txout) {
        // Replace with txouts os override
        os << *txout << std::endl;
    }
    os << "=============================================" << std::endl;

    return os;
}

std::string keyToHexString(uint8_t* key, size_t no_bytes) {
  std::stringstream ss;
  for(int i=0; i<no_bytes; i++) {
    ss << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) key[i];
  }
  return ss.str();
}

void keyToBytes(const std::string& hexKey, uint8_t* key) {
  std::string hex_byte="";
  uint8_t x;

  for(int i=0; i< hexKey.size(); i++) {
    hex_byte += hexKey[i];

    if(i%2 != 0) {
      x = strtoul(hex_byte.c_str(), NULL, 16);
      hex_byte = "";
      key[i/2] = x;
    }
  }

}

bool validSignature(std::string& publicKey, std::string& hash, std::string& signature)
{
  uint8_t p_publicKey[ECC_BYTES+1];
  keyToBytes(publicKey, p_publicKey);

  uint8_t p_hash[ECC_BYTES];
  keyToBytes(hash, p_hash);

  uint8_t p_signature[ECC_BYTES*2];
  keyToBytes(signature, p_signature);

  return ecdsa_verify(p_publicKey, p_hash, p_signature);
}
