#include <vector>
#include <iostream>
#include <algorithm>

class FibonacciHeap {
    private:
        struct Node {
            int degree; // number of children nodes
            Node* parent, *child;
            Node* left, *right; // links nodes at same depth via circular doubly linked list 

            int key; // key value stored by node
            bool mark; // indicates whether the node has lost a child (for optimizing time complexity)

            Node(int p_key) : degree(0), parent(nullptr), child(nullptr), left(this), right(this), key(p_key), mark(false) {};
        };

        Node* min_root;
        int m_size; // total number of nodes

        // adds heap to root list
        void addHeap(Node* root) {
            if (!min_root)
                min_root = root;
            else
                addSibling(root, min_root);
            if (!min_root || min_root->key > root->key)
                min_root = root;
        }

        // merges two heaps - larger root becomes child of smaller root
        Node* mergeHeaps(Node* root1, Node* root2) {
            if (root1->key > root2->key)
                std::swap(root1, root2);
            // link siblings of larger root before and after removal
            linkSiblings(root2->left, root2->right);
            if (root1->child)
                addSibling(root2, root1->child);
            else {
                root1->child = root2;
                root2->left = root2->right = root2;
            }
            root1->degree++;
            root2->parent = root1;
            return root1;
        }

        // finds new min root after old min root is deleted
        void updateMin(Node* root) {
            Node *next = root;
            do {
                if (next->key < min_root->key)
                    min_root = next;
                next = next->right;
            } while (next != root);
        }

        // merges roots with same degree, ensuring fibonacci heap remains compact
        void consolidateTrees(Node* min_root) {
            std::vector<Node*> root_list((int) (log2(m_size)) + 1, nullptr); 
            Node* root = min_root;
            do {
                Node* next = root->right;
                if (!root_list[root->degree])
                    root_list[root->degree] = root;
                else {
                    Node* node = root;
                    while (true) {
                        Node* merged = mergeHeaps(node, root_list[node->degree]);
                        root_list[node->degree] = nullptr;
                        if (!root_list[node->degree + 1]) {
                            root_list[node->degree + 1] = merged;
                            break;
                        } else
                            node = merged;
                    }
                }
                root = next;
            } while (root != min_root);
        }

        // helper function to connect two adjacent nodes in heap
        void linkSiblings(Node* prev, Node* next) {
            prev->right = next;
            next->left = prev;
        }

        // helper function to establish new sibling connection in heap
        void addSibling(Node* node, Node* sibling) {
            node->right = sibling;
            node->left = sibling->left;
            sibling->left->right = node;
            sibling->left = node;
        }

        // represents fibonacci heap using directory-like notation (simulates depth)
        void print(Node* root, int depth) {
            Node* curr = root;
            do {
                for (int i = 0; i < depth - 1; i++) {
                    std::cout << "  ";
                }
                if (depth >= 1)
                    std::cout << "|-";
                if (!curr) {
                    std::cout << 'X' << '\n';
                    return;
                }
                std::cout << curr->key << '\n';
                print(curr->child, depth + 1);
                curr = curr->right;
            } while (curr != root);
        }

    public:

        FibonacciHeap() : min_root(nullptr), m_size(0) {};
        
        bool empty() const { return m_size == 0; }
        int size() const { return m_size; }

        const int& top() const { return min_root->key; }
        const int& front() const { return min_root->key; }

        // inserts element into fibonacci heap by creating new heap
        void push(int val) {
            // creates new heap with one node
            Node* root = new Node(val);
            // adds new heap to root list
            addHeap(root);
            m_size++;
        }
        
        // deletes min element of fibonacci heap, melds its children into root list
        void pop() {
            // setup tree to delete min root
            Node* child = min_root->child;
            Node* new_root = (min_root->left != min_root ? min_root->left : nullptr);
            if (new_root)
                linkSiblings(min_root->left, min_root->right);
            // delete min root
            delete min_root;
            m_size--;
            min_root = new_root;
            // update rest of fibonacci heap
            if (child) {
                Node* next = child;
                do {
                    addHeap(next);
                    next = next->right;
                } while (next != child);
            }
            // updates new min root & merges trees with same degrees
            updateMin(min_root);
            consolidateTrees(min_root);
        }

        // prints fibonacci heap using directory-like notation
        void print() {
            print(min_root, 0);
        }
};  

int main() {
    FibonacciHeap heap;
    for (int i = 1; i <= 32; i++)
        heap.push(i);
    heap.pop();
    heap.print();
    return 0;
}