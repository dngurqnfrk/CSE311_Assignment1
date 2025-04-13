#pragma once
#include "sort.h"
#include <vector>
#include <limits>
#include <random>

class insertionSort : public absSort {
public:
	insertionSort() {}
	~insertionSort() {}

	void sort(std::vector<int> &arr);
};

class bubbleSort : public absSort {
    public:
        bubbleSort() {}
        ~bubbleSort() {}
    
        void sort(std::vector<int> &arr);
};

class heapSort : public absSort {
    private:
        int heap_size;
    public:
        heapSort() : heap_size(0) {}
        ~heapSort() {}
    
        void sort(std::vector<int> &arr);
        void build_max_heap(std::vector<int> &arr, int start, int end);
        void max_heapify(std::vector<int> &arr, int index, int start, int end);
        void heap_sort(std::vector<int> &arr, int start, int end);
        void heap_index_sort(std::vector<int> &arr, int start, int end);
};

class selectionSort : public absSort {
    public:
        selectionSort() {}
        ~selectionSort() {}
    
        void sort(std::vector<int> &arr);
};

class testSort : public absSort {
    public:
        testSort () {}
        ~testSort() {}
    
        void sort(std::vector<int> &arr);
        int find_index(std::vector<int> &arr, int i);
};

class mergeSort : public absSort {
    public:
        mergeSort () {}
        ~mergeSort() {}
    
        void sort(std::vector<int> &arr);
        void merge_sort(std::vector<int> &arr, int start, int end);
        void merge(std::vector<int> &arr, int start, int mid, int end);
};

class quickSort : public absSort {
public:
    quickSort() {}
    ~quickSort() {}
    
    void sort(std::vector<int> &arr);
    void quick_sort(std::vector<int> &arr, int start, int end);
    int partition(std::vector<int> &arr, int start, int end);
    int median_of_3(std::vector<int> arr, int start, int end);
};