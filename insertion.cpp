
#include <iostream>
#include "tools.h"
using namespace std;

class Insertion {
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
		for (int i = 1; i < a_len; ++i) {
			for (int j = i; j > 0 && is_less(a[j], a[j - 1]); --j) {
				exchange(a, j, j - 1);
			}
		}
	}

	static void test() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort(a, 10);
		print_array(a, 10);
	}

};


/* ≤‚ ‘ */
/*
int main() {
	Insertion::test();

	return 0;
} //*/
