#include "../lib/transaction.h"
#include "../lib/merkle.h"

#include "merkle_test_utils.h"

#include <iostream>

using namespace std;

int main() {

    cout << "****** Merkle Class Test *******" << endl;
    MerkleNode* root = CreateFakeMerkleTree();
    cout << root->validate() << endl;

}
