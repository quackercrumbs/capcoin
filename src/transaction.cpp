#include "../lib/transaction.h"

Transaction::Transaction(std::vector<TxIn>& ins, std::vector<TxOut>& outs):
                        txIns_{std::move(ins)}, txOuts_{std::move(outs)}{
    std::string accuInTx = "", accuOutTx = "";
    //for each transaction in txIns_, append its id and index to accuInTx
    for (auto i : txIns_)
        accuInTx = accuInTx + i.GetVal();
    //for each transaction in txOuts_, append its address and amount to accuOutTx
    for (auto i : txOuts_)
        accuOutTx = accuOutTx + i.GetVal();
    //add the two strings and hash them for the id
    id_ = picosha2::hash256_hex_string(accuOutTx);
}

std::string Transaction::hash(){
    return id_;
}
