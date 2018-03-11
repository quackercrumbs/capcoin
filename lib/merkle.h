#ifndef MERKLE_H
#define MERKLE_H

#include "transaction.h"
#include <memory>

class MerkleNode {
public:
    //Initalize the node with a ptr to the transaction 
    MerkleNode(Transaction &value);
    //Initalize the left and right node ptrs 
    MerkleNode(MerkleNode *left, MerkleNode *right);
    //Creates a node with subtrees pointing to transactions 
    MerkleNode(std::vector<Transaction>& nodes);

    //Recursively validates the integreity of the node and its subtrees.
    bool validate() const;

    //Returns the hash of the current node
    const size_t hash() const;

    //Return a ptr to the left subtree
    const MerkleNode* left() const;

    //Return a ptr to the right subtree
    const MerkleNode* right() const;
private:
    MerkleNode(std::vector<Transaction>& nodes, size_t start, size_t end);
    std::unique_ptr<MerkleNode> left_, right_;
    size_t hash_;
    std::shared_ptr<Transaction> value_;
    size_t computeHash() const;
};

#endif
