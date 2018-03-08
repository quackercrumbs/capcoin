#include "../lib/merkle.h"

size_t combine(size_t a, size_t b) {
   size_t times = 1;
   while (times <= b)
      times *= 10;
   return a*times + b;
}

MerkleNode::MerkleNode(Transaction &value): value_{std::move(std::make_shared<Transaction>(value))},
            left_{nullptr}, right_{nullptr}, hash_{value.hash()}{}

MerkleNode::MerkleNode(MerkleNode *left, MerkleNode *right):
    left_{left}, right_{right}, value_{nullptr}{}

MerkleNode::MerkleNode(std::vector<Transaction>& nodes){
    *this = MerkleNode(nodes, 0, nodes.size()-1);
}



MerkleNode::MerkleNode(std::vector<Transaction>& nodes, size_t start, size_t end){
    std::hash<size_t> hashify;
    if (end == start){
        left_ = std::move(std::unique_ptr<MerkleNode>(new MerkleNode(nodes[start])));
        right_ = std::move(std::unique_ptr<MerkleNode>(nullptr));
        hash_ = hashify(combine(nodes[start].hash(), nodes[start].hash()));
    }
    else if (end - start == 1){
        left_ = std::move(std::unique_ptr<MerkleNode>(new MerkleNode(nodes[start])));
        right_ = std::move(std::unique_ptr<MerkleNode>(new MerkleNode(nodes[end])));
        hash_ = hashify(combine(nodes[start].hash(), nodes[end].hash()));
    }
    else{
        size_t mid = ((end - start) / 2) + start;
        left_ = std::move(std::unique_ptr<MerkleNode>(new MerkleNode(nodes, start, mid)));
        right_ = std::move(std::unique_ptr<MerkleNode>(new MerkleNode(nodes, start+1, mid)));
        hash_ = hashify(combine(left_->hash(), right_->hash()));
    }
}

const size_t MerkleNode::hash()const{
    return hash_;
}

const MerkleNode* MerkleNode::left()const{
    return left_ ? left_.get() : nullptr;
}

const MerkleNode* MerkleNode::right()const{
    return right_ ? right_.get() : nullptr;
}
size_t MerkleNode::computeHash()const{
    std::hash<size_t>hashify;
    return left_ && right_ ?hashify(combine(left_->hash_, right_->hash_)):
                            hashify(combine(left_->hash_, left_->hash_));
}

bool MerkleNode::validate() const{
    if (left_ && !left_->validate()) {
      return false;
    }
    if (right_ && !right_->validate()) {
      return false;
    }
    size_t computedHash = (left_ || right_ ? computeHash() : (*value_).hash());
    return hash_ == computedHash ? true : false;
}
