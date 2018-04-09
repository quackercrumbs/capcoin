#include <iostream>
#include <string>
#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "utxout.h"
#include "serialize.h"
#include <iostream>

#include "compare_utils.h"


bool test_good_unspent_serial();

bool test_bad_unspent_serial();

bool test_good_transaction_serial();
