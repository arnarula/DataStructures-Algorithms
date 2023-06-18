#include "BinaryTree.h"

// recursively calculates height of tree
int BinaryTree::findHeight(TreeNode* root) const {
    if (!root) return -1;
    return std::max(findHeight(root->left), findHeight(root->right)) + 1;
}

// returns number of edges from root node to furthest leaf
int BinaryTree::getHeight() const {
    return BinaryTree::findHeight(m_root);
}

// represents tree using directory-like notation
void BinaryTree::print(const TreeNode* root, int depth, std::ostream& os) const {
    for (int i = 0; i < depth - 1; i++) {
        os << "  ";
    }
    if (depth >= 1)
        os << "|-";
    if (!root) {
        os << 'X' << '\n';
        return;
    }
    os << root->key << '\n';
    BinaryTree::print(root->right, depth + 1);
    BinaryTree::print(root->left, depth + 1);
}

// prints tree specifically to standard console output
void print(const BinaryTree& tree) {
    tree.print(tree.m_root, 0);
}

// prints tree to any output stream
std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
    tree.print(tree.m_root, 0, os);
    return os;
}

// deletes all nodes in tree (including root)
void BinaryTree::deleteTree(TreeNode* root) {
    if (!root) return;
    BinaryTree::deleteTree(root->left);
    BinaryTree::deleteTree(root->right);
    delete(root);
}