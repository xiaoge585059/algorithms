
#include <iostream>
#include "tools.h"
#include "my_random.h"
using namespace std;

class QuickSort {
private:
	static bool is_less(int x, int y) {
		return x < y;
	}

	static int compare_to(int x, int y) {
		if (x < y) {
			return -1;
		} else if (x == y) {
			return 0;
		} else {
			return 1;
		}
	}

	static void exchange(int a[], int i, int j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	static int partition(int a[], int low, int high) {
		// �������з�Ϊ a[low..i - 1], a[i], a[i + 1..high]
		int i = low, j = high + 1;  // ����ɨ��ָ��
		int v = a[low];  // �з�Ԫ��
		while (true) {
			// ɨ�����ң����ɨ���Ƿ����������Ԫ��
			while (is_less(a[++i], v)) {
				if (i == high) break;
			}
			while (is_less(v, a[--j])) {
				if (j == low) break;
			}
			if (i >= j) break;
			exchange(a, i, j);
		}
		exchange(a, low, j);  // �� v = a[j] ������ȷ��λ��
		return j;  // a[low..j - 1] <= a[j] <= a[j + 1..hi] ���
	}

	static void sort(int a[], int low, int high) {
		if (high <= low) return;

		int j = partition(a, low, high);  // �з�
		sort(a, low, j - 1);  // ����벿�� a[low..j - 1] ����
		sort(a, j + 1, high);  // ���Ұ벿�� a[j + 1..high] ����
	}

	static void sort_quick3way(int a[], int low, int high) {
		if (high < low) return;

		int less_to = low, i = low + 1, greater_to = high;
		int v = a[low];
		while (i <= greater_to) {
			int cmp = compare_to(a[i], v);
			if (cmp < 0) {
				exchange(a, less_to++, i++);
			} else if (cmp > 0) {
				exchange(a, i, greater_to--);
			} else {
				i += 1;
			}
		}  // ���� a[low..less_to - 1] < v = a[less_to..greater_to] < a[greater_to + 1..high] ����

		sort(a, low, less_to - 1);
		sort(a, greater_to + 1, high);
	}

public:
	static void sort(int a[], int a_len) {
		shuffle(a, a_len);  // ���������
		sort(a, 0, a_len - 1);
	}

	/* �����зֵĿ������� */
	static void sort_quick3way(int a[], int a_len) {
		sort_quick3way(a, 0, a_len - 1);
	}
	
	static void test() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort(a, 10);
		print_array(a, 10);
	}

	static void test_quick3way() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort_quick3way(a, 10);
		print_array(a, 10);
	}
};


/* ���� */
/*
int main() {
	QuickSort::test();
	QuickSort::test_quick3way();

	return 0;
} //*/
