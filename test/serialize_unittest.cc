#include "gtest/gtest.h"
#include "serialize.h"
#include <iostream>
#include "test_serialize_utils.h"

namespace {

TEST(SerialTest,UnspentTxOut) {
    EXPECT_TRUE(test_good_unspent_serial());
    EXPECT_FALSE(test_bad_unspent_serial());
}

TEST(SerialTest,Transaction) {
    EXPECT_TRUE(test_good_transaction_serial());
    EXPECT_FALSE(test_bad_transaction_serial());
}

/*
These will fail because the JSONtoTxIn was designed to only parse TxIn from Transactions
TEST(SerialTest,TxIn) {
    EXPECT_TRUE(test_good_txin_serial());
    EXPECT_FALSE(test_bad_txin_serial());   
}

TEST(SerialTest,TxOut) {
    EXPECT_TRUE(test_good_txout_serial());
    EXPECT_FALSE(test_bad_txout_serial());
}
*/

TEST(SerialTest,Block) {
    EXPECT_TRUE(test_good_block_serial());
    EXPECT_FALSE(test_bad_block_serial());
}

}

