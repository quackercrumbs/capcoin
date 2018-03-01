#include <iostream>
#include <string>
#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"

using namespace std;

TxIn CreateFakeTxIn();
TxOut CreateFakeTxOut();

int main () {
    TxIn txIn = CreateFakeTxIn();
    cout << txIn.GetVal() << endl;
    TxOut txOut = CreateFakeTxOut();
    cout << txOut.GetVal() << endl;
    return 0;
}

TxIn CreateFakeTxIn() {
	string id = "12345";
    string sig = "5677";
    size_t index = 2;
    TxIn fakeTxIn{id,sig,index};
    return fakeTxIn;
}

TxOut CreateFakeTxOut() {
	string addr = "";
	double amt = 20;
	TxOut fakeTxOut{addr,amt};
	return fakeTxOut;
}
