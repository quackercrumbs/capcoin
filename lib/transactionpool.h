#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();
	//Grabs unique transactions from other pool
	void SharePool(const std::vector<Transactions>& beta);
private:
	std::vector<Transaction> pool_;
};


#endif
