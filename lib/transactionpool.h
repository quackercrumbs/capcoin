#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include <queue>
#include <iostream>

#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();
	bool push(Transaction& newTx);
	size_t size() const;
	Transaction front() const;
	bool pop();
	friend std::ostream& operator<<(std::ostream& os, const TransactionPool& txpool);

private:
	std::queue<Transaction> pool_;
};


#endif
