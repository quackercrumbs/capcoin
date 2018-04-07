#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "transaction.h"
#include "block.h"
#include "blockchain.h"
#include <stdlib.h>

class Serialize{
public:
  void operator()(Transaction& toBeSent);
  void operator()(Block& toBeSent);
  void operator()(TxIn& toBeSent);
  void operator()(TxOut& toBeSent);
  std::string toString();
private:
  std::string output;
};
TxIn JSONtoTxIn(std::string instring);
TxOut JSONtoTxOut(std::string outstring);
Transaction JSONtoTx(std::string txnString);
Block JSONtoBlock(std::string blockString);

#endif
