// Main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Bignum.h"
#include "Operator.h"
#include <iostream>
using namespace std;

void test() {
	list<int> l1, l2;
	l1.push_back(789);
	l2.push_back(123456);

	cout << "divideBasic(l1, l2, 999999999, 8): " <<  divideBasic(l1, l2, 999999999, 8) << endl;
	Bignum b1("123456789");
	Bignum b2("123456");
	cout << "(b1 / b2).toString(): " << (b1 / b2).toString() << endl;
	Bignum b3("123456789123456789");
	Bignum b4("123456");
	cout << "(b3 / b4).toString(): " << (b3 / b4).toString() << endl;

	Bignum b5("123456789123456789123456789");
	Bignum b6("123456");
	cout << "(b5 / b6).toString(): " << (b5 / b6).toString() << endl;

	Bignum b7("123456789123456789");
	Bignum b8("987654321987654321");
	Bignum b9("23456789123456789");
	cout << "(b7 * b8 / b9).toString(): " << (b7 * b8 / b9).toString() << endl;
}


int main(int argc, char* args[])
{
	if (argc != 3)
	{
		cout << "Usage: Bignum.exe sample.in sample.out" << endl;
		return 1;
	}
	ifstream fin(args[1]);
	ofstream fout(args[2]);
	
	int num;
	fin >> num;
	string line;
	getline(fin , line);
	// to do;
	for (int i = 0; i < num; i++) {
		getline(fin , line);
		Bignum result("0");
		line = line >> result;
		while (true) {
			Bignum operand1("0");
			Operator optr('+');
			line = line >> optr >> operand1;
			if (optr.getChar() == '?') {
				break;
			}
			result = optr.operate(result , operand1);
		}
		fout << result << endl;
	}
	fout.close();

	while (true) {
		string command;
		cout << "Enter compute to compute, exit to exit: " << endl;
		cin >> command;
		if (command == "compute") {
			cout << "How many operands？" << endl;
			int num = 0;
			cin >> num;
			cout << "Enter your formula: " << endl;
			Bignum result("1"), b2("1");
			Operator op('+');
			cin >> result;
			for (int i = 0; i < num-1; i++) {
				cin >> op >> b2;
				result = op.operate(result , b2);
			}
			cout << "result = " << result << endl;
		}
		else if (command == "exit") {
			break;
		}
		else {
			continue;
		}
	}
    return 0;
}
