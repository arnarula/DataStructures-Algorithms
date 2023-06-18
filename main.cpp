#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include "Trees/RedBlackTree.h"
#include "Trees/AVLTree.h"
// #include "heap.cpp"

using namespace std;

int main() {
    RedBlackTree tree;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }
    cout << tree << '\n';
    return 0;
}