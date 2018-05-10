#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include <queue>
#include <iostream>

#include "transaction.h"

class TransactionPool {
public:
	//Initialize the transaction pool (loads data from pool)
	TransactionPool();

    //Pushes the newTx into the memory pool
    bool AddTransaction(const Transaction& newTx);
		size_t size() const;

    friend std::ostream& operator<<(std::ostream& os, const TransactionPool& txpool);

private:

	std::queue<Transaction> pool_;
};


#endif
