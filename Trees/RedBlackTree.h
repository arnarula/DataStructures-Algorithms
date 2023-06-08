#pragma once
#include "BinarySearchTree.h"

// red black nodes come in two flavors
enum colors { BLACK, RED }; 
#define isBlack(node) (!node || node->color == BLACK)
#define isRed(node) (node && node->color == RED)

#define RB(node) static_cast<RBNode*>(node)
#define RB_CONST(node) static_cast<const RBNode*>(node)

// nodes used in red black tree 
struct RBNode : TreeNode {
    enum colors color; // color of node
    TreeNode* parent; // parent node
    
    RBNode(int val) : color(RED), parent(nullptr), TreeNode(val) {};
    RBNode(string NIL) : color(BLACK), parent(nullptr), TreeNode() {};
    ~RBNode() { parent = nullptr; };
};

// red black tree is a type of self-balancing binary search tree
class RedBlackTree : public BinarySearchTree {

    private:
    
        // checks if violation occurs during removal
        bool checkViolation(RBNode* target, RBNode* replacement) const;

        // fixes violations of red black tree due to insertion and removal respectively
        void fixAdjacentRedViolation(RBNode* child);
        void fixBlackPathViolation(RBNode* child);

        // helper methods to perform rotations with respect to root of subtree
        RBNode* rotateLeft(RBNode* root);
        RBNode* rotateRight(RBNode* root);

        // transfers ownership of subtree from root to child, connecting it back to the tree
        void transferRoot(RBNode* root, RBNode* child);

        // overloaded public method for recursive height calculation
        int getBlackHeight(RBNode* root) const;
        
        // returns family info (e.g. uncle, grandfather, sibling, newphews) of a node
        tuple<RBNode*, RBNode*, RBNode*> getUpperFamily(RBNode* child) const;
        tuple<RBNode*, RBNode*, RBNode*, RBNode*> getLowerFamily(RBNode* child) const;

        // deletes node, removing its parent connection
        void deleteNode(RBNode* root);

        // inline functions to establish parent-child relationships
        void connectLeft(TreeNode* root, RBNode* child);
        void connectRight(TreeNode* root, RBNode* child);

        // prints red black tree using directory-like notation, includes node key and color (e.g. 1B)
        void print(const TreeNode* root, int depth, ostream& os) const override;

        // DEBUGGING: tests if red black tree requirements 
        bool noAdjacentReds(RBNode* root, colors parent) const;
        bool blackHeightConsistency(RBNode* root, int blackHeight, int target) const;

    public:
        // inserts element with given value, then rebalances Red Black tree to fix color violations
        void insert (int val) override;
        // removes element with given value (if exists), then rebalances Red Black tree to fix color violations 
        bool remove (int val) override;

        // retrieves number of black nodes in any path from root to a leaf
        int getBlackHeight() const;

        // returns true if red black tree meets all requirements :)
        bool isValidRedBlackTree() const;
};