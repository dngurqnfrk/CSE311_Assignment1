#pragma once
#include <vector>
#include <iostream>

class absSort {
public:
	absSort() {};
	virtual void sort(std::vector<int>& arr) = 0;
};

template <typename T>
void swap(std::vector<T> &arr, int i, int j) {
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template <typename T>
static void reverse_arr(std::vector<T>& arr, int start, int end) {
	while (start < end) {
		swap(arr, start, end);
		start++;
		end--;
	}
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