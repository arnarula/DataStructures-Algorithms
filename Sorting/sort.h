#pragma once
#include <vector>
#include <algorithm>
using namespace std;

using sortFunc = void (*)(vector<int>& args);

// merge sort - divide & conquer (bottom up) - merge sorted subarrays
void mergesort(vector<int>& v);
void mergesort(vector<int>& v, int l, int r);
void merge(vector<int>& v, int l, int r, int m);

// quick sort - divide & conquer (top down) - partition subarrays based off random pivot
void quicksort(vector<int>& v);
void quicksort(vector<int>& v, int l, int r);
int partition(vector<int>& v, int l, int r, int pivot);

// insertion sort - iterative - insert next element into trailing sorted array each iteration
void insertionsort(vector<int>& v);
void insertionsort(vector<int>& v, int l, int r);

// selection sort - iteratitve - select smallest remaining element each iteration
void selectionsort(vector<int>& v);
void selectionsort(vector<int>& v, int l, int r);

// bubble sort - iterative - highest element bubbles up each iteration
void bubblesort(vector<int>& v);
void bubblesort(vector<int>& v, int l, int r);

// counting or dictionary sort - memoization - calculates frequency count of all elements to generate sorting
void countingsort(vector<int>& v);
void countingsort(vector<int>& v, int mx);
void countingsort(vector<int>& v, int mn, int mx);

// bucket or radix sort - memoization - groups numbers into buckets, sorts buckets, then concatenates buckets
void bucketsort(vector<int>& v, sortFunc sort, int k);

// heap sort - max heap - grabs max element from heap, removes it, and restores heap variance each iteration
void heapsort(vector<int>& v);
void heapify(vector<int>& v);
void siftDown(vector<int>& v, int start, int end);

void print(const vector<int>& v);