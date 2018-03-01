/*
*	Still work in progress
*	Test all Block class functionality
*/
#include <iostream>
#include <string>
#include "../lib/block.h"
#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"
#include <time.h>
#include <vector>

using namespace std;

int main() {
	cout << "************Block Class Test************" << endl;
	//Create TxIns and TxOuts
	string id1 = "123";
	string sig1 = "4444";
	string id2 = "124";
	string sig1 = "4445";
	TxIn txin1{id1, sig1,0};
	TxIn txin2{id2, sig2,1};
	vector<TxIn> txIns {txin1,txin2};

	string addr1 = "fake address1";
	string addr2 = "fake address2";
	double amt1 = 12;
	double amt2 = 13;
	TxOut txout1{addr1,amt1};
	TxOut txout2{addr2,amt2};
	vector<TxOut> txOuts {txout1,txout2};

	//Create transaction for block
	Transaction transaction{txIns, txOuts};
	//Create transaction list for block
	vector<Transaction> transactions {transaction};

	//Create other block variables (hash,prevHash,index,etc....)
	size_t block_index = 0;
	time_t timestamp;
	time(&timestamp);
	size_t difficulty = 2;
	size_t nonce = 2;
	string hash = "12345";
	string prevHash = "4567";

	//create block
	Block block1 {block_index, timestamp, difficulty, nonce, hash, prevHash, transactions};


}