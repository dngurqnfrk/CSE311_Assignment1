#pragma once
#include "sort.h"
#include <vector>

class testSort : public absSort {
public:
    testSort () {}
	~testSort() {}

	void sort(std::vector<int> &arr);
    int find_index(std::vector<int> &arr, int i);
};

void testSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

	for (int i = 1; i < arr.size(); i++) {
		int start = find_index(arr, i);

        int temp = arr[i];
        for (int j = i; j > start; j--) {
            arr[j] = arr[j - 1];
        }
        arr[start] = temp;
	}
}

int testSort::find_index(std::vector<int> &arr, int i) {
    int start = 0;
    int end = i - 1;
    while(start < end) {
        int mid = (end + start) / 2;
        if (arr[mid] > arr[i]) {
            end = mid - 1;
        } else if (arr[mid] < arr[i]) {
            start = mid + 1;
        } else {
            start = mid + 1;
            end = mid + 1;
        }
    }

    if (arr[start] < arr[i])
        start++;

    return start;
}