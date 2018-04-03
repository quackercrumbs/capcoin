#include "transaction_test.h"

#include <iostream>
#include <string>
#include "transaction.h"
#include "txin.h"
#include "txout.h"

#include "test_transaction_utils.h"

using namespace std;

int main () {
    Transaction t = CreateFakeTransaction(5,3);
    return 0;
}
