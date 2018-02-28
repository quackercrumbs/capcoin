#include "../lib/merkle.h"

template<typename T, std::string (hashFunc)(const T&)>
MerkleNode<T, hashFunc>::MerkleNode(T &value): value_{value}, left_{nullptr},
    right_{nullptr}, hash_{hashFunc(value)}{}

template<typename T, std::string (hashFunc)(const T&)>
MerkleNode<T, hashFunc>::MerkleNode(const MerkleNode *left, const MerkleNode *right):
    left_{left}, right_{right}, value_{nullptr}{}

template<typename T, std::string (hashFunc)(const T&)>
MerkleNode<T, hashFunc>::MerkleNode(std::vector<T>& nodes, size_t start, size_t end){
    if (end - start == 0){
        left_   = new MerkleNode(nodes[start]);
        right_  = nullptr;
    }
    //return new MerkleNode(new MerkleNode<T>(nodes[start]), nullptr);
    if (end - start == 1){
        left_   = new MerkleNode(nodes[start]);
        right_  = new MerkleNode(nodes[end]);
    }
    //return new MerkleNode(new MerkleNode<T>(nodes[start]), new MerkleNode<T>(nodes[end]));
    size_t mid = ((end - start) / 2) + start;
    left_   = new MerkleNode(nodes, start, mid);
    right_  = new MerkleNode(nodes, mid+1, end);
}

template<typename T, std::string (hashFunc)(const T&)>
const std::string MerkleNode<T, hashFunc>::hash()const{
    return hash_;
}

template<typename T, std::string (hashFunc)(const T&)>
const MerkleNode<T, hashFunc>* MerkleNode<T, hashFunc>::left()const{
    return left_.get();
}

template<typename T, std::string (hashFunc)(const T&)>
const MerkleNode<T, hashFunc>* MerkleNode<T, hashFunc>::right()const{
    return right_.get();
}
