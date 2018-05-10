#include "transactionpool.h"

TransactionPool::TransactionPool() {}

bool TransactionPool::push(Transaction& newTx) {
    // Perform validation, to check if the newTx properties matches criteria
    // Check for double spending (double spend an input of transactiuon already in the pool
    // Check if transaction inputs and outputs matches

    //If all requirements pass, add transaction into pool
    pool_.push(newTx);
    return true;
}

size_t TransactionPool::size() const{
    return pool_.size();
}

Transaction TransactionPool::front() const{
	return pool_.front();
}

bool TransactionPool::pop(){
	if (!pool_.empty()){
		pool_.pop();
		return true;
	}
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const TransactionPool& txpool) {
    std::queue<Transaction> tmp_pool {txpool.pool_};

    while(!tmp_pool.empty()) {
        os << tmp_pool.front()<< std::endl;
        tmp_pool.pop();
    }

    return os;
}
