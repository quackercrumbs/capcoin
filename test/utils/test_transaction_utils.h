#ifndef TEST_TRANSACTION_UTILS_H
#define TEST_TRANSACTION_UTILS_H

#include "transaction.h"
#include "txin.h"
#include "txout.h"

#include <string>
#include <vector>



//Creates a fake TxIn with random dummy data
TxIn CreateFakeTxIn();

//Create a fake TxOut with random dummy data
TxOut CreateFakeTxOut();

//Create a fake transaction with a single fake random TxIn and single fake random TxOut
//@param in: the number of fake txins
//@param out: the number of fake txouts
Transaction CreateFakeTransaction(size_t in, size_t out);

//Create a list of transactions of random txin and txouts
//@param size: the number of fake transactions
std::vector<Transaction> CreateFakeTransactionList(size_t size);

//Generates a random sequence of characters with the given length
//@param length: the length of the random string
std::string random_string(size_t length);

#endif
