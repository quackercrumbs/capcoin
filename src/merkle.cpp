#include "../lib/merkle.h"

MerkleNode::MerkleNode(T &value): value_{value}, left_{nullptr},
    right_{nullptr}, hash_{hashFunc(value)}{}

MerkleNode::MerkleNode(const MerkleNode *left, const MerkleNode *right):
    left_{left}, right_{right}, value_{nullptr}{}

MerkleNode::MerkleNode(vector<MerkleNode>& nodes, size_t start, size_t end){
    if (end - start == 0)
        return new MerkleNode(nodes[start], nullptr);
    if (end - start == 1)
        return new MerkleNode(nodes[start], nodes[end]);
    size_t mid = ((end - start) / 2) + start;
    return new MerkleNode(MerkleNode(nodes, start, mid), build_(nodes, mid+1, end));
}

const std::string MerkleNode::hash()const{
    return hash_;
}
const MerkleNode* MerkleNode::left()const{
    return left_.get();
}
const MerkleNode* MerkleNode::right()const{
    return right_.get();
}
