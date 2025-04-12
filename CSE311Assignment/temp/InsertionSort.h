#pragma once
#include "sort.h"
#include <vector>

class insertionSort : public absSort {
public:
	insertionSort() {}
	~insertionSort() {}

	void sort(std::vector<int> &arr);
};

void insertionSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

	for (int i = 1; i < arr.size(); i++) {
		int j = i - 1;
		int temp = arr[i];
		while (j >= 0 && temp < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}