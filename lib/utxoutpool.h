#ifndef UTXOPOOL_H
#define UTXOPOOL_H

#include "transaction.h"

//Container for all unspent transactions (coins)
class UnspentTxOutPool {
public:
	//All unspent TxOuts are loaded through this constructor
	UnspentTxOutPool();
	UnspentTxOut FindFromIn(const TxIn& input);
private:
	std::vector<UnspentTxOut> txOuts_;
};

#endif
