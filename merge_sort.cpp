
#include <iostream>
#include "tools.h"
using namespace std;

class MergeSort {
private:
	static bool is_less(int x, int y) {
		return x < y;
	}

public:
	static void merge(int a[], int low, int mid, int high, int aux[]) {
		// 将 a[low..mid] 和 a[mid + 1..high] 归并
		int i = low, j = mid + 1;
		for (int k = low; k <= high; ++k) {
			// 将 a[low..high] 复制到 aux[low..high]
			aux[k] = a[k];
		}

		for (int k = low; k <= high; ++k) {
			if (i > mid) {
				a[k] = aux[j++];
			} else if (j > high) {
				a[k] = aux[i++];
			} else if (is_less(aux[j], aux[i])) {
				a[k] = aux[j++];
			} else {
				a[k] = aux[i++];
			}
		}
	}

	static void sort(int a[], int low, int high, int aux[]) {
		if (high <= low) {
			return;
		}

		int mid = low + (high - low) / 2;
		sort(a, low, mid, aux);
		sort(a, mid + 1, high, aux);
		merge(a, low, mid, high, aux);
	}

	static void sort(int a[], int a_len) {
		int* aux = new int[a_len];
		sort(a, 0, a_len - 1, aux);

		delete[] aux;
	}

	static void sort_from_bottom_to_up(int a[], int a_len) {
		int* aux = new int[a_len];
		// 进行 lg(a_len) 次两两归并
		for (int size = 1; size < a_len; size += size) {
			for (int low = 0; low < a_len - size; low += size + size) {
				// low: 子数组索引
				merge(a, low, low + size - 1, min(low + size + size - 1, a_len - 1), aux);
			}
		}

		delete[] aux;
	}

	static void test() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort(a, 10);
		print_array(a, 10);
	}

	static void test_sort_from_bottom_to_up() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort_from_bottom_to_up(a, 10);
		print_array(a, 10);
	}
};


/* 测试 */
/*
int main() {
	MergeSort::test();
	MergeSort::test_sort_from_bottom_to_up();

	return 0;
} //*/
