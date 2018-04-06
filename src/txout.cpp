#include "txout.h"

TxOut::TxOut   (std::string address, double amount):
                address_{address}, amount_{amount}{}

std::string TxOut:: GetVal(){
    std::stringstream ss;
    ss << address_ << amount_;
    return ss.str();
}

std::string TxOut:: GetAddress(){
    return address_;
}

double TxOut:: GetAmount(){
    return amount_;
}
