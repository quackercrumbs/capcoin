#include "test_merkle_utils.h"
#include "test_transaction_utils.h"

#include <iostream>

using namespace std;

MerkleNode* CreateFakeMerkleTree(vector<Transaction> txs) {

    Transaction t = CreateFakeTransaction(5,3);
    MerkleNode* root = new MerkleNode(t);
    return root;
}

bool CompareMerkleTrees() {
    
    cout << "-- Test: Comparing Merkle Trees --" << endl;
    bool all_pass = true;

    //Test Case: The trees have the same transaction and same hashes
    if(!test_tree_same()) {
        all_pass = false;
        cout << "FAIL: The trees have same transaction and same hashes" << endl;
    }
    //Test Case: The trees have different transactions
    if(test_tree_different_transaction()) {
        all_pass = false;
        cout << "FAIL: The trees have different transactions" << endl;
    }

    if(all_pass) {
        cout << "All test passes!" << endl;
    }
    return all_pass;
}

bool test_tree_same() {
    bool pass = true;

    vector<Transaction> t_list1 = CreateFakeTransactionList(3);

    MerkleNode* root1 = CreateFakeMerkleTree(t_list1);
    MerkleNode* root2 = CreateFakeMerkleTree(t_list1);

    //Peform comparison

    return pass;
}


bool test_tree_different_transaction() {
    bool pass = true;

    vector<Transaction> t_list1 = CreateFakeTransactionList(3);
    vector<Transaction> t_list1 = CreateFakeTransactionList(3);

    MerkleNode* root1 = CreateFakeMerkleTree(t_list1);
    MerkleNode* root2 = CreateFakeMerkleTree(t_list1);

    //Peform comparison

    return pass;
}

