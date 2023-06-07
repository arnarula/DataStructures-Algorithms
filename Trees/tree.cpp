#include "tree.h"

// deletes all nodes in tree (including root)
void Tree::deleteTree(TreeNode* root) {
    if (!root) return;
    Tree::deleteTree(root->left);
    Tree::deleteTree(root->right);
    delete(root);
}

// print tree using directory-like notation
void print(const TreeNode* root, int depth) {
    for (int i = 0; i < depth - 1; i++) {
        cout << "  ";
    }
    if (depth >= 1)
        cout << "|-";
    if (!root) {
        cout << 'X' << '\n';
        return;
    }
    cout << root->key << '\n';
    print(root->right, depth + 1);
    print(root->left, depth + 1);
}

void print(const Tree* tree) {
    print(tree->m_root, 0);
}

// returns number of edges from root node to furthest leaf
int Tree::getHeight() const {
    return Tree::findHeight(m_root);
}

int Tree::findHeight(TreeNode* root) const {
    if (!root) return -1;
    return max(findHeight(root->left), findHeight(root->right)) + 1;
}

// inserts TreeNode with given value into BST
void BinarySearchTree::insert(int val) {
    m_root = BinarySearchTree::insertNode(m_root, val);
    m_size++;
}

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

// removes TreeNode with given value (if exists) from tree, returns if removal successful
bool BinarySearchTree::remove(int val) {
    int size = m_size;
    m_root = BinarySearchTree::removeNode(m_root, val);
    return m_size == size - 1;
}

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
        // CASE 0: if node has duplicates of same key, decrement key count
        if (root->count > 1) {
            root->count--;
            m_size--;
            return root;
        }
        // CASE 1: NO CHILDREN - delete node
        if (!root->left && !root->right) {
            delete(root);
            m_size--;
            return nullptr;
        }
        // CASE 2: ONLY ONE CHILD - connect child to parent
        else if (!root->right || !root->left) {
            TreeNode* child = root->right ? root->right : root->left;
            delete(root);
            m_size--;
            return child;
        }
        // CASE 3: BOTH CHILDREN - replace root with inorder successor & swap their info
        else {
            TreeNode* successor = BinarySearchTree::findNextChild(root);
            swap(root->key, successor->key);
            swap(root->count, successor->count);
            root->right = BinarySearchTree::removeNode(root->right, successor->key);
            return root;
        }
    }
}

// determines leftmost TreeNode of BST recursively
int BinarySearchTree::findMin() const {
    return BinarySearchTree::findMin(m_root);
}

int BinarySearchTree::findMin(TreeNode* root) const {
    if (!root) return INT_MIN;
    if (!root->left) return root->key;
    return BinarySearchTree::findMin(root->left);
}

// determines rightmost TreeNode of BST recursively
int BinarySearchTree::findMax() const {
    return BinarySearchTree::findMax(m_root);
}

int BinarySearchTree::findMax(TreeNode* root) const {
    if (!root) return INT_MAX;
    if (!root->right) return root->key;
    return BinarySearchTree::findMax(root->right);
}

// finds address of greatest child smaller than root TreeNode
TreeNode* BinarySearchTree::findPrevChild(TreeNode* root) const {
    root = root->left;
    if (!root) return nullptr;
    while (root->right)
        root = root->right;
    return root;
}

// finds address of smallest TreeNode greater than root TreeNode
TreeNode* BinarySearchTree::findNextChild(TreeNode* root) const {
    root = root->right;
    if (!root) return nullptr;
    while (root->left)
        root = root->left;
    return root;
}

// finds value of greatest element strictly smaller than given value
int BinarySearchTree::findPrev(int val) const {
    return BinarySearchTree::findPrev(m_root, val, INT_MIN);
}

int BinarySearchTree::findPrev(TreeNode* root, int val,  int max_prev) const {
    if (!root) return max_prev;
    if (val > root->key) {
        max_prev = max(max_prev, root->key);
        return BinarySearchTree::findPrev(root->right, val, max_prev);
    } else {
        return BinarySearchTree::findPrev(root->left, val, max_prev);
    }
}

// finds value of smallest element strictly greater than given value
int BinarySearchTree::findNext(int val) const {
    return BinarySearchTree::findNext(m_root, val, INT_MAX);
}

int BinarySearchTree::findNext(TreeNode* root, int val, int min_next) const {
    if (!root) return min_next;
   if (val < root->key) {
        min_next = min(min_next, root->key);
        return BinarySearchTree::findNext(root->left, val, min_next); 
   } else {
        return BinarySearchTree::findNext(root->right, val, min_next);
   }
}

// returns if Treenode with given value exists
bool BinarySearchTree::search(int val) const {
    TreeNode* node = BinarySearchTree::search(m_root, val);
    return (node != nullptr);
}

// finds address of TreeNode with given value (if exists)
TreeNode* BinarySearchTree::search(TreeNode* root, int val) const {
    if (!root) return nullptr;
    if (val > root->key) return BinarySearchTree::search(root->right, val);
    if (val < root->key) return BinarySearchTree::search(root->left, val);
    return root;
}

// returns count of key in BST
int BinarySearchTree::count(int val) const {
    TreeNode* node = BinarySearchTree::search(m_root, val);
    if (!node) return 0;
    return node->count;
}

// performs preorder traversal (TreeNode, left subtree, right subtree)
vector<int> BinarySearchTree::preorder() const {
    vector<int> v;
    BinarySearchTree::preorder(m_root, v);
    return v;
}

void BinarySearchTree::preorder(TreeNode* root, vector<int>& v) const {
    if (!root) return;
    v.push_back(root->key);
    BinarySearchTree::preorder(root->left, v);
    BinarySearchTree::preorder(root->right, v);
}

// performs inorder traversal (left subtree, TreeNode, right subtree)
vector<int> BinarySearchTree::inorder() const {
    vector<int> v;
    BinarySearchTree::inorder(m_root, v);
    return v;
}

void BinarySearchTree::inorder(TreeNode* root, vector<int>& v) const {
    if (!root) return;
    BinarySearchTree::inorder(root->left, v);
    v.push_back(root->key);
    BinarySearchTree::inorder(root->right, v);
}

// performs postorder traversal (left subtree, right subtree, TreeNode)
vector<int> BinarySearchTree::postorder() const {
    vector<int> v;
    BinarySearchTree::postorder(m_root, v);
    return v;
}

void BinarySearchTree::postorder(TreeNode* root, vector<int>& v) const {
    if (!root) return;
    BinarySearchTree::postorder(root->left, v);
    BinarySearchTree::postorder(root->right, v);
    v.push_back(root->key);
}

// performs breadth-first search traversal of BST
vector<int> BinarySearchTree::BFSorder() const {
    if (!m_root) return {};
    vector<int> v;
    queue<TreeNode*> q;
    q.push(m_root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto TreeNode = q.front(); q.pop();
            v.push_back(TreeNode->key);
            if (TreeNode->left) q.push(TreeNode->left);
            if (TreeNode->right) q.push(TreeNode->right);
        }
    }
    return v;
}

// prints tree structure to console output
std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {
    print(tree.m_root, 0);
    return os;
}

// inserts node with given value into BST, then rebalance AVL tree
void AVLTree::insert(int val) {
    m_root = AVLTree::insertNode(m_root, val);
    m_size++;
}

TreeNode* AVLTree::insertNode(TreeNode* root, int val) {
    // tree has 0 nodes
    if (!root) {
        return new AVLNode(val);
    }
    // recursively finds path of insertion
    if (val > root->key) {
        root->right = AVLTree::insertNode(root->right, val);
    } else if (val < root->key) {
        root->left = AVLTree::insertNode(root->left, val);
    } else {
        root->count++;
        return root;
    }
    // updates balance_factor and height of root after insertion
    AVLTree::updateBalance(root);
    return AVLTree::rebalance(root);
}

// removes TreeNode with given value (if exists) from tree, then rebalances AVL tree
bool AVLTree::remove(int val) {
    int size = m_size;
    m_root = AVLTree::removeNode(m_root, val);
    return m_size == size - 1;
}

TreeNode* AVLTree::removeNode(TreeNode* root, int val) {
    // return false if node not found
    if (!root) return nullptr;
    // search for node to remove
    if (val != root->key) {
        if (val > root->key)
            root->right = AVLTree::removeNode(root->right, val);
        else
            root->left = AVLTree::removeNode(root->left, val);
        // update height and balance factor based off removal path
        AVLTree::updateBalance(root);
        return AVLTree::rebalance(root);
    } 
    // found node to remove:
    // case 0: node has duplicate of same key
    if (root->count > 1) {
        root->count--;
        m_size--;
        return root;
    }
    // case 1: node has no children
    else if (!root->left && !root->right) {
        delete(root);
        m_size--;
        return nullptr;
    }
    // case 2: node has single child, connect child to node's parent
    else if (!root->right || !root->left) {
        TreeNode* child = root->right ? root->right : root->left;
        delete(root);
        m_size--;
        return child;
    }
    // case 3: node has two childrem, swap info with inorder successor's & delete successor
    else {
        TreeNode* successor = AVLTree::findNextChild(root);
        swap(root->key, successor->key);
        swap(root->count, successor->count);
        // recurse removal method on inorder successor
        root->right = AVLTree::removeNode(root->right, successor->key);
        AVLTree::updateBalance(root);
        return AVLTree::rebalance(root);
    }
}

// performs left rotation between two nodes and updates their heights
TreeNode* AVLTree::rotateLeft(TreeNode* root) {
    TreeNode* child = root->right;
    root->right = child->left;
    child->left = root;
    AVLTree::updateBalance(root);
    AVLTree::updateBalance(child);
    return child;
}
 
 // performs right rotation between two nodes and updates their heights
TreeNode* AVLTree::rotateRight(TreeNode* root) {
    TreeNode* child = root->left;
    root->left = child->right;
    child->right = root;
    AVLTree::updateBalance(root);
    AVLTree::updateBalance(child);
    return child;
}

// updates height and balance factor of a node
void AVLTree::updateBalance(TreeNode* root) {
    int left_height = (root->left ? static_cast<AVLNode*>(root->left)->height : -1);
    int right_height = (root->right ? static_cast<AVLNode*>(root->right)->height : -1);
    // balance factor = difference between heights of left and right subtree
    static_cast<AVLNode*>(root)->balance_factor = right_height - left_height;
    static_cast<AVLNode*>(root)->height = max(left_height, right_height) + 1;
}

// self balances AVL tree
TreeNode* AVLTree::rebalance(TreeNode* parent) {
    // no rotation needed
    if (abs(static_cast<AVLNode*>(parent)->balance_factor) < 2)
        return parent;
    // left subtree bigger than right subtree
    if (static_cast<AVLNode*>(parent)->balance_factor < 0) {
         AVLNode* child = static_cast<AVLNode*>(parent->left);
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
        AVLNode* child = static_cast<AVLNode*>(parent->right);
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

// prints red black tree using directory-like notation
void print(const RedBlackNode* root, int depth) {
    for (int i = 0; i < depth - 1; i++) {
        cout << "  ";
    }
    if (depth >= 1)
        cout << "|-";
    if (!root) {
        cout << 'X' << '\n';
        return;
    }
    // for each node, prints key value followed by color initial
    cout << root->key << (root->color == BLACK ? 'B' : 'R') << '\n';
    print(static_cast<const RedBlackNode*>(root->right), depth + 1);
    print(static_cast<const RedBlackNode*>(root->left), depth + 1);
}

void print(const RedBlackTree* tree) {
    print(static_cast<const RedBlackNode*>(tree->m_root), 0);
}

// returns parent, uncle, and grandparent for a given node 
tuple<RedBlackNode*, RedBlackNode*, RedBlackNode*> RedBlackTree::getUpperFamily(RedBlackNode* child) const {
    RedBlackNode* parent = static_cast<RedBlackNode*>(child->parent);
    RedBlackNode* grandparent = (parent ? static_cast<RedBlackNode*>(parent->parent) : nullptr);
    RedBlackNode* uncle = nullptr;
    if (grandparent) {
        if (parent == grandparent->left) uncle = static_cast<RedBlackNode*>(grandparent->right);
        else uncle = static_cast<RedBlackNode*>(grandparent->left);
    }
    return make_tuple(parent, uncle, grandparent);
}

// returns parent, sibling, and newphews for a given node
tuple<RedBlackNode*, RedBlackNode*, RedBlackNode*, RedBlackNode*> RedBlackTree::getLowerFamily(RedBlackNode* child) const {
    RedBlackNode* parent = static_cast<RedBlackNode*>(child->parent);
    RedBlackNode* sibling = nullptr;
    if (parent && parent->left == child) sibling = static_cast<RedBlackNode*>(parent->right);
    else if (parent && parent->right == child) sibling = static_cast<RedBlackNode*>(parent->left);
    RedBlackNode* newphewInner = (sibling ? static_cast<RedBlackNode*>(sibling->left) : nullptr);
    RedBlackNode* newphewOuter = (sibling ? static_cast<RedBlackNode*>(sibling->right) : nullptr);
    if (parent && sibling && parent->left == sibling) swap(newphewInner, newphewOuter);
    return make_tuple(parent, sibling, newphewInner, newphewOuter);
}

// delete parent connection when calling node desconstructor
void RedBlackTree::deleteNode(RedBlackNode* root) {
    TreeNode* parent = root->parent;
    if (parent) {
        if (parent->left == root) parent->left = nullptr;
        else if (parent->right == root) parent->right = nullptr;
    } else {
        m_root = nullptr;
    }
    delete(root);
}

// connects new root to rest of red black tree
void RedBlackTree::transferRoot(RedBlackNode* old_root, RedBlackNode* new_root) {
    if (!old_root->parent) m_root = new_root;
    else if (old_root->parent->left == old_root) old_root->parent->left = new_root;
    else if (old_root->parent->right == old_root) old_root->parent->right = new_root;
    if (new_root) new_root->parent = old_root->parent;
}

// performs left rotation on subtree and updates children/parent connections
RedBlackNode* RedBlackTree::rotateLeft(RedBlackNode* root) {
    RedBlackNode* child = static_cast<RedBlackNode*>(root->right);
    root->right = child->left;
    if (child->left) static_cast<RedBlackNode*>(child->left)->parent = root;
    transferRoot(root, child);
    child->left = root;
    root->parent = child;
    return child;
}
 
 // performs right rotation on subtree and updates children/parent connections
RedBlackNode* RedBlackTree::rotateRight(RedBlackNode* root) {
    RedBlackNode* child = static_cast<RedBlackNode*>(root->left);
    root->left = child->right;
    if (child->right) static_cast<RedBlackNode*>(child->right)->parent = root;
    transferRoot(root, child);
    child->right = root;
    root->parent = child;
    return child; 
}

// inserts node with given value into BST, then rebalance red black tree
void RedBlackTree::insert(int val) {
    TreeNode* root = m_root, *parent = nullptr;
    // iterative search for insert location
    while (root) {
        parent = root;
        if (val > root->key) root = root->right;
        else if (val < root->key) root = root->left;
        else { root->count++; return; }
    }
    // insert new node into tree
    RedBlackNode* node = new RedBlackNode(val);
    if (!parent) m_root = node;
    else if (val < parent->key) parent->left = node;
    else parent->right = node;
    node->parent = parent;
    // fix red parent violation
    RedBlackTree::fixAdjacentRedViolation(node);
}

// removes TreeNode with given value (if exists) from tree, then rebalances red black tree
bool RedBlackTree::remove(int val) {
    RedBlackNode* target = static_cast<RedBlackNode*>(RedBlackTree::search(m_root, val));
    if (!target) return false;
    // duplicate of key value present
    if (target->count > 1) { 
        target->count--, m_size--;
        return true;
    }
    // determine replacement node i.e. node that will replace target node
    RedBlackNode* replacement;
    while (true) {
        if (!target->left && !target->right) {
            replacement = new RedBlackNode("NIL");
            break;
        } 
        else if (!target->left || !target->right) {
            TreeNode* child = (target->left ? target->left : target->right);
            replacement = static_cast<RedBlackNode*>(child);
            break;
        }
        else {
            RedBlackNode* successor = static_cast<RedBlackNode*>(RedBlackTree::findNextChild(target));
            swap(target->key, successor->key);
            swap(target->count, successor->count);
            target = successor;
        }
    }

    // replacement node replaces target node's position
    transferRoot(target, replacement);
    // check for black path violation and fix if necessary
    if (checkViolation(target, replacement))
        fixBlackPathViolation(replacement);
    // delete replacement if NIL black leaf
    if (replacement->count == 0) deleteNode(replacement);
    delete(target); m_size--;
    return true;
}

// self balances Red Black tree
void RedBlackTree::fixAdjacentRedViolation(RedBlackNode* child) {
    // obtain family information with respect to child node
    auto [parent, uncle, grandparent] = RedBlackTree::getUpperFamily(child);
    RedBlackNode* root = static_cast<RedBlackNode*>(m_root);
    // case 0 - root color violation
    if (root->color == RED)
         root->color = BLACK;
    // case 1 - no red violation
    else if (parent->color == BLACK) {
        // do nothing :)
    }
    // case 2 - red violation with red uncle -> color flip
    else if (uncle && uncle->color == RED) {
        grandparent->color = RED;
        parent->color = uncle->color = BLACK;
        RedBlackTree::fixAdjacentRedViolation(grandparent);
    }
    // case 3 - red violation with black uncle -> rotations
    else {
        // pivot = new root after rotation
        RedBlackNode* pivot;
        if (grandparent->left == parent) {
            // left right case
            if (parent->right == child) {
                rotateLeft(parent);
                pivot = rotateRight(grandparent);
            } 
            // left left case
            else {
                pivot = rotateRight(grandparent);
            }
        } else {
            // right left case
            if (parent->left == child) {
                rotateRight(parent);
                pivot = rotateLeft(grandparent);
            } 
            // right right case
            else {
                pivot = rotateLeft(grandparent);
            }
        }
        swap(pivot->color, grandparent->color);
    }
}   

bool RedBlackTree::checkViolation(RedBlackNode* target, RedBlackNode* replacement) const {
    // case 1 - target = red -> normal BST deletion
    if (target->color == RED)
        return false;
    // case 1 - replacement = red -> normal BST deletion, changes color
    else if (replacement->color == RED) {
        replacement->color = BLACK;
        return false;
    }
    // target & replacement both black - double black violation
    return true;
}

// fixes black path violation given a double black node
void RedBlackTree::fixBlackPathViolation(RedBlackNode* child) {
    // case 2 - root is double black
    if (child == m_root)
        return;
    // obtain family information with respect to child node
    auto [parent, sibling, nephewInner, nephewOuter] = RedBlackTree::getLowerFamily(child);
    int DB_direction = (parent->right == child ? 1 : -1);
    // case 3 - sibling is red
    if (isRed(sibling)) { 
        swap(parent->color, sibling->color);
        DB_direction == 1 ? RedBlackTree::rotateRight(parent) : RedBlackTree::rotateLeft(parent); 
        RedBlackTree::fixBlackPathViolation(child);
    } 
    // case 4 - sibling is black or DNE, newphews are both black
    else if (!sibling || isBlack(sibling) && isBlack(nephewInner) && isBlack(nephewOuter)) {
        if (sibling) sibling->color = RED;
        if (parent->color == RED) parent->color = BLACK;
        else RedBlackTree::fixBlackPathViolation(parent);
    }
    // case 5 - sibling & outer nephew are black, inner nephew is red
    else if (isBlack(sibling) && isRed(nephewInner) && isBlack(nephewOuter)) {
        swap(sibling->color, nephewInner->color);
        DB_direction == 1 ? RedBlackTree::rotateLeft(sibling) : RedBlackTree::rotateRight(sibling);
        RedBlackTree::fixBlackPathViolation(child);
    }
    // case 6 - sibling is black, outer nephew is red
    else {
        swap(parent->color, sibling->color);
        nephewOuter->color = BLACK;
        DB_direction == 1 ? RedBlackTree::rotateRight(parent) : RedBlackTree::rotateLeft(parent); 
    }
}

int RedBlackTree::getBlackHeight() const {
    RedBlackNode* root = static_cast<RedBlackNode*>(m_root);
    return RedBlackTree::getBlackHeight(root);
}

int RedBlackTree::getBlackHeight(RedBlackNode* root) const {
    if (!root) return 0;
    return RedBlackTree::getBlackHeight(static_cast<RedBlackNode*>(root->left)) + (root->color == BLACK);
}


 bool RedBlackTree::validRedBlackTree() const {
    RedBlackNode* root = static_cast<RedBlackNode*>(m_root);
    return RedBlackTree::noAdjacentReds(root) && blackHeightConsistency(root, 0, RedBlackTree::getBlackHeight());
 }

bool RedBlackTree::noAdjacentReds(RedBlackNode* root) const {
    if (!root) return true;
    RedBlackNode* left = static_cast<RedBlackNode*>(root->left), *right = static_cast<RedBlackNode*>(root->right);
    if (root->color == RED && (isRed(left) || isRed(right)))
        return false;
    return RedBlackTree::noAdjacentReds(left) && RedBlackTree::noAdjacentReds(right);
 }

bool RedBlackTree::blackHeightConsistency(RedBlackNode* root, int blackHeight, int target) const {
    if (!root) return blackHeight == target;
    RedBlackNode* left = static_cast<RedBlackNode*>(root->left), *right = static_cast<RedBlackNode*>(root->right);
    if (root->color == BLACK) blackHeight++;
    return RedBlackTree::blackHeightConsistency(left, blackHeight, target)
           && RedBlackTree::blackHeightConsistency(right, blackHeight, target);
 }