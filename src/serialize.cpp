/*Serialize::Serialize(Transaction& toBeSent){
  Univalue holdsJSON(Univalue::VOBJ);
  holdsJSON.pushKV("ID", toBeSent.hash());
  holdsJSON.pushKV("INS", toBeSent.GetTxIns());
  holdsJSON.pushKV("OUTS", toBeSent.GetTxOuts());
}

Serialize::Serialize(Block& toBeSent){
  Univalue holdsJSON(Univalue::VOBJ);
  holdsJSON.pushKV("INDEX", toBeSent.GetIndex());
  holdsJSON.pushKV("TIME", toBeSent.GetTimestamp());
  holdsJSON.pushKV("DIFFICULTY", toBeSent.GetDifficulty());
  holdsJSON.pushKV("NONCE", toBeSent.GetNonce());
  holdsJSON.pushKV("HASH", toBeSent.GetHash());
  holdsJSON.pushKV("PREVIOUSBLOCKHASH", toBeSent.GetPreviousHash());
  holdsJSON.pushKV("DATA", toBeSent.GetData());
}

std::string toString(){
  return output;
}*/

Serialize::Serialize(Transaction& toBeSent){
  std::stringstream accumulator;
  accumulator << "\"TRANSACTION\":{\"ID\":\"" << toBeSent.hash() << "\"";
  for(TxIn in: toBeSent.GetTxIns()){
    accumulator << ",\"IN\":{\"ID\":\"" << in.GetID() << "\","
      << "\"SIG\":\"" << in.GetSignature() << "\","
      << "\"INDEX\":\"" << in.GetIndex() << "\"}";
  }
  for(TxIn out: toBeSent.GetTxOuts()){
    accumulator << ",\"OUT\":{\"AMOUNT\":\"" << out.GetAmount() << "\","
      << "\"ADDRESS\":\"" << out.GetAddress() << "\"},";
  }
  accumulator << "}";
  accumulator >> output;
}

Serialize::Serialize(Block& toBeSent){
  std::stringstream accumulator;
  accumulator << "\"BLOCK\":{\"INDEX\":\"" << toBeSent.GetIndex() << "\",";
    << "\"TIMESTAMP\":\"" << toBeSent.GetTimestamp() << "\","
    << "\"DIFFICULTY\":\"" << toBeSent.GetDifficulty() << "\","
    << "\"NONCE\":\"" << toBeSent.GetNonce() << "\","
    << "\"HASH\":\"" << toBeSent.GetHash() << "\","
    << "\"PREVHASH\":\"" << toBeSent.GetPreviousHash() << "\"";
  for (Transaction tx: toBeSent.GetData()){
    Serialize txSerial(tx);
    accumulator << "," << txSerial.toString();
  }
  accumulator >> output;
}

std::string toString(){
  return output;
}
