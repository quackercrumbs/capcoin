#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <sstream>

class TxIn{
public:
    TxIn    (std::string id, std::string sig, size_t index):
            id_{id}, sig_{sig}, index_{index}{}

    std::string GetVal(){
        std::stringstream ss;
        ss << id_ << index_;
        return ss.str();
    }
private:
    const std::string id_;
    const std::string sig_;
    const size_t index_;
};

class TxOut{
public:
    TxOut   (std::string address, double amount):
            address_{address}, amount_{amount}{}

    std::string GetVal(){
        std::stringstream ss;
        ss << address_ << amount_;
        return ss.str();
    }
private:
    const std::string address_;
    const double amount_;
};

//std::string TxIn:: GetVal(){
//    std::stringstream ss;
//    ss << id_ << index_;
//    return ss.str();
//}



class Transaction{
public:
    Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs):
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

private:
    std::string id_;
    //TxIn* txIns_;
    const std::vector<TxIn> txIns_;
    //TxOut* txOuts_;
    const std::vector<TxOut> txOuts_;
};

#endif
