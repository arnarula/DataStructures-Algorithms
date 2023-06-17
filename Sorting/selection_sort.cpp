#include <vector>
#include <algorithm>
using namespace std;

void selectionsort(vector<int>& v);
void selectionsort(vector<int>& v, int l, int r);

// selection sort - iterative - select smallest remaining element each iteration
void selectionsort(vector<int>& v, int l, int r) {
    for (int i = l; i < r; i++) {
        int mn = i;
        for (int j = i + 1; j <= r; j++) {
            if (v[j] < v[mn])
                mn = j;
        }
        swap(v[i], v[mn]);
    }
}

void selectionsort(vector<int>& v) {
    return selectionsort(v, 0, v.size() - 1);
}