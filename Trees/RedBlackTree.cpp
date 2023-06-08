#include "RedBlackTree.h"

// inserts a red node with given value into BST, then rebalance tree to fix adjacent red violation
void RedBlackTree::insert(int val) {
    TreeNode* root = m_root, *parent = nullptr;
    // iterative search for insert location
    while (root) {
        parent = root;
        if (val > root->key) root = root->right;
        else if (val < root->key) root = root->left;
        else { root->count++; m_size++; return; }
    }
    // insert new node into tree
    RBNode* node = new RBNode(val);
    m_size++;
    if (!parent || val < parent->key)
        RedBlackTree::connectLeft(parent, node);
    else 
        RedBlackTree::connectRight(parent, node);
    // fix red parent violation
    RedBlackTree::fixAdjacentRedViolation(node);
}

// removes TreeNode with given value (if exists) from tree, then rebalances tree if a black path violation occurred
bool RedBlackTree::remove(int val) {
    // search for target node
    RBNode* target = RB(RedBlackTree::search(m_root, val));
    if (!target) return false;
    // if target node contains duplicates of key, decrement key count
    if (target->count > 1) { 
        target->count--, m_size--;
        return true;
    }
    // determine replacement node i.e. node that will replace target node
    RBNode* replacement;
    while (true) {
        // case 1 : no children - replacement is a black NIL leaf node
        if (!target->left && !target->right) {
            replacement = new RBNode("NIL");
            break;
        } 
        // case 2: one child - replacement is target's non-null child
        else if (!target->left || !target->right) {
            TreeNode* child = (target->left ? target->left : target->right);
            replacement = RB(child);
            break;
        }
        // case 3: two children - swap target info with inorder successor's, set successor to new target
        else {
            RBNode* successor = RB(RedBlackTree::findNextChild(target));
            swap(target->key, successor->key);
            swap(target->count, successor->count);
            target = successor;
        }
    }
    // replacement node replaces target's position
    transferRoot(target, replacement);
    // checks for black path violation, fixes tree if violation occurred
    if (checkViolation(target, replacement))
        fixBlackPathViolation(replacement);
    // delete target, delete replacement if placeholder NIL leaf
    delete(target);
    if (replacement->count == 0)
        deleteNode(replacement);
    m_size--;
    return true;
}

// fixes adjacent red nodes violation by rebalancing the tree
void RedBlackTree::fixAdjacentRedViolation(RBNode* child) {
    // obtain family information with respect to child node
    auto [parent, uncle, grandparent] = RedBlackTree::getUpperFamily(child);
    RBNode* root = RB(m_root);
    // case 1 - root color violation
    if (root->color == RED)
        root->color = BLACK;
    // case 2 - no red violation
    else if (parent->color == BLACK) {

    }
    // case 3 - red violation with red uncle -> color flip
    else if (uncle && uncle->color == RED) {
        grandparent->color = RED;
        parent->color = uncle->color = BLACK;
        RedBlackTree::fixAdjacentRedViolation(grandparent);
    }
    // case 4 - red violation with black uncle -> rotations
    else {
        // pivot = new root after rotation
        RBNode* pivot;
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

// checks if black path violation occurred during deletion
bool RedBlackTree::checkViolation(RBNode* target, RBNode* replacement) const {
    // case 1a - target = red -> normal BST deletion
    if (target->color == RED)
        return false;
    // case 1b - replacement = red -> normal BST deletion, replacement turns black
    else if (replacement->color == RED) {
        replacement->color = BLACK;
        return false;
    }
    // target & replacement both black - double black violation
    return true;
}

// fixes black path violation given a double black node
void RedBlackTree::fixBlackPathViolation(RBNode* child) {
    // case 2 - root is double black
    if (child == m_root) return;
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

// performs left rotation on subtree and updates children/parent connections
RBNode* RedBlackTree::rotateLeft(RBNode* root) {
    RBNode* child = RB(root->right);
    connectRight(root, RB(child->left));
    transferRoot(root, child);
    connectLeft(child, root);
    return child;
}
 
 // performs right rotation on subtree and updates children/parent connections
RBNode* RedBlackTree::rotateRight(RBNode* root) {
    RBNode* child = RB(root->left);
    connectLeft(root, RB(child->right));
    transferRoot(root, child);
    connectRight(child, root);
    return child; 
}

// replaces old root of subtree with new root (typically a child)
void RedBlackTree::transferRoot(RBNode* old_root, RBNode* new_root) {
    RBNode* parent = RB(old_root->parent);
    if (!parent || parent->left == old_root) 
        connectLeft(parent, new_root);
    else 
        connectRight(parent, new_root);
}

 // returns parent, uncle, and grandparent for a given node 
tuple<RBNode*, RBNode*, RBNode*> RedBlackTree::getUpperFamily(RBNode* child) const {
    RBNode* parent = RB(child->parent);
    RBNode* grandparent = (parent ? RB(parent->parent) : nullptr);
    RBNode* uncle = nullptr;
    if (grandparent) {
        if (parent == grandparent->left) 
            uncle = RB(grandparent->right);
        else 
            uncle = RB(grandparent->left);
    }
    return make_tuple(parent, uncle, grandparent);
}

// returns parent, sibling, and newphews for a given node
tuple<RBNode*, RBNode*, RBNode*, RBNode*> RedBlackTree::getLowerFamily(RBNode* child) const {
    RBNode* parent = RB(child->parent), *sibling = nullptr;
    if (parent) {
        if (parent->left == child)
            sibling = RB(parent->right);
        else
            sibling = RB(parent->left);
    }
    RBNode* newphewInner = (sibling ? RB(sibling->left) : nullptr);
    RBNode* newphewOuter = (sibling ? RB(sibling->right) : nullptr);
    if (parent && sibling && parent->left == sibling) swap(newphewInner, newphewOuter);
    return make_tuple(parent, sibling, newphewInner, newphewOuter);
}

// returns number of black nodes traversed from root to any leaf (constant in RB tree)
int RedBlackTree::getBlackHeight(RBNode* root) const {
    if (!root) return 0;
    return RedBlackTree::getBlackHeight(RB(root->left)) + (root->color == BLACK);
}

int RedBlackTree::getBlackHeight() const {
    RBNode* root = RB(m_root);
    return RedBlackTree::getBlackHeight(root);
}

// establish a left connection between root and child
inline void RedBlackTree::connectLeft(TreeNode* root, RBNode* child) {
    if (!root) m_root = child;
    else root->left = child;
    if (child) child->parent = root;
}

// establish a right connection between root and child
inline void RedBlackTree::connectRight(TreeNode* root, RBNode* child) {
    if (!root) m_root = child;
    else root->right = child;
    if (child) child->parent = root;
}

// delete parent connection when calling node desconstructor
void RedBlackTree::deleteNode(RBNode* root) {
    TreeNode* parent = root->parent;
    if (parent) {
        if (parent->left == root) parent->left = nullptr;
        else if (parent->right == root) parent->right = nullptr;
    } else {
        m_root = nullptr;
    }
    delete(root);
}

 // prints red black tree using directory-like notation
void RedBlackTree::print(const TreeNode* root, int depth, ostream& os) const {
    for (int i = 0; i < depth - 1; i++) {
        cout << "  ";
    }
    if (depth >= 1)
        os << "|-";
    if (!root) {
        os << 'X' << '\n';
        return;
    }
    // for each node, prints key value followed by color initial
    os << root->key << (RB_CONST(root)->color == BLACK ? 'B' : 'R') << '\n';
    print(root->right, depth + 1, os);
    print(root->left, depth + 1, os);
}

// DEBUGGING TOOLS:

// debugging test: checks if red black tree meets all requirements
bool RedBlackTree::isValidRedBlackTree() const {
    RBNode* root = RB(m_root);
    bool req1 = isBlack(root);
    bool req2 = RedBlackTree::noAdjacentReds(root, BLACK);
    bool req3 = RedBlackTree::blackHeightConsistency(root, 0, RedBlackTree::getBlackHeight());
    return req1 && req2 && req3;
}

// requirement 1: no two red nodes in red black tree are adjacent
bool RedBlackTree::noAdjacentReds(RBNode* root, colors parent) const {
    if (!root) return true;
    if (root->color == RED && parent == RED) return false;
    return RedBlackTree::noAdjacentReds(RB(root->left), root->color) 
        && RedBlackTree::noAdjacentReds(RB(root->right), root->color);
}

// requirement 2: all paths to leaves pass through the same number of black nodes
bool RedBlackTree::blackHeightConsistency(RBNode* root, int blackHeight, int target) const {
    if (!root) return blackHeight == target;
    if (root->color == BLACK) blackHeight++;
    return RedBlackTree::blackHeightConsistency(RB(root->left), blackHeight, target)
        && RedBlackTree::blackHeightConsistency(RB(root->right), blackHeight, target);
}
