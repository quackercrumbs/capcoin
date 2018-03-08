#ifndef MERKLE_H
#define MERKLE_H

#include "transaction.h"
#include <memory>

class MerkleNode {
public:
    MerkleNode(Transaction &value);
    MerkleNode(MerkleNode *left, MerkleNode *right);
    MerkleNode(std::vector<Transaction>& nodes);
    bool validate() const;
    const size_t hash() const;
    const MerkleNode* left() const;
    const MerkleNode* right() const;
private:
    MerkleNode(std::vector<Transaction>& nodes, size_t start, size_t end);
    std::unique_ptr<MerkleNode> left_, right_;
    size_t hash_;
    std::shared_ptr<Transaction> value_;
    size_t computeHash() const;
};

#endif
