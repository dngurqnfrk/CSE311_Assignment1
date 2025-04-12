#pragma once
#include <vector>
#include <chrono>
#include "IOHandler.h"
#include "sort.h"

typedef struct test_node_t {
    std::vector<int> arr;
    double performance;
} test_node; 

class test {
private:
    std::vector<absSort*> func_arr;
    int test_func_num;
    int test_iteration;
public:
    test(int i) : test_func_num(0), test_iteration(i) {}
    ~test();

    void insert_func(absSort* func);
    void start_test(test_node& tn, int index);
    int set_func_arr(absSort* func, int index);
    bool is_empty_func_arr();
};

bool check_arr_sorted(std::vector<int> arr);