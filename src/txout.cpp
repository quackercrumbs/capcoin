#include "../lib/txout.h"

TxOut::TxOut   (std::string address, double amount):
                address_{address}, amount_{amount}{}

std::string TxOut:: GetVal(){
    std::stringstream ss;
    ss << address_ << amount_;
    return ss.str();
}