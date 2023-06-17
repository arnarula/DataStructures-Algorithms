#include "sort.h"

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

void mergesort(vector<int>& v) {
    return mergesort(v, 0, v.size() - 1);
}

void mergesort(vector<int>& v, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergesort(v, l, m);
    mergesort(v, m + 1, r);
    merge(v, l, r, m);
}

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

void quicksort(vector<int>& v) {
    return quicksort(v, 0, v.size() - 1);
}

void quicksort(vector<int>& v, int l, int r) {
    if (l >= r) return;
    int pivot = l + rand() % (r - l + 1);
    int m = partition(v, l, r, pivot);
    quicksort(v, l, m - 1);
    quicksort(v, m + 1, r);
}

void insertionsort(vector<int>& v) {
    return insertionsort(v, 0, v.size() - 1);
}

void insertionsort(vector<int>& v, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int j = i;
        while (j > l && v[j] < v[j - 1]) {
            swap(v[j], v[j - 1]);
            j--;
        }
    }
}

void selectionsort(vector<int>& v) {
    return selectionsort(v, 0, v.size() - 1);
}

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

void bubblesort(vector<int>& v) {
    return bubblesort(v, 0, v.size() - 1);
}

void bubblesort(vector<int>& v, int l, int r) {
    for (int i = r; i > l + 1; i--) {
        for (int j = l; j < i; j++) {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
        }
    }
}

void countingsort(vector<int>& v) {
    if (v.size() == 0) return;
    int mn = *min_element(v.begin(), v.end());
    int mx = *max_element(v.begin(), v.end());
    countingsort(v, mn, mx);
}

void countingsort(vector<int>& v, int mx) {
    countingsort(v, 0, mx);
}

void countingsort(vector<int>& v, int mn, int mx) {
    if (mn > mx) return;
    int memo[mx - mn + 1];
    memset(memo, 0, sizeof(memo));
    for (int i = 0; i < v.size(); i++)
        memo[v[i] - mn]++;
    int cnt = 0;
    for (int i = 0; i < mx - mn + 1 && cnt < v.size(); i++) {
        while (memo[i]--) {
            v[cnt++] = i + mn;
        }
    }
}

void bucketsort(vector<int>& v, sortFunc sort = countingsort, int k = 10) {
    if (v.size() == 0) return;
    vector<vector<int>> buckets(k);
    int mx = *max_element(v.begin(), v.end()) + 1;
    for (int num : v)
        buckets[k * num / mx].push_back(num);
    for (int i = 0; i < buckets.size(); i++) {
        if (sort == (void (*)(vector<int>&)) countingsort) {
            countingsort(buckets[i], mx * i / k, mx * (i + 1) / k);
        } else
            sort(buckets[i]);
    }
    int cnt = 0;
    for (auto bucket : buckets) {
        for (int num : bucket)
            v[cnt++] = num;
    }
}

void heapify(vector<int>& v) {
    int start = (v.size() - 2) / 2;
    while (start >= 0) {
        siftDown(v, start, v.size() - 1);
        start--;
    }
}

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

void heapsort(vector<int>& v) {
    heapify(v);
    int end = v.size() - 1;
    while (end > 0) {
        swap(v[0], v[end--]);
        siftDown(v, 0, end);
    }
}

void print(const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " \n"[i == v.size() - 1];
    }
}