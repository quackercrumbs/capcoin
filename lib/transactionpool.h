#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include <queue>
#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();
	//Grabs unique transactions from other pool
	void SharePool(const std::queue<Transactions>& beta);
private:
	std::queue<Transaction> pool_;
};


#endif
