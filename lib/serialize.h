#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "transaction.h"
#include "block.h"

class Serialize{
public:
  Serialize(Transaction& toBeSent);
  Serialize(Block& toBeSent);
  std::string toString();
private:
  std::string output;
};

#endif
