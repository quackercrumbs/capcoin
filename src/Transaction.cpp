#include "Transaction.h"

TxIn::txIns (std::string id, std::string sig, size_t index):
        id_{id}, sig_{sig}, index_{index}{}

std::string TxIn:: GetVal(){
    std::stringstream ss;
    ss << id_ << index_;
    return ss.str();
}

TxOut::txOuts   (std::string address, double amount):
                address_{address}, amount_{amount}{}

std::string TxOut:: GetVal(){
    std::stringstream ss;
    ss << address_ << amount_;
    return ss.str();
}

Transaction::Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs):
                        txIns_{std::move(ins)}, txOuts_{std::move(outs)}{
    std::string accuInTx = "", accuOutTx = "";
    //for each transaction in txIns_, append its id and index to accuInTx
    for (auto i : txIns_)
        accuInTx = accuInTx + i.GetVal();
    //for each transaction in txOuts_, append its address and amount to accuOutTx
    for (auto i : txOuts_)
        accuOutTx = accuOutTx + i.GetVal();
    std::hash<std::string> hashifier;
    //add the two strings and hash them for the id
    id_ = hashifier(accuInTx + accuOutTx);
}
