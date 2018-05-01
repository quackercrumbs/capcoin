#ifndef UTXOPOOL_H
#define UTXOPOOL_H

#include "utxout.h"
#include "txin.h"
#include <map>

//Container for all unspent transactions (coins)
class UnspentTxOutPool{
public:
	//All unspent TxOuts are loaded through this constructor
	UnspentTxOutPool();
	bool AddTxn(UnspentTxOut& input);
	UnspentTxOut* FindFromIn(const TxIn& input) const;
	double search(const std::string& publicKey) const;

	friend std::ostream& operator<<(std::ostream& os, const UnspentTxOutPool& pool);
private:
	std::map<std::string, UnspentTxOut> uTxOuts_;
};

#endif
