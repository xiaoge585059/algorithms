  
#include <iostream>
#include "tools.h"
#include "my_random.h"
using namespace std;

/**
 * @brief �����Լ�� \n
 * ��ŷ������㷨��ȡ�����������Լ����gcd, greatest common divisor��
 * ���������Ǹ����� p �� q �����Լ����
 * �� p �� 0�������Լ��Ϊ q��
 * ���򣬽� p ���� q �õ����� r��p �� q �����Լ����Ϊ q �� r �����Լ����
 *
 * @param p: int, �������е�һ��
 * @param q: int, �������е���һ��
 * @return: int, ��õ����Լ��
 */
int gcd(int p, int q) {
	if (q == 0) return p;
	int r = p % q;
	return gcd(q, r);
}

/**
 * @brief ���ֲ��� \n
 * �Զ��ֲ��ҷ������������п��ٲ���ֵ
 *
 * @param key: int, Ҫ���ҵ�ֵ
 * @param a: int[], �������飬����������в��� key
 * @parma a_len: int, �������� a �ĳ���
 * @return: int, key ���������� a �е�������key �����������򷵻� -1
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
 * �ݹ�ʵ�ֶ��ֲ��ҷ�
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

/* ���� my_random */
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

/* ɾ�����������е��ظ�Ԫ�� */
int* drop_dulicated_elements(int a[], int a_len) {
	int count = 1;
	for (int i = a_len - 1; i > 0; --i) {
		if (a[i] != a[i - 1]) {
			count++;
		}
	}

	int* a_result = new int[count] { 0 };
	for (int i = a_len - 1; i > 0; --i) {
		if (a[i] != a[i - 1]) {
			a_result[--count] = a[i];
		}
	}

	return a_result;
}

void test_drop_dulicated_elements() {
	int a[20] = { 0, 1, 1, 2, 3, 4, 4, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 8, 9, 9 };
	int* b = drop_dulicated_elements(a, 20);
	print_array(b, 10);

	delete[] b;
}

/**
 * �ж� s1 �Ƿ�Ϊ s2 �Ļػ���λ
 *   ����ַ��� s1 �е��ַ�ѭ���ƶ�����λ��֮���ܹ��õ���һ���ַ��� s2
 *   ��ô s1 �ͱ���Ϊ s2 �Ļػ���λ
 * ����ֵ��
 *   -1: s1 ���� s2 �Ļػ���λ
 *   result = [0, s1.length - 1]: s1 ѭ���ƶ� result λ֮��õ� s2
 */
int circular_rotation(string s1, string s2) {
	// string.find() ����ֵΪ�޷������ͣ���ת���� int ����
	return (s1.length() == s2.length()) && ((int)(s1 + s1).find(s2) >= 0);
}

/* ���� circular_rotation ���� */
void test_circular_rotation() {
	cout << circular_rotation("ACTGACG", "TGACGAC") << endl;
	cout << circular_rotation("ACTGACG", "TGACGA") << endl;
	cout << circular_rotation("ACTGACG", "TGACGTC") << endl;
}


/* ���� */
/*
int main() {
	// cout << gcd(123, 9) << endl;  // ���� gcd ����
	// ���� binary_search �� binary_search_recursion ����

	const int a_len = 10;
	int a[a_len] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// cout << binary_search(5, a, a_len) << endl << binary_search(11, a, a_len) << endl;
	// cout << binary_search_recursion(5, a, a_len) << endl;
	// cout << binary_search_recursion(11, a, a_len) << endl;

	// test_random();  // ���� my_random
	// test_drop_dulicated_elements();
	test_circular_rotation();

	return 0;
} //*/
