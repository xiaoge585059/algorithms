  
#include <iostream>
#include "tools.h"
#include "my_random.h"
using namespace std;

/**
 * @brief 求最大公约数 \n
 * 用欧几里得算法求取两个数的最大公约数（gcd, greatest common divisor）
 * 计算两个非负整数 p 和 q 的最大公约数：
 * 若 p 是 0，则最大公约数为 q。
 * 否则，将 p 除以 q 得到余数 r，p 和 q 的最大公约数即为 q 和 r 的最大公约数。
 *
 * @param p: int, 两个数中的一个
 * @param q: int, 两个数中的另一个
 * @return: int, 求得的最大公约数
 */
int gcd(int p, int q) {
	if (q == 0) return p;
	int r = p % q;
	return gcd(q, r);
}

/**
 * @brief 二分查找 \n
 * 以二分查找法从有序数组中快速查找值
 *
 * @param key: int, 要查找的值
 * @param a: int[], 有序数组，从这个数组中查找 key
 * @parma a_len: int, 有序数组 a 的长度
 * @return: int, key 在有序数组 a 中的索引，key 不在数组中则返回 -1
 */
int binary_search(int key, int a[], int a_len) {
	int lo = 0;
	int hi = a_len - 1;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		if (key < a[mid]) {
			hi = mid - 1;
		} else if (key > a[mid]) {
			lo = mid + 1;
		} else {
			return mid;
		}
	}

	return -1;
}

/**
 * 递归实现二分查找法
 */
int binary_search_recursion(int key, int a[], int lo, int hi) {
	if (lo > hi) return -1;

	int mid = lo + (hi - lo) / 2;
	if (key < a[mid]) return binary_search_recursion(key, a, lo, mid - 1);
	else if (key > a[mid]) return binary_search_recursion(key, a, mid + 1, hi);
	else return mid;
}

int binary_search_recursion(int key, int a[], int a_len) {
	return binary_search_recursion(key, a, 0, a_len - 1);
}

/* 测试 my_random */
void test_random() {
	set_random_seed();

	cout << "random:" << endl;
	for (int i = 0; i < 50; ++i) {
		cout << random() << " ";
	}
	cout << endl;

	cout << "uniform(1.5, 6.6):" << endl;
	for (int i = 0; i < 50; ++i) {
		cout << uniform(1.5, 6.6) << " ";
	}
	cout << endl;

	cout << "uniform(100):" << endl;
	for (int i = 0; i < 50; ++i) {
		cout << uniform(100) << " ";
	}
	cout << endl;

	cout << "uniform(25, 75):" << endl;
	for (int i = 0; i < 50; ++i) {
		cout << uniform(25, 75) << " ";
	}
	cout << endl;

	cout << "discrete(new double[3]{ 0.1, 0.7, 0.2 }, 3):" << endl;
	double d[3] = { 0.1, 0.7, 0.2 };
	for (int i = 0; i < 50; ++i) {
		cout << discrete(d, 3) << " ";
	}
	cout << endl;

	cout << "shuffle(a, 10)" << endl;
	double a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 0; i < 3; ++i) {
		shuffle(a, 10);
		print_array(a, 10);
	}
}

/**
 * 测试
 */
int main() {
	// cout << gcd(123, 9) << endl;  // 测试 gcd 函数
	// 测试 binary_search 和 binary_search_recursion 函数

	const int a_len = 10;
	int a[a_len] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// cout << binary_search(5, a, a_len) << endl << binary_search(11, a, a_len) << endl;
	// cout << binary_search_recursion(5, a, a_len) << endl;
	// cout << binary_search_recursion(11, a, a_len) << endl;

	// test_random();  // 测试 my_random

	return 0;
}
