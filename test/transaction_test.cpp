#include <iostream>
#include <string>
#include "../lib/transaction.h"

using namespace std;

int main () {
    string id = "12345";
    string sig = "5677";
    size_t index = 2;
    TxIn testTransactionIn{id,sig,index};
    cout << testTransactionIn.GetVal() << endl;
    return 0;
}
