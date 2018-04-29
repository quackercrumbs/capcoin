#ifndef TXOUT_H
#define TXOUT_H

#include <string>
#include <sstream>

class TxOut{
public:
    TxOut(std::string address, double amount);

    std::string GetAddress();
    double GetAmount();
    
private:
    const std::string address_;
    const double amount_;
};

#endif
