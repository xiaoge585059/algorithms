#pragma once

#include <iostream>
using namespace std;

template <typename T>
void print_array(T a[], int a_len, string prompt = "") {
	if (prompt != "") {
		cout << prompt << endl;
	}
	for (int i = 0; i != a_len; ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;
}

template <typename T>
bool is_sorted(T a[], int a_len) {
	for (int i = 1; i < a_len; ++i) {
		if (a[i - 1] > a[i]) {
			return false;
		}
	}
	return true;
}
