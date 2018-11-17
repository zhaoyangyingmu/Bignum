#pragma once
#include <iostream>
#include "Bignum.h"
#include "Util.h"
using namespace std;

class Operator
{
	char op;
public:
	Operator(char ch) : op(ch) {};
	~Operator();
	const Bignum operate(const Bignum& b1 , const Bignum& b2);
	friend istream& operator>>(istream& is , Operator& optr);
	friend ostream& operator<<(ostream& os, Operator& optr);
	friend string& operator>>(string& line , Operator& optr);
	char getChar()const {
		return op;
	}
};

