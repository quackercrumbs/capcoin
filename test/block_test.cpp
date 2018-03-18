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
#include "../lib/blockchain.h"
#include <time.h>
#include <vector>

#include "test_block_utils.h"
#include "test_transaction_utils.h"

using namespace std;

int main() {
	cout << "************Block Class Test************" << endl;
	
    Blockchain bc;
    Block genBlock = bc.GetLastBlock();
    cout << "Hash Match Difficulty: " << bc.HashMatchesDifficulty("0012323123",2) << endl;

    vector<Transaction> t_list = CreateFakeTransactionList(6);
    Block newBlock = bc.GenerateNextBlock(t_list);     
    cout << "Gen Block Hash: " << genBlock.GetHash()  << endl;    
    cout << "New Block Previous Hash: " << newBlock.GetPreviousHash()  << endl;    
}
