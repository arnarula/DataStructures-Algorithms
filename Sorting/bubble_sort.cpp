#include <vector>
#include <algorithm>
using namespace std;

void bubblesort(vector<int>& v);
void bubblesort(vector<int>& v, int l, int r);

// bubble sort - iterative - highest element bubbles up each iteration
void bubblesort(vector<int>& v, int l, int r) {
    for (int i = r; i > l + 1; i--) {
        for (int j = l; j < i; j++) {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
        }
    }
}

void bubblesort(vector<int>& v) {
    return bubblesort(v, 0, v.size() - 1);
}
