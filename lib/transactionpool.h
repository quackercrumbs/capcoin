#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();
	//Grabs unique transactions from other pool
	bool AddTxn(Transaction& beta);
private:
	std::vector<Transaction> pool_;
};


#endif
