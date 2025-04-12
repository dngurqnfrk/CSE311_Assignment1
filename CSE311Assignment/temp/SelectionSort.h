#pragma once
#include "sort.h"
#include <vector>

class selectionSort : public absSort {
public:
	selectionSort() {}
	~selectionSort() {}

	void sort(std::vector<int> &arr);
};

void selectionSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

	for (int i = arr.size(); i > 1; i--) {
        int max = arr[0];
        int max_index = 0;
        for (int j = 1; j < i; j++) {
            if (arr[j] > max) {
                max = arr[j];
                max_index = j;
            }
        }
        swap(arr, max_index, i - 1);
	}
}