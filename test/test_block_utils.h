#ifndef TEST_BLOCK_UTILS_H
#define TEST_BLOCK_UTILS_H

#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"
#include "../lib/block.h"

//Creates a fake Block. The Block will contain fake/dummy data for transactions
Block CreateFakeBlock();

#endif