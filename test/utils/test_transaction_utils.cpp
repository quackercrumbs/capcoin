#include "test_transaction_utils.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>

using namespace std;

TxIn CreateFakeTxIn() {
	string id = random_string(8);
    string sig = random_string(8);
    size_t index = rand() % 1000;
    TxIn fakeTxIn{id,sig,index};
    return fakeTxIn;
}

TxOut CreateFakeTxOut() {
    string addr = random_string(8);
	double amt = rand() % 1000;
	TxOut fakeTxOut{addr,amt};
	return fakeTxOut;
}

Transaction CreateFakeTransaction(size_t in, size_t out) {
    //Create fake txIns
    vector<TxIn> txIns;
    for(size_t i = 0; i < in; i++) {
	    txIns.push_back(CreateFakeTxIn());
    }
    //Create fake txOuts
	vector<TxOut> txOuts;
    for (size_t i = 0; i < out; i++) {
        txOuts.push_back(CreateFakeTxOut());
    }
    //Create fake transaction with fake ins and outs
	Transaction fakeTransaction{txIns,txOuts};
	return fakeTransaction;
}

vector<Transaction> CreateFakeTransactionList(size_t size) {
    vector<Transaction> t_list;
    for(int i = 0; i < size; i++) {
        t_list.push_back(CreateFakeTransaction(5,3));
    }
    return t_list;
}


std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
