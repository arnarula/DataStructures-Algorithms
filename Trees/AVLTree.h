#pragma once
#include "BinarySearchTree.h"

#define AVL(node) static_cast<AVLNode*>(node)

// nodes used in AVLTree
struct AVLNode : TreeNode {
    int height; // height of subtree
    int balance_factor; // difference in heights of left & right subtrees
    
    AVLNode(int val) : height(0), balance_factor(0), TreeNode(val) {};
    ~AVLNode() { balance_factor = height = 0; };
};

// AVL self-balancing binary search tree
class AVLTree : public BinarySearchTree {

    private:
        // overrides recursive insert/remove operations to perform self-balancing
        TreeNode* insertNode(TreeNode* root, int val) override;
        TreeNode* removeNode(TreeNode* root, int val) override;

        // helper methods to perform rotations with respect to root of subtree
        TreeNode* rotateLeft(TreeNode* root);
        TreeNode* rotateRight(TreeNode* root);

        // respondible for updating height of nodes and rebalancing tree when balance exceeds 1
        void updateHeight(TreeNode* root);
        TreeNode* rebalance(TreeNode* root);

    public:
        // inserts element with given value, then self balances AVL tree if necessary
        void insert (int val) override;
        // removes element with given value (if exists), then self balances AVL tree if necessary
        bool remove (int val) override;

        // returns difference of heights between left and right subtrees
        int getBalance() const { return AVL(m_root)->balance_factor; };
        // returns number of edges between root and farthest leaf
        int getHeight() const override { return AVL(m_root)->height; };
};