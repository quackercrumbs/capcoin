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

#include "test_block_utils.h"

using namespace std;

int main() {
	cout << "************Block Class Test************" << endl;
	
	Block b = CreateFakeBlock();

}