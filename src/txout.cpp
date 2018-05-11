#include "txout.h"

TxOut::TxOut   (std::string address, double amount):
                address_{address}, amount_{amount}{}

std::string TxOut:: toString() const{
    std::stringstream ss;
    ss << address_ << amount_;
    return ss.str();
}

std::string TxOut:: GetAddress() const{
    return address_;
}

double TxOut:: GetAmount() const{
    return amount_;
}

std::ostream& operator<<(std::ostream& os, const TxOut& txout) {
    os << "=== TxOut ===" << std::endl;
    os << "ADDRESS: " << txout.address_ << std::endl;
    os << "AMT: " << txout.amount_ << std::endl;
    return os;
}
