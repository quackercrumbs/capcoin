/*
*	Still work in progress
*	Test all Block class functionality
*/
#include <iostream>
#include <string>
#include "block.h"
#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "blockchain.h"
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

    //DONT MATCH B/C HAVENT IMPLEMENT CALCULATE HASH() 
    cout << "Gen Block Hash: " << genBlock.GetHash()  << endl;    
    cout << "New Block Previous Hash: " << newBlock.GetPreviousHash()  << endl;    
}
