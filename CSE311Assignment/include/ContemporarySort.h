#pragma once
#include "sort.h"
#include "ConventionalSort.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <stack>

static insertionSort basic_sort;
static mergeSort merge_sort;

class librarySort : public absSort {
private:
    int size;
    int max_size;
    int gap;
    int stage_ceil;

public:
    librarySort() : size(1), max_size(0), gap(INT32_MIN), stage_ceil(1) {}
    ~librarySort() {}

    void sort(std::vector<int> &arr);
    bool is_gap(int n) {return n == gap;}
    void gapped_insert(std::vector<int> &arr, int value);
    int find_gap(std::vector<int> &arr, int pivot_index);
    void rearrange(std::vector<int> &arr);
};

class test_timSort : public absSort {
private:
    int k;
public:
    test_timSort(int _k) : k(_k) {};
    ~test_timSort() {};

    void sort(std::vector<int> &arr);
    void tim_sort(std::vector<int> &arr, int start, int end);
    void insertion_sort(std::vector<int> &arr, int start, int end);
};

class timSort : public absSort {
private:
    std::vector<int> run_arr;
    int run_height;
    int stack_start;
public:
    timSort() : run_height(0), stack_start(0) {};
    ~timSort() {};

    void sort(std::vector<int> &arr);
    void probe_run(std::vector<int> &arr);
    void reverse_arr(std::vector<int> &arr, int start, int end);
    void merge_collapse(std::vector<int> &arr);
    void merge_force_collapse(std::vector<int> &arr);
};