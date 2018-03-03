#ifndef TEST_BLOCK_UTILS_H
#define TEST_BLOCK_UTILS_H

#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"
#include "../lib/block.h"

#include <time.h>
#include <string>
#include <vector>

//Creates a fake Block. The Block will contain fake/dummy data for transactions
Block CreateFakeBlock();

#endif
