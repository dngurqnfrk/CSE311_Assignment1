#include "IOHandler.h"
#include "test.h"
#include "ConventionalSort.h"
#include "ContemporarySort.h"
#include <string>

std::vector<absSort*> sort_func_arr;

int main(int argc, char* argv[]) {
    sort_func_arr = {new insertionSort, new testSort, new bubbleSort, new selectionSort,
                     new mergeSort, new heapSort, new quickSort,
                     new librarySort, new test_timSort(10), new timSort, new cocktailShakerSort,
                     new combSort, new tournamentSort, new introSort
                    };
    std::string test_name_arr[] = {"insertionSort", "testSort", "bubbleSort", "selectionSort",
                                   "mergeSort", "heapSort", "quickSort",
                                   "librarySort", "test_timSort", "timSort", "cocktailShakerSort",
                                   "combSort", "tournamentSort", "introSort"
                                  };
    std::cout << "argc : " << argc << std::endl;
    
    for(int i = 0; i < argc; i++) {
        std::cout << "argv " << i << " : " << argv[i] << std::endl;
    }

    std::string addr = argv[1];
    IOHandler ioh(addr);

    test t(1);
    for(int i = 0; i < sort_func_arr.size(); i++) {
        t.insert_func(sort_func_arr[i]);
    }

    test_node* tn_arr = new test_node[ioh.get_num_arrs()];
    for(int j = 0; j < sort_func_arr.size(); j++) {
        std::cout  << "test[" << j << "] : " << test_name_arr[j] << std::endl; // DEBUG
        for(int i = 0; i < ioh.get_num_arrs(); i++) {
            tn_arr[i].arr = ioh.get_arr(i);
            t.start_test(tn_arr[i], j);

            std::cout << "Array is sorted in " << tn_arr[i].performance << "(s) time.\n";
        }
    }

    /*
    int k_max = 30;
    for (int i = 0 ; i < ioh.get_num_arrs(); i++) {
        double timSort_performance[1001];
        timSort_performance[0] = 9999;
        timSort_performance[1] = 9999;
        std::cout << "For array [" << i << "] : ";
        for (int k = 2; k < k_max; k++) {
            t.set_func_arr(new timSort(k), 8);
            tn_arr[i].arr = ioh.get_arr(i);
            t.start_test(tn_arr[i], 8);
            timSort_performance[k] = tn_arr[i].performance;
        }
        std::cout << "\n";

        int index[1001];
        for (int k = 0; k < 1000; k++) {
            index[k] = k;
        }

        for (int i_2 = 1; i_2 < k_max; i_2++) {
            double temp_2 = timSort_performance[i_2];
            int j_2 = i_2;
            while(timSort_performance[j_2 - 1] > temp_2 && j_2 > 0) {
                timSort_performance[j_2] = timSort_performance[j_2 - 1];
                index[j_2] = index[j_2 - 1];
                j_2--;
            }
            timSort_performance[j_2] = temp_2;
            index[j_2] = i_2;
        }
        
        for (int i_2 = 0; i_2 < 5; i_2++) {
            std::cout << "(" << i_2 << " order) : " << "[" << index[i_2] << "] - "
                      << timSort_performance[i_2] << "(s)\n";
        }
        std::cout << "\n----------------\n\n";
    }
    */

    return 0;
}