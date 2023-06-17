#include <vector>
#include <algorithm>
using namespace std;

void quicksort(vector<int>& v);
void quicksort(vector<int>& v, int l, int r);
int partition(vector<int>& v, int l, int r, int pivot);

// quick sort - divide & conquer (top down) - partition subarrays based off random pivot
void quicksort(vector<int>& v, int l, int r) {
    if (l >= r) return;
    int pivot = l + rand() % (r - l + 1);
    int m = partition(v, l, r, pivot);
    quicksort(v, l, m - 1);
    quicksort(v, m + 1, r);
}

void quicksort(vector<int>& v) {
    return quicksort(v, 0, v.size() - 1);
}

// partitions elements less than and greater than value of pivot
int partition(vector<int>& v, int l, int r, int pivot) {
    swap(v[l], v[pivot]);
    int p1 = l + 1, p2 = r;
    while (p1 <= p2) {
        if (v[p1] <= v[l]) {
            p1++;
            continue;
        }
        if (v[p2] >= v[l]) {
            p2--;
            continue;
        }
        swap(v[p1++], v[p2--]);
    }
    swap(v[l], v[p2]);
    return p2;
}