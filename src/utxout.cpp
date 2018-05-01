#include "utxout.h"

UnspentTxOut::UnspentTxOut(std::string txOutId, std::string address, size_t txOutIndex, double amount):
                txOutId_{txOutId}, address_{address}, txOutIndex_{txOutIndex}, amount_{amount}{}

std::string UnspentTxOut::GetId() const {
    return txOutId_;
}

std::string UnspentTxOut::GetAddress() const {
    return address_;
}

size_t UnspentTxOut::GetIndex() const {
    return txOutIndex_;
}

double UnspentTxOut::GetAmount() const {
    return amount_;
}

std::ostream& operator<<(std::ostream& os, const UnspentTxOut& u) {
    os << "--------- Unspent Txn -----------" << std::endl;
    os << "TxOut Id: " << u.txOutId_ << std::endl;
    os << "Address: " << u.address_ << std::endl;
    os << "TxOut Index: " << u.txOutIndex_ << std::endl;
    os << "Amount: " << u.amount_ << std::endl;
    os << "---------------------------------" << std::endl;
    return os;
}
