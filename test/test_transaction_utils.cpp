#include "test_transaction_utils.h"

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

Transaction CreateFakeTransaction() {
	//Create fake txIns
	vector<TxIn> txIns;
	txIn.push_back(CreateFakeTxIn());
	//Create fake txOuts
	vector<TxOut> txOuts;
	txOuts.push_back(CreateFakeTxOut());
	//Create fake transaction with fake ins and outs
	Transaction fakeTransaction{txIns,txOuts};
	return fakeTransaction;
}