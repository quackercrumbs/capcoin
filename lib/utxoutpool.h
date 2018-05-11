#ifndef UTXOPOOL_H
#define UTXOPOOL_H

#include "utxout.h"
#include "transaction.h"
#include <map>
#include <vector>

//Container for all unspent transactions (coins)
class UnspentTxOutPool{
public:
	//All unspent TxOuts are loaded through this constructor
	UnspentTxOutPool();
	bool insert(UnspentTxOut& input);
	bool AddTxn(const Transaction& txn);
	void RemoveFromIn(const TxIn& in, std::string& address);
	UnspentTxOut* FindFromIn(const TxIn& input) const;
	std::string GetHash(const TxIn& input) const;
	double balance(const std::string& publicKey) const;
	std::vector<UnspentTxOut>* operator[] (std::string&);

	friend std::ostream& operator<<(std::ostream& os, const UnspentTxOutPool& pool);
private:
	std::map<std::string, std::vector<UnspentTxOut>> uTxOuts_;
	size_t index_;
};

#endif
