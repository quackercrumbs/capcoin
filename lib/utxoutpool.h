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
	void RemoveTxIns(const std::vector<TxIn>& txIns, const std::string& address);
	void AddTxOuts(const std::vector<TxOut>& txOuts, const std::string& hash);
	UnspentTxOut* FindFromIn(const TxIn& input) const;
	std::string GetHash(const TxIn& input) const;
	size_t GetIndex() const;
	size_t size() const;
	double balance(const std::string& publicKey) const;
	std::vector<UnspentTxOut>* operator[] (std::string&);

	friend std::ostream& operator<<(std::ostream& os, const UnspentTxOutPool& pool);
private:
	std::map<std::string, std::vector<UnspentTxOut>> uTxOuts_;
	size_t index_;
};

#endif
