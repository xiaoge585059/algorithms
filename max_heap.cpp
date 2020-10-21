
#include <iostream>
#include "tools.h"
using namespace std;

class MaxHeap {
private:
	/* ���ڶѵ���ȫ������ */
	int* pq;  // priority queue ���ȶ���Ԫ������
	int max_index; // �����������
	int N;  // ��ǰ�ѵ����һ��Ԫ������

	bool is_less(int i, int j) {
		return pq[i] < pq[j];
	}

	void exchange(int i, int j) {
		int temp = this->pq[i];
		this->pq[i] = this->pq[j];
		this->pq[j] = temp;
	}

	/* �������ϵĶ�����(�ϸ�) */
	void swim(int k) {
		while (k > 1 && is_less(k / 2, k)) {
			exchange(k / 2, k);
			k = k / 2;
		}
	}

	/* �������µĶ�����(�³�) */
	void sink(int k) {
		while (2 * k <= this->N) {
			int j = 2 * k;
			if (j < this->N && is_less(j, j + 1)) {  // �Ƚ������ӽڵ��С
				j += 1;
			}

			if (!is_less(k, j)) break;  // ���ڵ���ڵ����ӽڵ㣬������ָ�

			exchange(k, j);
			k = j;
		}
	}

public:
	MaxHeap(int max_index) {
		this->max_index = max_index;
		int pq_size = max_index + 1;
		this->pq = new int[pq_size];
		this->N = 0;
	}

	~MaxHeap() {
		delete[] this->pq;
	}

	bool is_empty() {
		return this->N == 0;
	}

	int size() {
		return this->N;
	}

	void insert(int v) {
		pq[++this->N] = v;
		swim(this->N);
	}

	int del_max() {
		int max_key = pq[1];  // �Ӹ��ڵ�õ����Ԫ��
		exchange(1, this->N--);  // ��������һ��Ԫ�ؽ���
		sink(1);  // �ָ��ѵ�������
		return max_key;
	}
};

void test_MaxHeap() {
	int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
	MaxHeap mp(11);
	for (int i = 0; i < 10; ++i) {
		mp.insert(a[i]);
	}
	for (int i = 0; i < 10; ++i) {
		cout << mp.del_max() << endl;
	}
}

class HeapSort {
private:
	/* ���������� 0 ��ʼ���Ѵ� 1 ��ʼ */
	static bool is_less(int a[], int i, int j) {
		return a[i - 1] < a[j - 1];
	}

	static void exchange(int a[], int i, int j) {
		int temp = a[i - 1];
		a[i - 1] = a[j - 1];
		a[j - 1] = temp;
	}

	/* �������µĶ�����(�³�) */
	static void sink(int a[], int k, int N) {
		while (2 * k <= N) {
			int j = 2 * k;
			if (j < N && is_less(a, j, j + 1)) {  // �Ƚ������ӽڵ��С
				j += 1;
			}

			if (!is_less(a, k, j)) break;  // ���ڵ���ڵ����ӽڵ㣬������ָ�

			exchange(a, k, j);
			k = j;
		}
	}

public:
	static void sort(int a[], int a_len) {
		int N = a_len;
		for (int k = N / 2; k >= 1; --k) {
			sink(a, k, N);
		}
		
		while (N > 1) {
			exchange(a, 1, N--);
			sink(a, 1, N);
		}
	}

	static void test() {
		int a[10] = { 3, 0, 1, 8, 9, 2, 4, 5, 7, 6 };
		sort(a, 10);
		print_array(a, 10);
	}

};


/* ���� */
/*
int main() {
	// test_MaxHeap();
	HeapSort::test();

	return 0;
} //*/

