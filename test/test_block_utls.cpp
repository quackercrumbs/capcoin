#include "../lib/transaction.h"
#include <time.h>
#include <string>

#include "test_block_utils.h"
#include "test_transaction_utils.h"

Block CreateFakeBlock() {
	Transaction t = CreateFakeTransaction();
	vector<Transaction> transaction_list {t};
	size_t block_index = 0;
	time_t timestamp;
	time(&timestamp);
	size_t difficulty = 2;
	size_t nonce = 2;
	string hash = "12345";
	string prevHash = "4567";

	Block fake_block {block_index, timestamp, difficulty, nonce, hash, prevHash, transaction_list};

}