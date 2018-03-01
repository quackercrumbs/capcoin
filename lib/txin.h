#ifndef TXIN_H
#define TXIN_H

class TxIn{
public:
    TxIn(std::string id, std::string sig, size_t index);
    std::string GetVal();
private:
    const std::string id_;
    const std::string sig_;
    const size_t index_;
};

#endif