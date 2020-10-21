
#include <iostream>
#include "tools.h"
using namespace std;

class MaxHeap {
private:
	/* 基于堆的完全二叉树 */
	int* pq;  // priority queue 优先队列元素容器
	int max_index; // 容器最大索引
	int N;  // 当前堆的最后一个元素索引

	bool is_less(int i, int j) {
		return pq[i] < pq[j];
	}

	void exchange(int i, int j) {
		int temp = this->pq[i];
		this->pq[i] = this->pq[j];
		this->pq[j] = temp;
	}

	/* 由下至上的堆有序化(上浮) */
	void swim(int k) {
		while (k > 1 && is_less(k / 2, k)) {
			exchange(k / 2, k);
			k = k / 2;
		}
	}

	/* 由上至下的堆有序化(下沉) */
	void sink(int k) {
		while (2 * k <= this->N) {
			int j = 2 * k;
			if (j < this->N && is_less(j, j + 1)) {  // 比较两个子节点大小
				j += 1;
			}

			if (!is_less(k, j)) break;  // 父节点大于等于子节点，堆有序恢复

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
		int max_key = pq[1];  // 从根节点得到最大元素
		exchange(1, this->N--);  // 将其和最后一个元素交换
		sink(1);  // 恢复堆的有序性
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
	/* 数组索引从 0 开始，堆从 1 开始 */
	static bool is_less(int a[], int i, int j) {
		return a[i - 1] < a[j - 1];
	}

	static void exchange(int a[], int i, int j) {
		int temp = a[i - 1];
		a[i - 1] = a[j - 1];
		a[j - 1] = temp;
	}

	/* 由上至下的堆有序化(下沉) */
	static void sink(int a[], int k, int N) {
		while (2 * k <= N) {
			int j = 2 * k;
			if (j < N && is_less(a, j, j + 1)) {  // 比较两个子节点大小
				j += 1;
			}

			if (!is_less(a, k, j)) break;  // 父节点大于等于子节点，堆有序恢复

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


/* 测试 */
/*
int main() {
	// test_MaxHeap();
	HeapSort::test();

	return 0;
} //*/

