#include <vector>
#include <iostream>
#include <algorithm>

#define leftChild(x) (2 * x + 1)
#define rightChild(x) (2 * x + 2)
#define parent(x) ((x - 1) / 2)

// creates heap compatiable with any data type and comparator (max heap by default)
// note: unlike standard priority queue implementation, the container, however, is fixed (vector)
template <typename T, typename C = std::less<T>>
class heap {
    private:
        std::vector<T> tree;

        // sifts root downward to restablish heap variant
        void siftDown(std::size_t index, const std::size_t end) {
            C cmp;
            while (index <= end) {
                std::size_t child = index;
                if (leftChild(index) <= end && cmp(tree[child], tree[leftChild(index)]))
                    child = leftChild(index);
                if (rightChild(index) <= end && cmp(tree[child], tree[rightChild(index)]))
                    child = rightChild(index);
                if (index == child) return;
                std::swap(tree[index], tree[child]);
                index = child;
            }
        }

        // sifts last leaf upward to restablish heap variant
        void siftUp(std::size_t index) {
            C cmp;
            while (index > 0 && cmp(tree[parent(index)], tree[index])) {
                std::swap(tree[parent(index)], tree[index]);
                index = parent(index);
            }
        }
    
    public:
        heap(std::vector<T>& p_tree) : tree(p_tree) { heapify(); }

        std::size_t size() const { return tree.size(); }
        bool empty() const { return tree.size() == 0; }
        
        // accesses first element of heap
        const T& top() const { return tree[0]; }
        const T& front() const { return tree[0]; }

        // inserts element into heap by creating new copy
        void push(const T& val) { 
            tree.push_back(val);
            siftUp(tree.size() - 1);
        }

        // inserts element into heap by "moving" its contents
        void push(T&& val) { 
            tree.push_back(std::move(val));
            siftUp(tree.size() - 1);
        }

        // removes root element from heap
        void pop() {
            if (tree.size() == 0) throw std::out_of_range("heap is empty, no element to remove");
            std::swap(tree[0], tree.back());
            tree.pop_back();
            if (tree.size()) siftDown(0, tree.size() - 1);
        }

        // creates heap in O(n) time
        void heapify() {
            if (tree.size() <= 1) return;
            std::size_t node = parent(tree.size() - 1);
            while (true) {
                siftDown(node, tree.size() - 1);
                if (node == 0) break;
                node--;
            }
        }

        // sorts heap according to comparator
        void heapSort() {
            if (tree.size() <= 1) return;
            std::size_t end = tree.size() - 1;
            while (end > 0) {
                std::swap(tree[0], tree[end]);
                siftDown(0, --end);
            }
        }

        // prints all elements in heap 
        void print() const {
            for (const T& node : tree)
                std::cout << node << ' ';
            std::cout << '\n';
        }
};