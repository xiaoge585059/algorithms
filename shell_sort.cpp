
#include <iostream>
#include "tools.h"
using namespace std;

class ShellSort {
private:
	static bool is_less(int x, int y) {
		return x < y;
	}

	static void exchange(int a[], int i, int j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

public:
	static void sort(int a[], int a_len) {
		int h = 1;
		while (h < a_len / 3) {
			h = 3 * h + 1;  // 1, 4, 13, 40, 121, 364, 1093, ...
		}

		while (h >= 1) {
			// 将数组变为 h 有序
			for (int i = h; i < a_len; ++i) {
				// 将 a[i] 插入到 a[i - h], a[i - 2 * h], a[i - 3 * h] ... 之中
				for (int j = i; j >= h && is_less(a[j], a[j - h]); j -= h) {
					exchange(a, j, j - h);
				}
			}
			h = h / 3;
		}
	}

	static void test() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort(a, 10);
		print_array(a, 10);
	}

};


/* 测试 */
/*
int main() {
	ShellSort::test();

	return 0;
} //*/
