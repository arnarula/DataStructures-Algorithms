#include <vector>
#include <algorithm>
using namespace std;

void insertionsort(vector<int>& v);
void insertionsort(vector<int>& v, int l, int r);

// insertion sort - iterative - insert next element into trailing sorted array each iteration
void insertionsort(vector<int>& v, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int j = i;
        while (j > l && v[j] < v[j - 1]) {
            swap(v[j], v[j - 1]);
            j--;
        }
    }
}

void insertionsort(vector<int>& v) {
    return insertionsort(v, 0, v.size() - 1);
}