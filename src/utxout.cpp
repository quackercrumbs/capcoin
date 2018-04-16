#include "utxout.h"

UnspentTxOut::UnspentTxOut(std::string txOutId, std::string address, size_t txOutIndex, size_t amount):
                txOutId_{txOutId}, address_{address}, txOutIndex_{txOutIndex}, amount_{amount}{}

std::string UnspentTxOut::GetId(){
    return txOutId_;
}

std::string UnspentTxOut::GetAddress(){
    return address_;
}

size_t UnspentTxOut::GetIndex(){
    return txOutIndex_;
}

size_t UnspentTxOut::GetAmount(){
    return amount_;
}
