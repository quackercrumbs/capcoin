#include "txin.h"

TxIn::TxIn (std::string id, std::string sig, size_t index):
            id_{id}, sig_{sig}, index_{index}{}

std::string TxIn:: GetVal(){
    std::stringstream ss;
    ss << id_ << index_;
    return ss.str();
}
