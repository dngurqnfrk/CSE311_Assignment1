#include "test.h"

test::~test() {}

void test::insert_func(absSort* func) {
    test_func_num++;
    func_arr.emplace_back(func);
}

void test::start_test(test_node& tn, int index){
    if(is_empty_func_arr())
        return;

    std::vector<double> test_performance;
    double test_time = 0;
    for (int j = 0; j < test_iteration; j++) {
        std::vector<int> test_arr = tn.arr;
        auto start = std::chrono::high_resolution_clock::now();
        func_arr[index]->sort(test_arr);
        auto end = std::chrono::high_resolution_clock::now();           
        std::chrono::duration<double> exec_time = end - start;
        test_time += exec_time.count();
        
        if (!check_arr_sorted(test_arr)) {
            std::cout << "Array is not sorted :<\n";
        }
        
        std::cout << "Sorted Array is ";
        std::cout << test_arr[0] << ", " << test_arr[1] << ", " << test_arr[2] << ", ... , ";
        std::cout << test_arr[test_arr.size() - 2] << ", " << test_arr[test_arr.size() - 1] << std::endl;
        /*
        for(int i = 0; i < test_arr.size(); i++) {
            std::cout << test_arr[i] << " ";
        }
        std::cout << std::endl;
        */
    }

    tn.performance = test_time / test_iteration;
    // MODIFY : For fast test, I modify # of test for sort function.
}

int test::set_func_arr(absSort* func, int index) {
    if (index >= test_func_num)
        return -1;
    
    func_arr[index] = func;
}

bool test::is_empty_func_arr() {
    if (test_func_num < 1)
        return true;
    
    if (func_arr.empty())
        return true;

    return false;
}

bool check_arr_sorted(std::vector<int> arr) {
    if (arr.size() < 2)
        return true;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i])
            return false;
    }
    return true;
}
