#pragma once
#include "BinaryTree.h"
#include <vector>
#include <queue>

// binary search tree class
class BinarySearchTree : public BinaryTree {

    private:
        // collection of recursive helper functions
        int findMin(TreeNode* root) const; 
        int findMax(TreeNode* root) const; 

        int findPrev(TreeNode* root, int val, int max_prev) const;
        int findNext(TreeNode* root, int val, int max_prev) const;

        void inorder(TreeNode* root) const;
        void preorder(TreeNode* root) const;
        void postorder(TreeNode* root) const;

    protected:
        // recursively performs insert/remove operations with respect to tree
        virtual TreeNode* insertNode(TreeNode* root, int val);
        virtual TreeNode* removeNode(TreeNode* root, int val);
        
        // recursively searches if a value is present in tree 
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
        bool search(int val) const override;
        // returns count of key in tree
        int count(int val) const;

        // finds greatest element strictly less than given value; returns INT_MIN if none exists
        int findPrev(int val) const;
        // finds smallest element strictly greater than given value; returns INT_MAX if none exists
        int findNext(int val) const;

        // returns min element in tree
        int findMin() const;
        // returns max element in tree
        int findMax() const;
    
        // prints all elements in tree using the following DFS ordering
        void preorder() const;
        void inorder() const;
        void postorder() const;
        // prints all elements in tree using a breadth-first search ordering
        void BFSorder() const;
};