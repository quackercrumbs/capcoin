#include <iostream>
#include <string>
#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "utxout.h"
#include "serialize.h"
#include <iostream>

#include "comparator.h"

/*
bool test_good_unspent_serial();

bool test_bad_unspent_serial();
*/
bool test_good_transaction_serial();

bool test_bad_transaction_serial();

/*
bool test_good_txin_serial();

bool test_bad_txin_serial();

bool test_good_txout_serial();

bool test_bad_txout_serial();
*/

bool test_good_block_serial();

bool test_bad_block_serial();
