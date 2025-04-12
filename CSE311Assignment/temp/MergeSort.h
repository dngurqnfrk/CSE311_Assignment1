#pragma once
#include "sort.h"
#include <vector>

class mergeSort : public absSort {
public:
    mergeSort () {}
	~mergeSort() {}

	void sort(std::vector<int> &arr);
    void merge_sort(std::vector<int> &arr, int start, int end);
    void merge(std::vector<int> &arr, int start, int mid, int end);
};

void mergeSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

    merge_sort(arr, 0, arr.size() - 1);
}

void mergeSort::merge_sort(std::vector<int> &arr, int start, int end) {
    if (start >= end)
        return;

    int mid = (start + end) / 2;
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}
    
void mergeSort::merge(std::vector<int> &arr, int start, int mid, int end) {
    int* front_arr = new int[mid - start + 2];
    int* back_arr = new int[end - mid + 1];

    for(int i = 0; i < mid - start + 2; i++) {
        front_arr[i] = arr[start + i];
    }
    front_arr[mid - start + 1] = std::numeric_limits<int>::max();

    for(int i = 0; i < end - mid; i++) {
        back_arr[i] = arr[mid + 1 + i];
    }
    back_arr[end - mid] = std::numeric_limits<int>::max();

    int fi = 0;
    int bi = 0;

    for (int i = start; i < end + 1; i++) {
		if (front_arr[fi] <= back_arr[bi]) {
			arr[i] = front_arr[fi];
			fi++;
		} else {
			arr[i] = back_arr[bi];
			bi++;
		}
	}
}