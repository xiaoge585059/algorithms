
#include <iostream>
#include <stack>
using namespace std;

/* 返回操作符的优先级 */
int priority(char oper) {
	if (oper == '+' || oper == '-') {
		return 0;
	}
	if (oper == '*' || oper == '/') {
		return 1;
	}
	if (oper == '^') {
		return 2;
	}
	return -1;
}

/* 将中序表达式转为后序表达式 */
string infix_to_postfix(string express) {
	stack<char> opers;
	string result = "";

	int exp_len = express.length();
	for (int i = 0; i < exp_len; ++i) {
		if (express[i] == ' ') {  // 忽略空格
			continue;
		}

		char c = express[i];
		if (isdigit(c)) {
			result += c;
		} else if (c == '(') {
			opers.push(c);
		} else if (c == ')') {
			while (!opers.empty() && opers.top() != '(') {
				result += opers.top();
				opers.pop();
			}
			opers.pop();
		} else {
			while (!opers.empty() && priority(c) <= priority(opers.top())) {
				result += opers.top();
				opers.pop();
			}
			opers.push(c);
		}
	}

	while (!opers.empty()) {
		result += opers.top();
		opers.pop();
	}

	return result;
}

/* 计算后序表达式的值 */
double evaluate_postfix(string express) {
	stack<double> nums;
	double p1 = 0, p2 = 0;
	bool first = true;
	int exp_len = express.length();
	for (int i = 0; i < exp_len; ++i) {
		char c = express[i];
		if (isdigit(c)) {
			nums.push(c - '0');
		} else {
			p2 = nums.top();
			nums.pop();
			p1 = nums.top();
			nums.pop();
			if (c == '+') {
				nums.push(p1 + p2);
			} else if (c == '-') {
				nums.push(p1 - p2);
			} else if (c == '*') {
				nums.push(p1 * p2);
			} else if (c == '/') {
				nums.push(p1 / p2);
			}
		}
	}

	return nums.top();
}

/* 测试中序表达式转后序表达式，以及计算后序表达式的值 */
void test_postfix() {
	string express = "((1 + 2) * ((3 - 4) * (5 - 6)))";
	cout << express << endl;
	string result = infix_to_postfix(express);
	cout << result << endl;
	double evaluate_result = evaluate_postfix(result);
	cout << evaluate_result << endl;
}


/* 测试 */
/*
int main() {
	test_postfix();

	return 0;
} //*/
