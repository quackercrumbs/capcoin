#include <iostream>
#include <string>
#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"

#include "test_transaction_utils.h"

using namespace std;

int main () {
    Transaction t = CreateFakeTransaction();
    return 0;
}