template<typename T, std::string (hashFunc)(const T&)>
class MerkleNode {
public:
    //this constructor takes an object, makes an empty merkle
    //node with it as a value, and generates a hash
    //NOTE, MIGHT BE ERROR HERE. SHARED POINTER MIGHT HAVE BAD INITIALIZATION
    MerkleNode(T &value): value_{value}, left_{nullptr}, right_{nullptr}, hash_{hashFunc(value)}{}
    //this constructor takes two MerkleNodes, and creates a new parent node for them
    MerkleNode  (const MerkleNode *left, const MerkleNode *right) :
        left_{left}, right_{right}, value_{nullptr} {}

    //Constructor recursively builds the Tree from a vector.

    MerkleNode (vector<MerkleNode>& nodes, size_t start, size_t end){
        if (end - start == 0)
            return new MerkleNode(nodes[start], nullptr);
        if (end - start == 1)
            return new MerkleNode(nodes[start], nodes[end]);
        size_t mid = ((end - start) / 2) + start;
        return new MerkleNode(MerkleNode(nodes, start, mid), build_(nodes, mid+1, end));
    }

    virtual bool validate() const;
    const std::string hash() const { return hash_; }
    const MerkleNode* left() const { return left_.get(); }
    const MerkleNode* right() const { return right_.get(); }
private:
    std::unique_ptr<const MerkleNode> left_, right_;
    const std::string hash_;
    const std::shared_ptr<T> value_;
    virtual const std::string computeHash() const;
};
