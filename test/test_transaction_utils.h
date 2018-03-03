#ifndef TEST_TRANSACTION_UTILS_H
#define TEST_TRANSACTION_UTILS_H

#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"

#include <string>
#include <vector>



//Creates a fake TxIn with dummy data
TxIn CreateFakeTxIn();

//Create a fake TxOut with dummy data
TxOut CreateFakeTxOut();

//Create a fake transaction with a single fake TxIn and single fake TxOut
Transaction CreateFakeTransaction();

#endif
