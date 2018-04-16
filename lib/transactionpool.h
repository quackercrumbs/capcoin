#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();
	//finds transaction in pool
	bool HasTxn(Transaction& beta);
	//Grabs unique transactions from other pool
	bool AddTxn(Transaction& beta, UnspentTxOutPool& source);
private:
	std::vector<Transaction> pool_;
};


#endif
