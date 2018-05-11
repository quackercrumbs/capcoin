#ifndef TXOUT_H
#define TXOUT_H

#include <string>
#include <sstream>

class TxOut{
public:
    TxOut(std::string address, double amount);

    std::string toString() const;
    std::string GetAddress() const;
    double GetAmount() const;

    friend std::ostream& operator<<(std::ostream& os, const TxOut& txout);

private:
    const std::string address_;
    const double amount_;
};

#endif
