#ifndef TXIN_H
#define TXIN_H
#include <string>
#include <sstream>

class TxIn{
public:
    TxIn(std::string id, std::string sig, size_t index);

    std::string GetVal()const;
    std::string GetId()const;
    std::string GetSignature()const;
    size_t GetIndex()const;

private:
    const std::string id_;
    const std::string sig_;
    const size_t index_;
};

#endif
