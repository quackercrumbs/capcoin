#include "merkle_test_utils.h"
#include "test_transaction_utils.h"

#include <iostream>

MerkleNode* CreateFakeMerkleTree() {

    Transaction t = CreateFakeTransaction();
    MerkleNode* root = new MerkleNode(t);
    return root;
}


