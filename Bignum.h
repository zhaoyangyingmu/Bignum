#pragma once
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <fstream>
#include "Util.h"
using namespace std;
const vector<int> splitDec(const long long& num);
const int divideBasic(const list<int>& bigMag, const list<int>&smallMag, int testResult, int level);
const list<int> operator*(const list<int>& leftMag, int num);
ostream& operator<<(ostream& os, const list<int> lst);

class Bignum
{
	int sign;
	list<int> mag; // ʹ�ô�˷��洢��
	void init(const string& val);
	static const int digitsPerInt = 9;// ÿ��int�洢9������
	static const int maxPerInt = 1000000000 - 1;// 10 ��10 �η� - 1 �� ���Դ�9��9��
	static const int bitsPerDigit = 1624; // ÿ��������Ҫ���ٸ�bitλ��Ϊ�˼��㷽�� x1024
	// ʵ��ʹ��ʱ �� λ��*����1624 / 1024�� + 1�� = ʵ������Ķ�����λ��
public:
	Bignum(const string& val);
	Bignum(const list<int>& mg, int sn) :mag(mg), sign(sn) {};
	~Bignum();
	const string toString() const;
	friend const Bignum
		operator+(const Bignum& left, const Bignum& right);
	friend const Bignum
		operator*(const Bignum& left, const Bignum& right);
	friend const Bignum
		operator/(const Bignum& left, const Bignum& right);
	friend const Bignum
		operator-(const Bignum& left, const Bignum& right);
	friend const bool
		operator>(const Bignum& left, const Bignum& right);
	friend ostream& operator<<(ostream& os, const Bignum& num);
	friend ofstream& operator<<(ofstream& os, const Bignum& num);
	friend istream& operator>>(istream& is, Bignum& num);
	friend string& operator>>(string& line , Bignum& num);
};

