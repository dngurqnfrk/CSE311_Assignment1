#pragma once
#include <vector>
#include <iostream>

class absSort {
public:
	absSort() {};
	virtual void sort(std::vector<int>& arr) = 0;
};

static void swap(std::vector<int> &arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/* Function to print all elements of array for DEBUG*/
static void print_arr(std::vector<int> arr, int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == INT32_MIN)
			std::cout << " ** ";
		else
			std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}