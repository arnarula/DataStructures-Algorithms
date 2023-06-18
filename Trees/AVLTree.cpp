#include "AVLTree.h"

// inserts node with given value into BST, then rebalance AVL tree
TreeNode* AVLTree::insertNode(TreeNode* root, int val) {
    // tree has 0 nodes
    if (!root) {
        return new AVLNode(val);
    }
    // recursively find insertion location
    if (val > root->key) {
        root->right = AVLTree::insertNode(root->right, val);
    } else if (val < root->key) {
        root->left = AVLTree::insertNode(root->left, val);
    } else {
        root->count++;
        return root;
    }
    // recursively update height & rebalance node in insertion path
    AVLTree::updateHeight(root);
    return AVLTree::rebalance(root);
}

void AVLTree::insert(int val) {
    m_root = AVLTree::insertNode(m_root, val);
    m_size++;
}

// removes node with given value (if exists) from tree, then rebalances AVL tree
TreeNode* AVLTree::removeNode(TreeNode* root, int val) {
    // return false if node not found
    if (!root) return nullptr;
    // search for node to remove
    if (val != root->key) {
        if (val > root->key)
            root->right = AVLTree::removeNode(root->right, val);
        else
            root->left = AVLTree::removeNode(root->left, val);
        // recursively update height and rebalance nodes in removal path
        AVLTree::updateHeight(root);
        return AVLTree::rebalance(root);
    } 
    // found node to remove
    else {
        // CASE 0: if node has duplicates of key, decrement key count
        if (root->count > 1) {
            root->count--;
            m_size--;
            return root;
        }
        // CASE 1: node has no children - delete normally
        else if (!root->left && !root->right) {
            delete(root);
            m_size--;
            return nullptr;
        }
        // CASE 2: node has only one child - connect child to parent & delete
        else if (!root->right || !root->left) {
            TreeNode* child = root->right ? root->right : root->left;
            delete(root);
            m_size--;
            return child;
        }
        // CASE 3: node has two children - swap info with inorder successor's, delete successor
        else {
            TreeNode* successor = AVLTree::findNextChild(root);
            std::swap(root->key, successor->key);
            std::swap(root->count, successor->count);
            root->right = AVLTree::removeNode(root->right, successor->key);
            AVLTree::updateHeight(root);
            return AVLTree::rebalance(root);
        }
    }
}

// returns true if removal successful
bool AVLTree::remove(int val) {
    int size = m_size;
    m_root = AVLTree::removeNode(m_root, val);
    return m_size == size - 1; 
}

// self balances AVL tree
TreeNode* AVLTree::rebalance(TreeNode* parent) {
    // no rotation needed
    if (AVL(parent)->balance_factor < 2)
        return parent;
    // left subtree bigger than right subtree
    if (AVL(parent)->balance_factor < 0) {
         AVLNode* child = AVL(parent->left);
        // left left case
        if (child->balance_factor < 0)
            return AVLTree::rotateRight(parent);
        // left right case
        else {
            parent->left = AVLTree::rotateLeft(child);
            return AVLTree::rotateRight(parent);
        }
    } 
    // right subtree bigger than left subtree
    else {
        AVLNode* child = AVL(parent->right);
        // right left case
        if (child->balance_factor < 0) {
            parent->right = AVLTree::rotateRight(child);
            return AVLTree::rotateLeft(parent);
        }
        // right right case
        else
            return AVLTree::rotateLeft(parent);
    }
}

// performs left rotation around given root, updates affected nodes
TreeNode* AVLTree::rotateLeft(TreeNode* root) {
    TreeNode* child = root->right;
    root->right = child->left;
    child->left = root;
    AVLTree::updateHeight(root);
    AVLTree::updateHeight(child);
    return child;
}
 
 // performs right rotation around root, updates affected nodes
TreeNode* AVLTree::rotateRight(TreeNode* root) {
    TreeNode* child = root->left;
    root->left = child->right;
    child->right = root;
    AVLTree::updateHeight(root);
    AVLTree::updateHeight(child);
    return child;
}

// updates height and balance factor of a node
void AVLTree::updateHeight(TreeNode* root) {
    int left_height = (root->left ? AVL(root->left)->height : -1);
    int right_height = (root->right ? AVL(root->right)->height : -1);
    // balance factor = difference in heights betweem left and right subtree
    AVL(root)->balance_factor = right_height - left_height;
    AVL(root)->height = std::max(left_height, right_height) + 1;
}
