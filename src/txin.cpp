#include "txin.h"

TxIn::TxIn (std::string id, std::string sig, size_t index):
            id_{id}, sig_{sig}, index_{index}{}

std::string TxIn::toString(){
    std::stringstream ss;
    ss << id_ << index_;
    return ss.str();
}

std::string TxIn:: GetId()const{
    return id_;
}
std::string TxIn:: GetSignature()const{
    return sig_;
}
size_t TxIn:: GetIndex()const{
    return index_;
}
