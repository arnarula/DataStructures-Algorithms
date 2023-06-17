#include <vector>
#include <algorithm>
using namespace std;

void countingsort(vector<int>& v);
void countingsort(vector<int>& v, int mx);
void countingsort(vector<int>& v, int mn, int mx);

// counting or dictionary sort - memoization - calculates frequency count of all elements to generate sorting
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

void countingsort(vector<int>& v) {
    if (v.size() == 0) return;
    int mn = *min_element(v.begin(), v.end());
    int mx = *max_element(v.begin(), v.end());
    countingsort(v, mn, mx);
}

void countingsort(vector<int>& v, int mx) {
    countingsort(v, 0, mx);
}