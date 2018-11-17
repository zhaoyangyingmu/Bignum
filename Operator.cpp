#include "stdafx.h"
#include "Operator.h"

Operator::~Operator()
{
}

const Bignum Operator::operate(const Bignum& b1, const Bignum& b2) 
{
	switch (op) {
	case '+':
		return b1 + b2;
	case '-':
		return b1 - b2;
	case '*':
		return b1 * b2;
	case '/':
		return b1 / b2;
	default:
		return b1 + b2;
	}
}

istream& operator>>(istream& is, Operator& optr)
{
	string opStr;
	is >> opStr;
	optr = Operator(opStr[0]);
	return is;
}

ostream& operator<<(ostream& os, Operator& optr) 
{
	os << optr.op;
	return os;
}

string& operator>>(string& line, Operator& optr)
{
	line = Util::trim(line);
	if (line.size() == 0)
	{
		optr = Operator('?');
		return line;
	}
	optr = Operator(line[0]);
	line = line.substr(1);
	line = Util::trim(line);
	return line;
}