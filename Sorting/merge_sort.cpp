#include <vector>
#include <algorithm>
using namespace std;

void mergesort(vector<int>& v);
void mergesort(vector<int>& v, int l, int r);
void merge(vector<int>& v, int l, int r, int m);

// merge sort - divide & conquer (bottom up) - sort subarrays then merge
void mergesort(vector<int>& v, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergesort(v, l, m);
    mergesort(v, m + 1, r);
    merge(v, l, r, m);
}

void mergesort(vector<int>& v) {
    return mergesort(v, 0, v.size() - 1);
}

// merges sorted subarrays using two pointer method
void merge(vector<int>& v, int l, int r, int m) {
    vector<int> temp;
    int p1 = l, p2 = m + 1;
    while (p1 <= m || p2 <= r) {
        if (p2 > r || p1 <= m && v[p1] <= v[p2])
            temp.push_back(v[p1++]);
        else
            temp.push_back(v[p2++]);
    }
    for (int i = l; i <= r; i++)
        v[i] = temp[i - l];
}
