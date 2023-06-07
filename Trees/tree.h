// nodes used in Tree and Binary Search Tree
struct TreeNode  {
    TreeNode *left, *right;
    int key, count;

    TreeNode() : key(0), count(0), left(nullptr), right(nullptr) {};
    TreeNode(int val) : key(val), count(1), left(nullptr), right(nullptr) {};
    virtual ~TreeNode() {  left = right = nullptr; key = count = 0; };
};

// nodes used in AVLTree
struct AVLNode : TreeNode {
    int height, balance_factor;
    
    AVLNode(int val) : height(0), balance_factor(0), TreeNode(val) {};
    ~AVLNode() { balance_factor = height = 0; };
};

#define isBlack(node) (!node || node->color == BLACK)
#define isRed(node) (node && node->color == RED)

// nodes used in RedBlackTree
enum colors { BLACK, RED }; 

struct RedBlackNode : TreeNode {
    enum colors color;
    TreeNode* parent; 
    
    
    RedBlackNode(int val) : color(RED), parent(nullptr), TreeNode(val) {};
    RedBlackNode(string NIL) : color(BLACK), parent(nullptr), TreeNode() {};
    ~RedBlackNode() { parent = nullptr; };
};

// abstraction of tree
class Tree { 

    private:
        // calculates height of tree via DFS
        int findHeight(TreeNode* root) const;

        // deletes all nodes in tree recursively
        void deleteTree(TreeNode* root);

    protected:
        TreeNode* m_root; // root of tree
        int m_size; // size of tree

    public:
        Tree() : m_size(0), m_root(nullptr) {}
        ~Tree() { deleteTree(m_root); };

        // abstraction: ability to insert or remove elements from tree
        virtual void insert (int val) = 0;
        virtual bool remove (int val) = 0;
        
        // returns number of nodes in tree
        int getSize() const { return m_size; };
        // returns number of edges from root node to furthest leaf
        virtual int getHeight() const;

        // prints tree using directory-like notation
        friend void print(const Tree*);
};

// binary search tree
class BinarySearchTree : public Tree {

    private:
        // collection of overloaded helper functions
        int findMin(TreeNode* root) const; 
        int findMax(TreeNode* root) const; 

        int findPrev(TreeNode* root, int val, int max_prev) const;
        int findNext(TreeNode* root, int val, int max_prev) const;

        void inorder(TreeNode* root, vector<int>& v) const;
        void preorder(TreeNode* root, vector<int>& v) const;
        void postorder(TreeNode* root, vector<int>& v) const;

    protected:
        // recursively performs insert/remove operations with respect to tree
        virtual TreeNode* insertNode(TreeNode* root, int val);
        virtual TreeNode* removeNode(TreeNode* root, int val);
        
        // hrecursively searches if a value is present in tree 
        TreeNode* search(TreeNode* root, int val) const;

        // finds inorder predecessor and inorder successor within same subtree
        TreeNode* findPrevChild(TreeNode* root) const;
        TreeNode* findNextChild(TreeNode* root) const;

    public:
        // inserts element with given value into tree
        virtual void insert (int val) override;
        // removes element with given value (if exists) from tree; returns if removal successful
        virtual bool remove (int val) override;

        // returns if value is present in tree
        bool search(int val) const;
        // returns count of key in tree
        int count(int val) const;

        // finds greatest element strictly less than given value or INT_MIN if none exists
        int findPrev(int val) const;
        // finds smallest element strictly greater than given value or INT_MAX if none exists
        int findNext(int val) const;

        // returns min element in tree
        int findMin() const;
        // returns max element in tree
        int findMax() const;
    
        // returns vector of elements in tree corresponding to following DFS orderings
        vector<int> preorder() const;
        vector<int> inorder() const;
        vector<int> postorder() const;
        // returns vector of elements in tree corresponding to breadth-first search ordering
        vector<int> BFSorder() const;

        // prints inorder travesal of BST when entered into console output
        friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree);
};

// AVL self-balancing binary search tree
class AVLTree : public BinarySearchTree {

    private:
        // recursively performs insert/remove operations with respect to tree
        TreeNode* insertNode(TreeNode* root, int val) override;
        TreeNode* removeNode(TreeNode* root, int val) override;

        // helper methods to perform rotations with respect to root of subtree
        TreeNode* rotateLeft(TreeNode* root);
        TreeNode* rotateRight(TreeNode* root);

        // respondible for updating balance of nodes and rebalancing tree when balance exceeds 1
        void updateBalance(TreeNode* root);
        TreeNode* rebalance(TreeNode* root);

    public:
        // inserts element with given value, then self balances AVL tree if necessary
        void insert (int val) override;
        // removes element with given value (if exists), then self balances AVL tree if necessary
        bool remove (int val) override;

        // returns difference of heights between left and right subtrees
        int getBalance() const { return static_cast<AVLNode*>(m_root)->balance_factor; };
        // returns number of edges between root and farthest leaf
        int getHeight() const override { return static_cast<AVLNode*>(m_root)->height; };
};

class RedBlackTree : public BinarySearchTree {

    private:
        // returns family info (e.g. uncle, grandfather, sibling, newphews) of a node
        tuple<RedBlackNode*, RedBlackNode*, RedBlackNode*> getUpperFamily(RedBlackNode* child) const;
        tuple<RedBlackNode*, RedBlackNode*, RedBlackNode*, RedBlackNode*> getLowerFamily(RedBlackNode* child) const;

        // checks if violation occurs during removal
        bool checkViolation(RedBlackNode* target, RedBlackNode* replacement) const;

        // fixes violations of red black tree due to insertion and removal respectively
        void fixAdjacentRedViolation(RedBlackNode* child);
        void fixBlackPathViolation(RedBlackNode* child);

        // helper methods to perform rotations with respect to root of subtree
        RedBlackNode* rotateLeft(RedBlackNode* root);
        RedBlackNode* rotateRight(RedBlackNode* root);

        // transfers old root's parent to new root's parent, connecting subtree to rest of red black tree
        void transferRoot(RedBlackNode* root, RedBlackNode* child);

        // deletes node, removing its parent connection
        void deleteNode(RedBlackNode* root);

        // tests if the tree meets red black tree requirements for debugging purposes
        bool validRedBlackTree() const;
        bool noAdjacentReds(RedBlackNode* root) const;
        bool blackHeightConsistency(RedBlackNode* root, int blackHeight, int target) const;

        // overloaded public method for recursive height calculation
        int getBlackHeight(RedBlackNode* root) const;

    public:
        // inserts element with given value, then rebalances Red Black tree to fix color violations
        void insert (int val) override;
        // removes element with given value (if exists), then rebalances Red Black tree to fix color violations 
        bool remove (int val) override;

        // retrieves number of black nodes in any path from root to a leaf
        int getBlackHeight() const;

         // prints tree using directory-like notation, includes node key and color info
        friend void print(const RedBlackTree*);
};