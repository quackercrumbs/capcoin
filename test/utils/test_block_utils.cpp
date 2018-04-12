#include "transaction.h"

#include "test_block_utils.h"
#include "test_transaction_utils.h"

using namespace std;

Block CreateFakeBlock() {
	vector<Transaction> transaction_list = CreateFakeTransactionList(6);
	size_t block_index = 0;
	time_t timestamp;
	time(&timestamp);
	size_t difficulty = 2;
	size_t nonce = 2;
	string hash = "12345";
	string prevHash = "4567";

	Block fake_block {block_index, timestamp, difficulty, nonce, hash, prevHash, transaction_list};
	return fake_block;
}
