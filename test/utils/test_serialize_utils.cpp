#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "utxout.h"
#include "serialize.h"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "comparator.h"
#include "test_serialize_utils.h"
#include "test_transaction_utils.h"

/*
bool test_good_unspent_serial() {
    
    srand(time(NULL));
    UnspentTxOut og("z","y",2,50);
    
    //Serialize string data
    Serialize s(og);
    std::string serial_data = s.toString();

    //Unserialize the data
    UnspentTxOut new_og  = JSONtoUTxO(serial_data);
    
    //Compare original to new_original
    bool pass = compareUTxOut(og,new_og);
    return pass;
}

bool test_bad_unspent_serial() {
    Serialize s;

    srand(time(NULL));
    UnspentTxOut og("z","y",2,50);
    UnspentTxOut fake("z","y",3,50);
    bool pass = compareUTxOut(og,fake);
    return pass;
}
*/
bool test_good_transaction_serial() {
    
    srand(time(NULL));
    TxIn in1("a", "asdasdasd", 1);
    TxOut out1("b", 50);

    TxIn in2("c", "asdfasdfasdf", 2);
    TxOut out2("d", 100);

    TxIn in3("e", "asdfadf", 3);
    TxOut out3("f", 150);

    std::vector<TxIn> ins{in1, in2, in3};
    std::vector<TxOut> outs{out1, out2, out3};
    Transaction og(ins, outs);

    Serialize s(og);
    std::string serial_data = s.toString();
    /*
    Transaction new_og = JSONtoTx(serial_data);

    bool pass = compareTransaction(og,new_og);
    return pass;
    */
    return false;
}

bool test_bad_transaction_serial() {
    srand(time(NULL));
    Transaction t1 = CreateFakeTransaction(2,4);
    Transaction t2 = CreateFakeTransaction(1,2);
    bool all_pass = compareTransaction(t1,t2);
    return all_pass;
}


bool test_good_block_serial() {
    //Block Genesis(0, 1521001712, 0, 0, "", GenTxns);
    srand(time(NULL));
    std::vector<Transaction> tlist = CreateFakeTransactionList(5);
    Block og(0, 1521001712, 0, 0, "", tlist);
    Serialize s(og);
    std::string serial_data = s.toString();
    /*
    Block new_og = JSONtoBlock(serial_data);
    bool pass = compareBlock(og,new_og); 
    return pass;
    */
    return false;
}

bool test_bad_block_serial() {

    srand(time(NULL));
    std::vector<Transaction> tlist1 = CreateFakeTransactionList(5);
    Block block1(0, 1521001712, 0, 0, "", tlist1);
    std::vector<Transaction> tlist2 = CreateFakeTransactionList(5);
    Block block2(0, 1521001712, 0, 0, "", tlist2);
    bool pass = compareBlock(block1,block2);

    return pass;
}

/*
bool test_good_txin_serial() {
    Serialize s;

    TxIn og("a","adfsdfsd",2);
    s(og);
    std::string serial_data = s.toString();
    TxIn new_og = JSONtoTxIn(serial_data);
    bool pass = compareTxIn(og,new_og);
    return pass;
}

bool test_bad_txin_serial() {
    Serialize s;

    TxIn t1("a", "adfsdafdsaf", 3);
    TxIn t2("b", "fdsfsa", 5);
    bool pass = compareTxIn(t1,t2);
    return pass;
}

bool test_good_txout_serial() {
    Serialize s;

    TxOut og("g",123);
    s(og);
    std::string serial_data = s.toString();
    TxOut new_og = JSONtoTxOut(serial_data);
    bool pass = compareTxOut(og,new_og);
    return pass;
}

bool test_bad_txout_serial() {
    Serialize s;

    TxOut t1("g", 123);
    TxOut t2("gg", 421);
    bool pass = compareTxOut(t1,t2);
    return pass;
}
*/
