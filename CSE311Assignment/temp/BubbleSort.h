#pragma once
#include "sort.h"
#include <vector>

class bubbleSort : public absSort {
public:
	bubbleSort() {}
	~bubbleSort() {}

	void sort(std::vector<int> &arr);
};

void bubbleSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

	for (int i = arr.size(); i > 1; i--) {
        bool swaped = false;
		for (int j = 1; j < i; j++) {
            if (arr[j - 1] > arr[j]) {
                swap(arr, j - 1, j);
                swaped = true;
            }
        }

        if(!swaped)
            break;
	}
}