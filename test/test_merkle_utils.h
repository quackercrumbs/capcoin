#ifndef TEST_MERKLE_UTILS_H 
#define TEST_MERKLE_UTILS_H

#include "../lib/merkle.h"
#include "../lib/transaction.h"
#include <vector>

//Creates a fake merkle tree root pointer. The tree contains fake/dummy data.
MerkleNode* CreateFakeMerkleTree(std::vector<Transaction> txs);

//Set of test comparing merkle trees
//Test Cases: same trees and different trees
bool CompareMerkleTrees();

//Create two hash trees with the same transactions
//Then compares the hashses at each tree level
//Return true if the trees match
bool test_tree_same();

//Creates two trees with different transactions
//Then compares the hashes at each tree level
//Return true if the hashes are different
bool test_tree_different_transaction();


#endif
