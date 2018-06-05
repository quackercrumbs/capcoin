#include "spv.h"

using namespace std;

SPV_TXN::SPV_TXN(string& prk, string& pbk, string& to, double amt)
  : private_key{prk}, public_key{pbk}, to_address{to}, amount{amt} {}

SPV_TXN JSONtoSPV(const string& txnString) {
  string prk, pbk, to;
  double amt;

  size_t start = 29, end = 29;
  while(txnString[end] != '\"') end++;
  prk = txnString.substr(start, end-start);
  start = end + 9;
  end = start;
  while(txnString[end] != '\"') end++;
  pbk = txnString.substr(start, end-start);
  start = end + 9;
  end = start;
  while(txnString[end] != '\"') end++;
  to = txnString.substr(start, end-start);
  start = end + 9;
  end = start;
  while(txnString[end] != '\"') end++;
  amt = strtod(txnString.substr(start, end-start).c_str(), NULL);
  SPV_TXN txn(prk,pbk,to,amt);

  return txn;
}

Transaction* process_spv(const string& txnString, TransactionPool* txpool, UnspentTxOutPool* utxopool) {
  size_t noQuotes = 0;
  for(auto c: txnString)
    if(c == '\"')
      noQuotes++;

  if(noQuotes != 20)
    return nullptr;

  SPV_TXN spv = JSONtoSPV(txnString);

  Wallet wa(spv.private_key, spv.public_key, txpool, utxopool);

  Transaction * t = wa.createTransaction(spv.to_address, spv.amount);

  return t;
}
