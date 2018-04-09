#include <iostream>
#include <string>
#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "utxout.h"
#include "serialize.h"
#include <iostream>

#include "compare_utils.h"
#include "test_transaction_utils.h"

bool test_good_unspent_serial() {
    Serialize s;
    
    UnspentTxOut og("z","y",2,50);
    
    //Serialize string data
    s(og);
    std::string serial_data = s.toString();

    //Unserialize the data
    UnspentTxOut new_og  = JSONtoUTxO(serial_data);
    
    //Compare original to new_original
    bool pass = compareUTxOut(og,new_og);
    return pass;
}

bool test_bad_unspent_serial() {
    Serialize s;

    UnspentTxOut og("z","y",2,50);
    UnspentTxOut fake("z","y",3,50);
    bool pass = compareUTxOut(og,fake);
    return pass;
}

bool test_good_transaction_serial() {
    Serialize s;

    TxIn in1("a", "asdasdasd", 1);
    TxOut out1("b", 50);

    TxIn in2("c", "asdfasdfasdf", 2);
    TxOut out2("d", 100);

    TxIn in3("e", "asdfadf", 3);
    TxOut out3("f", 150);

    std::vector<TxIn> ins{in1, in2, in3};
    std::vector<TxOut> outs{out1, out2, out3};
    Transaction og(ins, outs);

    s(og);
    std::string serial_data = s.toString();
    Transaction new_og = JSONtoTx(serial_data);

    bool pass = compareTransaction(og,new_og);
    return pass;
}

bool test_bad_transaction_serial() {
    Transaction t1 = CreateFakeTransaction(2,4);
    Transaction t2 = CreateFakeTransaction(1,2);
    bool all_pass = compareTransaction(t1,t2);
    return all_pass;
}
