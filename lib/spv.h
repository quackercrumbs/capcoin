#include <iostream>
#include <sstream>
#include "wallet.h"

class SPV_TXN {
public:
  SPV_TXN(std::string&, std::string&, std::string&, double);
  std::string private_key, public_key;
  std::string to_address;
  double amount;
};

SPV_TXN JSONtoSPV(const std::string& txnString);
Transaction* process_spv(const std::string& txnString, TransactionPool* txpool, UnspentTxOutPool* utxopool);
