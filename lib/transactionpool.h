#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include <set>
#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();
	//Shares a current pool with another pool
	void SharePool(std::set<Transactions>& beta) const;
private:
	std::set<Transaction> pool_;
};


#endif
