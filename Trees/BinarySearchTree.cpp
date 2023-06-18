#include "BinarySearchTree.h"

// inserts TreeNode with given value into BST
TreeNode* BinarySearchTree::insertNode(TreeNode* root, int val) {
    // tree has 0 nodes
    if (!root) {
        return new TreeNode(val);
    }
    // recursively find path of insertion
    if (val > root->key) {
        root->right = BinarySearchTree::insertNode(root->right, val);
    } else if (val < root->key) {
        root->left = BinarySearchTree::insertNode(root->left, val);
    } else {
        root->count++;
        return root;
    }
    return root;
}

void BinarySearchTree::insert(int val) {
    m_root = BinarySearchTree::insertNode(m_root, val);
    m_size++;
}

// removes TreeNode with given value (if exists) from tree, returns if removal successful
TreeNode* BinarySearchTree::removeNode(TreeNode* root, int val) {
    // return false if node not found
    if (!root) return nullptr;
    // search for node to remove
    if (val != root->key) { 
        if (val > root->key)
            root->right = BinarySearchTree::removeNode(root->right, val);
        else if (val < root->key)
            root->left = BinarySearchTree::removeNode(root->left, val); 
        return root;
    }
    // found node with given value to remove!
    else {
        // CASE 0: if node has duplicates of key, decrement key count
        if (root->count > 1) {
            root->count--;
            m_size--;
            return root;
        }
        // CASE 1: node has no children - delete normally
        if (!root->left && !root->right) {
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
        // CASE 3: node has two children - swap node info with inorder successor's, remove successor
        else {
            TreeNode* successor = BinarySearchTree::findNextChild(root);
            std::swap(root->key, successor->key);
            std::swap(root->count, successor->count);
            root->right = BinarySearchTree::removeNode(root->right, successor->key);
            return root;
        }
    }
}

bool BinarySearchTree::remove(int val) {
    int size = m_size;
    m_root = BinarySearchTree::removeNode(m_root, val);
    return m_size == size - 1;
}

// returns pointer to node with given value (if exists)
TreeNode* BinarySearchTree::search(TreeNode* root, int val) const {
    if (!root) return nullptr;
    if (val > root->key) return BinarySearchTree::search(root->right, val);
    if (val < root->key) return BinarySearchTree::search(root->left, val);
    return root;
}

// returns boolean if node with given value exists
bool BinarySearchTree::search(int val) const {
    TreeNode* node = BinarySearchTree::search(m_root, val);
    return (node != nullptr);
}

// returns count of key in BST
int BinarySearchTree::count(int val) const {
    TreeNode* node = BinarySearchTree::search(m_root, val);
    if (!node) return 0;
    return node->count;
}

// determines min/leftmost TreeNode of BST recursively
int BinarySearchTree::findMin(TreeNode* root) const {
    if (!root) return INT_MIN;
    if (!root->left) return root->key;
    return BinarySearchTree::findMin(root->left);
}

int BinarySearchTree::findMin() const {
    return BinarySearchTree::findMin(m_root);
}

// determines max/rightmost TreeNode of BST recursively
int BinarySearchTree::findMax(TreeNode* root) const {
    if (!root) return INT_MAX;
    if (!root->right) return root->key;
    return BinarySearchTree::findMax(root->right);
}

int BinarySearchTree::findMax() const {
    return BinarySearchTree::findMax(m_root);
}

// finds address of greatest child smaller than root
TreeNode* BinarySearchTree::findPrevChild(TreeNode* root) const {
    root = root->left;
    if (!root) return nullptr;
    while (root->right)
        root = root->right;
    return root;
}

// returns value of greatest node strictly smaller than given value, returns INT_MIN if none found
int BinarySearchTree::findPrev(TreeNode* root, int val,  int max_prev) const {
    if (!root) return max_prev;
    if (val > root->key) {
        max_prev = std::max(max_prev, root->key);
        return BinarySearchTree::findPrev(root->right, val, max_prev);
    } else {
        return BinarySearchTree::findPrev(root->left, val, max_prev);
    }
}

int BinarySearchTree::findPrev(int val) const {
    return BinarySearchTree::findPrev(m_root, val, INT_MIN);
}

// finds address of smallest child greater than root
TreeNode* BinarySearchTree::findNextChild(TreeNode* root) const {
    root = root->right;
    if (!root) return nullptr;
    while (root->left)
        root = root->left;
    return root;
}

// returns value of smallest node strictly greater than given value, returns INT_MAX if none found
int BinarySearchTree::findNext(TreeNode* root, int val, int min_next) const {
    if (!root) return min_next;
   if (val < root->key) {
        min_next = std::min(min_next, root->key);
        return BinarySearchTree::findNext(root->left, val, min_next); 
   } else {
        return BinarySearchTree::findNext(root->right, val, min_next);
   }
}

int BinarySearchTree::findNext(int val) const {
    return BinarySearchTree::findNext(m_root, val, INT_MAX);
}

// prints preorder traversal
void BinarySearchTree::preorder(TreeNode* root) const {
    if (!root) return;
    std::cout << root->key << ' ';
    BinarySearchTree::preorder(root->left);
    BinarySearchTree::preorder(root->right);
}

void BinarySearchTree::preorder() const {
    BinarySearchTree::preorder(m_root);
}

// performs inorder traversal 
void BinarySearchTree::inorder(TreeNode* root) const {
    if (!root) return;
    BinarySearchTree::inorder(root->left);
    std::cout << root->key << ' ';
    BinarySearchTree::inorder(root->right);
}

void BinarySearchTree::inorder() const {
    BinarySearchTree::inorder(m_root);
}

// performs postorder traversal
void BinarySearchTree::postorder(TreeNode* root) const {
    if (!root) return;
    BinarySearchTree::postorder(root->left);
    BinarySearchTree::postorder(root->right);
    std::cout << root->key << ' ';
}

void BinarySearchTree::postorder() const {
    BinarySearchTree::postorder(m_root);
}

// performs breadth-first search traversal
void BinarySearchTree::BFSorder() const {
    if (!m_root) return;
    std::queue<TreeNode*> q;
    q.push(m_root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto node = q.front(); q.pop();
            std::cout << node->key << ' ';
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
}