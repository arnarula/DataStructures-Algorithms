#pragma once
#include <algorithm>
#include <iostream>

// node used in binary tree
struct TreeNode  {
    TreeNode *left, *right;
    int key, count;

    TreeNode() : key(0), count(0), left(nullptr), right(nullptr) {};
    TreeNode(int val) : key(val), count(1), left(nullptr), right(nullptr) {};
    virtual ~TreeNode() {  left = right = nullptr; key = count = 0; };
};

// abstraction of binary ttree
class BinaryTree { 

    private:
        // calculates height of tree via DFS
        int findHeight(TreeNode* root) const;
        // deletes all nodes in tree recursively
        void deleteTree(TreeNode* root);

    protected:
        TreeNode* m_root; // root of tree
        int m_size; // size of tree

        // recursively prints tree values with offset correlated to depth
        virtual void print(const TreeNode* root, int depth, std::ostream& os = std::cout) const;

    public:
        BinaryTree() : m_size(0), m_root(nullptr) {}
        ~BinaryTree() { deleteTree(m_root); };
        
        // returns number of nodes in tree
        int getSize() const { return m_size; };
        // returns number of edges from root node to furthest leaf
        virtual int getHeight() const;

        // abstraction: ability to insert, remove, and search for elements
        virtual void insert(int val) = 0;
        virtual bool remove(int val) = 0;
        virtual bool search(int val) const = 0;

        // prints tree using directory-like notation
        friend void print(const BinaryTree&);
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);
};