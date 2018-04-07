#include "serialize.h"
#include <iostream>

void Serialize::operator()(Transaction& toBeSent){
  std::stringstream accumulator;
  Serialize smallSerial;
  accumulator << "\"TRANSACTION\":{\"ID\":\"" << toBeSent.hash() << "\"";
  for(TxIn in: toBeSent.GetTxIns()){
    smallSerial(in);
    accumulator << smallSerial.toString();
  }
  for(TxOut out: toBeSent.GetTxOuts()){
    smallSerial(out);
    accumulator << smallSerial.toString();
  }
  accumulator << "}";
  accumulator >> output;
}

void Serialize::operator()(Block& toBeSent){
  std::stringstream accumulator;
  Serialize smallSerial;
  accumulator << "\"BLOCK\":{\"INDEX\":\"" << toBeSent.GetIndex() << "\","
    << "\"TIMESTAMP\":\"" << toBeSent.GetTimestamp() << "\","
    << "\"DIFFICULTY\":\"" << toBeSent.GetDifficulty() << "\","
    << "\"NONCE\":\"" << toBeSent.GetNonce() << "\","
    << "\"HASH\":\"" << toBeSent.GetHash() << "\","
    << "\"PREVHASH\":\"" << toBeSent.GetPreviousHash() << "\"";
  for (Transaction tx: toBeSent.GetData()){
    smallSerial(tx);
    accumulator << "," << smallSerial.toString();
  }
  accumulator << "}";
  accumulator >> output;
}
void Serialize::operator()(TxIn& toBeSent){
  std::stringstream accumulator;
  accumulator << ",\"IN\":{\"ID\":\"" << toBeSent.GetId() << "\","
    << "\"SIG\":\"" << toBeSent.GetSignature() << "\","
    << "\"INDEX\":\"" << toBeSent.GetIndex() << "\"}";
  accumulator >> output;
}
void Serialize::operator()(TxOut& toBeSent){
  std::stringstream accumulator;
  accumulator << ",\"OUT\":{\"AMOUNT\":\"" << toBeSent.GetAmount() << "\","
    << "\"ADDRESS\":\"" << toBeSent.GetAddress() << "\"}";
  accumulator >> output;
}

std::string Serialize::toString(){
  return output;
}

Block JSONtoBlock(std::string blockString){
    size_t index, difficulty, nonce, start = 19, end = 19;
    time_t timestamp;
    std::string prevHash, hash;
    std::vector<Transaction> data;
    while (blockString[end] != '\"'){end++;}
    index = strtol(blockString.substr(start, end-start).c_str(), NULL, 10);
    start = end + 15;
    end = start;
    while (blockString[end] != '\"'){end++;}
    timestamp = strtol((blockString.substr(start, end-start).c_str()), NULL, 10);
    start = end + 16;
    end = start;
    while (blockString[end] != '\"'){end++;}
    difficulty = strtol((blockString.substr(start, end-start).c_str()), NULL, 10);
    start = end + 11;
    end = start;
    while (blockString[end] != '\"'){end++;}
    nonce = strtol((blockString.substr(start, end-start).c_str()), NULL, 10);
    start = end + 10;
    end = start;
    while (blockString[end] != '\"'){end++;}
    hash = blockString.substr(start, end-start);
    start = end + 14;
    end = start;
    while (blockString[end] != '\"'){end++;}
    prevHash = blockString.substr(start, end-start);
    start = end + 2;
    end = start + 11;
    std::string prefix = blockString.substr(start+1, end-start);
    while(prefix == "TRANSACTION"){
        end = start + 16;
        size_t brackets = 1;
        while (brackets != 0 && !(blockString.length() < end)){
            if(blockString[end] == '{')
                brackets++;
            if(blockString[end] == '}')
                brackets--;
            end++;
        }
        Transaction tx = JSONtoTx(blockString.substr(start, end));
        data.push_back(tx);
        start = end + 1;
        end = start + 11;
        if (end > blockString.length())
            break;
        prefix = blockString.substr(start+1, end-start);
    }
    Block output(index, timestamp, difficulty, nonce, hash, prevHash, data);
    return output;
}

Transaction JSONtoTx(std::string txnString){
    std::string id, prefix;
    std::vector<TxIn> ins;
    std::vector<TxOut> outs;
    size_t start = 21, end = 21;
    while (txnString[end] != '\"'){end++;}
    id = txnString.substr(start, end-start);
    start = end + 2;
    end = start + 2;
    //while (txnString[end] != '\"'){end++;}
    prefix = txnString.substr(start+1, end-start);
    while(prefix == "IN"){
        while(txnString[end] != '}'){end++;}
        TxIn in = JSONtoTxIn(txnString.substr(start, end-start));
        ins.push_back(in);
        start = end + 2;
        end = start + 2;
        if (end > txnString.length())
            break;
        prefix = txnString.substr(start+1, end-start);
    }
    prefix = txnString.substr(start+1, (++end)-start);
    while(prefix == "OUT"){
        while(txnString[end] != '}'){end++;}
        TxOut out = JSONtoTxOut(txnString.substr(start, end-start));
        outs.push_back(out);
        start = end + 2;
        end = start + 3;
        if (end > txnString.length())
            break;
        prefix = txnString.substr(start+1, end-start);
    }
    Transaction output(ins, outs);
    return output;
}

//"IN":{"ID":"a","SIG":"asdasdasd","INDEX":"1"}
TxIn JSONtoTxIn(std::string instring){
    std::string id;
    std::string sig;
    size_t index, start = 12, end = 12;
    while (instring[end] != '\"'){end++;}
    id = instring.substr(start, end-start);
    start = end + 9;
    end = start;
    while (instring[end] != '\"'){end++;}
    sig = instring.substr(start, end-start);
    start = end + 11;
    index = strtol((instring.c_str() + start), NULL, 10);
    TxIn output(id, sig, index);
    return output;
}

//"OUT":{"AMOUNT":"50","ADDRESS":"b"}
TxOut JSONtoTxOut(std::string outstring){
    std::string address;
    double amount;
    size_t start = 17, end = 17;
    while (outstring[end] != '\"'){end++;}
    amount = strtod(outstring.substr(start, end-start).c_str(), NULL);
    start = end + 13;
    end = start;
    while (outstring[end] != '\"'){end++;}
    address = outstring.substr(start, end-start);
    TxOut output(address, amount);
    return output;
}
