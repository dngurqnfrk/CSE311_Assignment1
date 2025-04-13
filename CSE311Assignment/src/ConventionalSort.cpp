#include "ConventionalSort.h"

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

void bubbleSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    for (int i = arr.size(); i > 1;) {
        int not_swaped_index = 0;
        for (int j = 1; j < i; j++) {
            if (arr[j - 1] > arr[j]) {
                swap(arr, j - 1, j);
                not_swaped_index = j;
            }
        }

        i = not_swaped_index;
    }
}

void heapSort::sort(std::vector<int> &arr) {
    heap_size = arr.size();
    if (heap_size < 2)
        return;

    heap_index_sort(arr, 0, arr.size() - 1);
}

void heapSort::build_max_heap(std::vector<int> &arr, int start, int end) {
    for (int i = start + heap_size / 2; i >= start; i--)
        max_heapify(arr, i, start, end);
}

void heapSort::max_heapify(std::vector<int> &arr, int index, int start, int end) {
    int left = (index - start) * 2 + start + 1;
    if (arr.size() <= left)
        return;

    int right = (index - start) * 2 + start + 2;
    
    int bigger_child = index;
    if (left < heap_size + start && arr[left] > arr[index])
        bigger_child = left;
    
    if (right < heap_size + start && arr[right] > arr[bigger_child])
        bigger_child = right;

    if (bigger_child != index) {
        swap(arr, index, bigger_child);
        max_heapify(arr, bigger_child, start, end);
    }
}

void heapSort::heap_sort(std::vector<int> &arr, int start, int end) {
    for(int i = end; i > start; i--) {
        heap_size--;
        swap(arr, start, i);
        max_heapify(arr, start, start, end);
    }
}

void heapSort::heap_index_sort(std::vector<int> &arr, int start, int end) {
    heap_size = end - start + 1;

    build_max_heap(arr, start, end);
    heap_sort(arr, start, end);
}

void selectionSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

	for (int i = arr.size(); i > 1; i--) {
        int max = arr[0];
        int max_index = 0;
        for (int j = 1; j < i; j++) {
            if (arr[j] > max) {
                max = arr[j];
                max_index = j;
            }
        }
        swap(arr, max_index, i - 1);
	}
}

void testSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

	for (int i = 1; i < arr.size(); i++) {
		int start = find_index(arr, i);

        int temp = arr[i];
        for (int j = i; j > start; j--) {
            arr[j] = arr[j - 1];
        }
        arr[start] = temp;
	}
}

int testSort::find_index(std::vector<int> &arr, int i) {
    int start = 0;
    int end = i - 1;
    while(start < end) {
        int mid = (end + start) / 2;
        if (arr[mid] > arr[i]) {
            end = mid - 1;
        } else if (arr[mid] < arr[i]) {
            start = mid + 1;
        } else {
            start = mid + 1;
            end = mid + 1;
        }
    }

    if (arr[start] < arr[i])
        start++;

    return start;
}

void mergeSort::sort(std::vector<int> &arr) {
	if (arr.size() < 2)
		return;

    merge_sort(arr, 0, arr.size() - 1);
}

void mergeSort::merge_sort(std::vector<int> &arr, int start, int end) {
    if (start >= end)
        return;

    int mid = (start + end) / 2;
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}
    
void mergeSort::merge(std::vector<int> &arr, int start, int mid, int end) {
    int* front_arr = new int[mid - start + 2];
    int* back_arr = new int[end - mid + 1];

    for(int i = 0; i < mid - start + 2; i++) {
        front_arr[i] = arr[start + i];
    }
    front_arr[mid - start + 1] = std::numeric_limits<int>::max();

    for(int i = 0; i < end - mid; i++) {
        back_arr[i] = arr[mid + 1 + i];
    }
    back_arr[end - mid] = std::numeric_limits<int>::max();

    int fi = 0;
    int bi = 0;

    for (int i = start; i < end + 1; i++) {
		if (front_arr[fi] <= back_arr[bi]) {
			arr[i] = front_arr[fi];
			fi++;
		} else {
			arr[i] = back_arr[bi];
			bi++;
		}
	}
}

/* quickSort */
void quickSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    quick_sort(arr, 0, arr.size() - 1);
}

void quickSort::quick_sort(std::vector<int> &arr, int start, int end) {
    if (start >= end)
        return;

    int mid = partition(arr, start, end);
    quick_sort(arr, start, mid - 1);
    quick_sort(arr, mid + 1, end);
}

int quickSort::partition(std::vector<int> &arr, int start, int end) {
    int pivot = median_of_3(arr, start, end);
    swap(arr, pivot, end);
    pivot = arr[end];
    int partition_index = start - 1;
    for (int i = start; i < end; i++) {
        if(arr[i] < pivot) {
            partition_index++;
            swap(arr, partition_index, i);
        }
    }
    swap(arr, partition_index + 1, end);
    return partition_index + 1;
}

int quickSort::median_of_3(std::vector<int> &arr, int start, int end) {
    int n1 = arr[start];
    int n2 = arr[(start + end + 1) / 2];
    int n3 = arr[end];
    if (n1 > n2) {
        if (n2 > n3)
            return (start + end + 1) / 2;
        else if(n1 > n3)
            return end;
        else
            return start;
    } else {
        if (n2 < n3)
            return (start + end + 1) / 2;
        else if(n1 < n3)
            return end;
        else
            return start;
    }

    return -1;
}