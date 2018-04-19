#include "serialize.h"

Serialize::Serialize(Transaction& toBeSent){
  std::stringstream accumulator;
  accumulator << "\"TRANSACTION\":{\"ID\":\"" << toBeSent.hash() << "\"";
  for(TxIn in: toBeSent.GetTxIns()){
    accumulator << ",\"IN\":{\"ID\":\"" << in.GetId() << "\","
      << "\"SIG\":\"" << in.GetSignature() << "\","
      << "\"INDEX\":\"" << in.GetIndex() << "\"}";
  }
  for(TxOut out: toBeSent.GetTxOuts()){
    accumulator << ",\"OUT\":{\"AMOUNT\":\"" << out.GetAmount() << "\","
      << "\"ADDRESS\":\"" << out.GetAddress() << "\"}";
  }
  accumulator << "}";
  accumulator >> output;
}

Serialize::Serialize(Block& toBeSent){
  std::stringstream accumulator;
  accumulator << "\"BLOCK\":{\"INDEX\":\"" << toBeSent.GetIndex() << "\","
    << "\"TIMESTAMP\":\"" << toBeSent.GetTimestamp() << "\","
    << "\"DIFFICULTY\":\"" << toBeSent.GetDifficulty() << "\","
    << "\"NONCE\":\"" << toBeSent.GetNonce() << "\","
    << "\"HASH\":\"" << toBeSent.GetHash() << "\","
    << "\"PREVHASH\":\"" << toBeSent.GetPreviousHash() << "\"";
  for (Transaction tx: toBeSent.GetData()){
    Serialize txSerial(tx);
    accumulator << "," << txSerial.toString();
  }
  accumulator << "}";
  accumulator >> output;
}

std::string Serialize::toString(){
  return output;
}
