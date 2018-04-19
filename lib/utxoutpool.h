#ifndef UTXOPOOL_H
#define UTXOPOOL_H

#include <unordered_map>
#include "transaction.h"

//Container for all unspent transactions (coins)
class UnspentTxOutPool {
public:
	//All unspent TxOuts are loaded through this constructor
	UnspentTxOutPool();

private:
	std::unordered_map<std::string, Transaction> unspent_txOuts_;
};

#endif