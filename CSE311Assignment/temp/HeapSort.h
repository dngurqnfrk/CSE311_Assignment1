#pragma once
#include "sort.h"
#include <vector>

class heapSort : public absSort {
private:
    int heap_size;
public:
	heapSort() : heap_size(0) {}
	~heapSort() {}

	void sort(std::vector<int> &arr);
    void build_max_heap(std::vector<int> &arr);
    void max_heapify(std::vector<int> &arr, int index);
    void heap_sort(std::vector<int> &arr);
};

void heapSort::sort(std::vector<int> &arr) {
    heap_size = arr.size();
	if (heap_size < 2)
		return;

    build_max_heap(arr);
    heap_sort(arr);
}

void heapSort::build_max_heap(std::vector<int> &arr) {
    for (int i = heap_size / 2; i >= 0; i--)
        max_heapify(arr, i);
}

void heapSort::max_heapify(std::vector<int> &arr, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    
    int bigger_child = index;
    if (left < heap_size && arr[left] > arr[index])
        bigger_child = left;
    
    if (right < heap_size && arr[right] > arr[bigger_child])
        bigger_child = right;

    if (bigger_child != index) {
        swap(arr, index, bigger_child);
        max_heapify(arr, bigger_child);
    }
}

void heapSort::heap_sort(std::vector<int> &arr) {
    for(int i = arr.size() - 1; i > 0; i--) {
        heap_size--;
        swap(arr, 0, i);
        max_heapify(arr, 0);
    }
}