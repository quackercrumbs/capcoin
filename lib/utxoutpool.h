#ifndef UTXOPOOL_H
#define UTXOPOOL_H

#include "utxout.h"
#include "txin.h"
#include <vector>
//Container for all unspent transactions (coins)
class UnspentTxOutPool{
public:
	//All unspent TxOuts are loaded through this constructor
	UnspentTxOutPool();
	bool AddTxn(UnspentTxOut& input);
	UnspentTxOut* FindFromIn(const TxIn& input);
private:
	std::vector<UnspentTxOut> uTxOuts_;
};

#endif
