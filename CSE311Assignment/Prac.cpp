#include <iostream>
#include <thread>
#include <ctime>
#include <vector>
#include <chrono>

template <typename T>
int merge_sort_mt(std::vector<T>& arr, int size);
template <typename T>
int merge_sort_st(std::vector<T>& arr, int size);
template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right);
template <typename T>
void copy_vector(std::vector<T>& srt, std::vector<T>& dest);

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	unsigned int arr_size;
	std::cin >> arr_size;
	if (arr_size < 100) {
		std::cout << "ERROR : size of array must be bigger than 100.\n";
	}

	std::vector<int> arr_raw(arr_size);
	std::vector<int> arr_test(arr_size);
	arr_raw[0] = std::rand() % arr_size;
 	std::cout << "Raw Arr : [" << arr_raw[0];
	for (unsigned int i = 1; i < arr_size; i++) {
		arr_raw[i] = std::rand() % arr_size;
		if (i < 10 || i > arr_size - 10)
			std::cout << ", " << arr_raw[i];
		else if (i == 10) {
			std::cout << ", ... ";
		}
	}
	std::cout << "]\n\n";
	
	copy_vector(arr_raw, arr_test);
	auto start = std::chrono::high_resolution_clock::now();
	merge_sort_mt(arr_test, arr_size);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> exet_mt = end - start;
	std::cout << "Execution time(Multi thread) : " << exet_mt.count() << "(s)\n";
	
	copy_vector(arr_raw, arr_test);
	start = std::chrono::high_resolution_clock::now();
	merge_sort_st(arr_test, arr_size);
	end = std::chrono::high_resolution_clock::now();
	exet_mt = end - start;
	std::cout << "Execution time(Single thread) : " << exet_mt.count() << "(s)\n";

	std::cout << "Sorted Arr : [" << arr_test[0];
	for (unsigned int i = 1; i < arr_size; i++) {
		if (i < 10 || i > arr_size - 10)
			std::cout << ", " << arr_test[i];
		else if (i == 10) {
			std::cout << ", ... ";
			i = arr_size - 10;
		}
	}
	std::cout << "]\n";
	
	return 0;
}

template <typename T>
int merge_sort_mt(std::vector<T>& arr, int size) {
	unsigned int numT = std::thread::hardware_concurrency();

	int jump_size = 1;
	while (jump_size < size) {
		int left_index = 0;
		std::vector <std::thread> tarr;
		unsigned int t_index = 0;
		for (left_index; left_index < size; left_index += jump_size * 2) {
			if (t_index >= numT) {
				for (unsigned int i = 0; i < tarr.size(); i++)
					tarr[i].join();
				t_index = 0;
				tarr.clear();
			}

			int right_index = std::min(left_index + jump_size * 2 - 1, size - 1);
			int mid_index = std::min(left_index + jump_size - 1, size - 1);
			tarr.emplace_back(merge<T>, std::ref(arr), left_index, mid_index, right_index);
			t_index++;
		}

		for (unsigned int i = 0; i < tarr.size(); i++)
			tarr[i].join();

		jump_size *= 2;
	}

	return 0;
}

template <typename T>
int merge_sort_st(std::vector<T>& arr, int size) {
	int jump_size = 1;
	while (jump_size < size) {
		int left_index = 0;
		unsigned int t_index = 0;
		for (left_index; left_index < size; left_index += jump_size * 2) {
			int right_index = std::min(left_index + jump_size * 2 - 1, size - 1);
			int mid_index = std::min(left_index + jump_size - 1, size - 1);
			merge(arr, left_index, mid_index, right_index);
		}
		jump_size *= 2;
	}

	return 0;
}

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
	if (mid == right || left > mid || left > right)
		return;

	std::vector<T> larr(mid - left + 2);
	std::vector<T> rarr(right - mid + 1);

	for (int i = 0; i < mid - left + 1; i++) {
		larr[i] = arr[i + left];
	}

	T type_max = std::numeric_limits<T>::max();
	larr[mid - left + 1] = type_max;

	for (int i = 0; i < right - mid; i++) {
		rarr[i] = arr[i + mid + 1];
	}
	rarr[right - mid] = type_max;

	int li = 0;
	int ri = 0;

	for (int i = left; i < right + 1; i++) {
		if (larr[li] <= rarr[ri]) {
			arr[i] = larr[li];
			li++;
		} else {
			arr[i] = rarr[ri];
			ri++;
		}
	}
}

template <typename T>
void copy_vector(std::vector<T>& srt, std::vector<T>& dest) {
	for (int i = 0; i < srt.size(); i++) {
		dest[i] = srt[i];
	}
}