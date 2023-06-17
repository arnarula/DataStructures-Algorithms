#include <vector>
#include <algorithm>
#include <sort.h>
using namespace std;

// using sortFunc = void (*)(vector<int>& args);
// void bucketsort(vector<int>& v, sortFunc sort, int k);

// bucket or radix sort - memoization - groups numbers into buckets, sorts buckets, then concatenates buckets
void bucketsort(vector<int>& v, sortFunc sort = countingsort, int k = 10) {
    if (v.size() == 0) return;
    vector<vector<int>> buckets(k);
    int mx = *max_element(v.begin(), v.end()) + 1;
    for (int num : v)
        buckets[k * num / mx].push_back(num);
    for (int i = 0; i < buckets.size(); i++) {
        if (sort == (void (*)(vector<int>&)) countingsort)
            countingsort(buckets[i], mx * i / k, mx * (i + 1) / k);
        else
            sort(buckets[i]);
    }
    int cnt = 0;
    for (auto bucket : buckets) {
        for (int num : bucket)
            v[cnt++] = num;
    }
}