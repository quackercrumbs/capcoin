//NOTE, WE NEED TO ADD DEPENDANCIES. I AM LAZY.

template<typename T, std::string (hashFunc)(const T&)>
class MerkleNode {
public:
    //this constructor takes an object, makes an empty merkle
    //node with it as a value, and generates a hash
    //NOTE, MIGHT BE ERROR HERE. SHARED POINTER MIGHT HAVE BAD INITIALIZATION
    MerkleNode(T &value);
    //this constructor takes two MerkleNodes, and creates a new parent node for them
    MerkleNode(const MerkleNode *left, const MerkleNode *right);
    //Constructor recursively builds the Tree from a vector.
    MerkleNode (vector<MerkleNode>& nodes, size_t start, size_t end);

    virtual bool validate() const;
    const std::string hash() const;
    const MerkleNode* left() const;
    const MerkleNode* right() const;
private:
    std::unique_ptr<const MerkleNode> left_, right_;
    const std::string hash_;
    const std::shared_ptr<T> value_;
    virtual const std::string computeHash() const;
};
