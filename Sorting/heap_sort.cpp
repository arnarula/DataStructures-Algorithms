#include <vector>
#include <algorithm>
using namespace std;

// heap sort - max heap - grabs max element from heap, removes it, and restores heap variance each iteration
void heapsort(vector<int>& v);
void heapify(vector<int>& v);
void siftDown(vector<int>& v, int start, int end);

// create max-heap from unsorted array (first step in heapsort)
void heapify(vector<int>& v) {
    // start at last parent node (i.e. ignore all leaves since they can't sift down)
    int start = (v.size() - 2) / 2;
    // traverse tree bottom to top, sift all elements down while mantaining max-heap variant
    while (start >= 0) {
        siftDown(v, start, v.size() - 1);
        start--;
    }
}

// helper method: smallest element sifts down until max-heap property resatisfied
void siftDown(vector<int>& v, int start, int end) {
    while (true) {
        int l = 2 * start + 1;
        int r = 2 * start + 2;
        int max_index = start;
        if (l <= end && v[l] > v[max_index])
            max_index = l;
        if (r <= end && v[r] > v[max_index])
            max_index = r;
        if (start == max_index) return;
        swap(v[start], v[max_index]);
        start = max_index;
    }
} 

// sort vector by repeatedly sampling next max element from heap 
void heapsort(vector<int>& v) {
    heapify(v);
    // pick max element from heap, place at end of vector, restore heap variant, repeat
    int end = v.size() - 1;
    while (end > 0) {
        swap(v[0], v[end--]);
        siftDown(v, 0, end);
    }
}