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
    if (end - start == 1){
        left_   = new MerkleNode(nodes[start]);
        right_  = new MerkleNode(nodes[end]);
    }
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


template<typename T, std::string (hashFunc)(const T&)>
bool MerkleNode<T, hashFunc>::validate() const{
    //if left is not null and left is not validated
    if (left_ && !left_->validate()) {
      return false;
    }
    //if right is not null and right is not validated
    if (right_ && !right_->validate()) {
      return false;
    }
    //NOTE ERROR MIGHT BE HERE, HASHFUNC MAY BE USING VALUE WRONG
    //OR PERHAPS THE UNIQUE POINTER SHOULD NOT BE OF CHAR TYPE
    //HASH_ IS OF STRING TYPE RATHER THAN CHAR* TYPE
    //ITS 5 AM IM GOING TO SLEEP
    std::unique_ptr<const char> computedHash(left_ || right_ ? computeHash() : hashFunc(*value_));
    return hash_ == computedHash.get() ? true : false;
}

