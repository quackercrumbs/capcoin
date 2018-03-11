#ifndef TEST_TRANSACTION_UTILS_H
#define TEST_TRANSACTION_UTILS_H

#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"

#include <string>
#include <vector>



//Creates a fake TxIn with random dummy data
TxIn CreateFakeTxIn();

//Create a fake TxOut with random dummy data
TxOut CreateFakeTxOut();

//Create a fake transaction with a single fake TxIn and single fake TxOut
Transaction CreateFakeTransaction();

//Create a list of transactions of random txin and txouts
std::vector<Transaction> CreateFakeTransactionList();

//Generates a random sequence of characters with the given length
std::string random_string(size_t length);

#endif
