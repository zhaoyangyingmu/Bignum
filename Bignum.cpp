#include "stdafx.h"
#include "Bignum.h"

ostream& operator<<(ostream& os, const list<int> lst) {
	os << "list as follows: " << endl;
	for (auto ir = lst.begin(); ir != lst.end(); ir++) {
		os << *ir << " ";
	}
	os << endl;
	return os;
}

const vector<int> splitDec(const long long& num) {
	vector<int> splitResult;
	ostringstream oss;
	oss << num;
	string numStr = oss.str();
	if (numStr.size() > 9)
	{
		// ���� 9123456789 -> 9 | 123456789
		int firstPart = atoi(numStr.substr(0 , numStr.size() - 9).c_str());
		int secondPart = atoi(numStr.substr(numStr.size() - 9).c_str());
		splitResult.push_back(firstPart);
		splitResult.push_back(secondPart);
	}
	else {
		splitResult.push_back(int(num));
	}
	return splitResult;
}

const bool gt(const list<int>& leftMag, const list<int>& rightMag)
{
	if (leftMag.size() > rightMag.size()) {
		return true;
	}
	if (leftMag.size() < rightMag.size()) {
		return false;
	}
	// ������ȣ���ͷ�ȵ�β��
	auto leftIr = leftMag.begin();
	auto rightIr = rightMag.begin();
	while (rightIr != rightMag.end()) {
		if (*leftIr > *rightIr) {
			return true;
		}
		if (*leftIr < *rightIr) {
			return false;
		}
		leftIr++;
		rightIr++;
	}
	return false;
}

const bool operator>(const Bignum& left, const Bignum& right)
{
	if (left.sign == -2 || right.sign == -2)
	{
		cout << "�������ش��󣬱Ƚϲ��ɱȽϵ����֣�" << endl;
		return false;
	}
	if (left.sign > right.sign) {
		return true;
	}

	if (left.sign < right.sign) {
		return false;
	}

	// ������ȵ����
	if (left.sign == 0) { // 0 > 0
		return false;
	}
	if (left.sign == 1) {
		bool result = gt(left.mag, right.mag);
		return result;
	}
	if (left.sign == -1) {
		return gt(left.mag , right.mag);
	}
}

const int divideBasic(const list<int>& bigMag , const list<int>&smallMag, int testResult , int level) 
{
	// first time 999999999 , level 10^8
	// ���� bigMag.size() == smallMag.size();
	// �� bigMag.size() - smallMag.size() == 1;
	// ������ bigMag[0] < smallMag[0] && bigMag.size() - smallMag.size() == 1; 10^9



	int delta = (int)pow(10 , level);
	if (gt(smallMag * testResult, bigMag)) {
		while (gt(smallMag * testResult , bigMag))
		{
			if (testResult >= delta) {
				testResult -= delta;
			}
			else {
				return divideBasic(bigMag, smallMag, testResult, level - 1);
			}
		}
		if (level == 0) {
			return testResult;
		}
		return divideBasic(bigMag , smallMag , testResult , level-1);
	}
	else if (gt(bigMag, smallMag * testResult))
	{
		while (gt(bigMag, smallMag * testResult)) {
			testResult += delta;
		}
		if (level == 0) {
			return testResult - 1;
		}
		return divideBasic(bigMag, smallMag, testResult, level - 1);
	}
	else {
		return testResult;
	}
}

const list<int> operator+(const list<int>& leftMag, const list<int>& rightMag)
{
	list<int> result;

	if (leftMag.size() == 0)
	{
		return rightMag;
	}
	if (rightMag.size() == 0)
	{
		return leftMag;
	}

	if (leftMag.size() > rightMag.size()) {
		int addNum = rightMag.size(); // �ڲ�Ԫ����Ӵ���
		auto rightIr = rightMag.rbegin();
		auto leftIr = leftMag.rbegin();
		long leftNum = 0; // ��Ҫ��λ��Ԫ��
		for (int i = 0; i < addNum; i++) {
			long sum = (long)*rightIr + (long)*leftIr + leftNum;
			rightIr++;
			leftIr++;
			ostringstream oss;
			oss << sum;
			string sumStr = oss.str();
			if (sumStr.size() > 9)
			{
				leftNum = (long)atoi(sumStr.substr(0, sumStr.size() - 9).c_str());
				int val = atoi(sumStr.substr(sumStr.size() - 9).c_str());
				result.push_front(val);
			}
			else {
				result.push_front((int)sum);
				leftNum = 0;
			}
		}
		while (leftNum != 0) {
			if (leftIr != leftMag.rend()) {
				long sum = (long)*leftIr + leftNum;
				leftIr++;

				ostringstream oss;
				oss << sum;
				string sumStr = oss.str();
				if (sumStr.size() > 9)
				{
					leftNum = (long)atoi(sumStr.substr(0, sumStr.size() - 9).c_str());
					int val = atoi(sumStr.substr(sumStr.size() - 9).c_str());
					result.push_front(val);
				}
				else {
					result.push_front((int)sum);
					leftNum = 0;
				}
			}
			else {
				result.push_front(leftNum);
				break;
			}
		}
		while (leftIr != leftMag.rend()) {
			result.push_front(*leftIr);
			leftIr++;
		}
		return result;
	}
	else if (leftMag.size() < rightMag.size())
	{
		return rightMag + leftMag;
	}
	else { // leftMag.size() == rightMag.size()
		int addNum = rightMag.size(); // �ڲ�Ԫ����Ӵ���
		auto rightIr = rightMag.rbegin();
		auto leftIr = leftMag.rbegin();
		long leftNum = 0; // ��Ҫ��λ��Ԫ��
		for (int i = 0; i < addNum; i++) {
			long sum = (long)*rightIr + (long)*leftIr + leftNum;
			rightIr++;
			leftIr++;
			ostringstream oss;
			oss << sum;
			string sumStr = oss.str();
			if (sumStr.size() > 9)
			{
				leftNum = (long)atoi(sumStr.substr(0, sumStr.size() - 9).c_str());
				int val = atoi(sumStr.substr(sumStr.size() - 9).c_str());
				result.push_front(val);
			}
			else {
				result.push_front((int)sum);
				leftNum = 0;
			}
		}
		if (leftNum != 0) {
			result.push_front((int)leftNum);
		}
		return result;

	}
}

const list<int> operator-(const list<int>& bigMag, const list<int>& smallMag) {
	// Ĭ�ϴ��� ��ȥ С����
	list<int> result;
	if (gt(smallMag,bigMag))
	{
		cout << "�������operator-: С����ȥ����" << endl;
		return result;
	}

	if (!gt(bigMag, smallMag))
	{
		cout << "�������operator-: �����������" << endl;
		return result; // size == 0;
	}

	// �ֳ���������� ��һ�֣�size���󣬵ڶ��֣�size���
	if (bigMag.size() > smallMag.size())
	{
		long loan = 0;//��֮ǰ��һλ���
		int subNum = smallMag.size();
		auto bigIr = bigMag.rbegin();
		auto smallIr = smallMag.rbegin();
		for (int i = 0; i < subNum; i++)
		{
			long subResult = (long)*bigIr - (long)*smallIr - loan;
			bigIr++;
			smallIr++;
			if (subResult < 0)
			{
				subResult += 1000000000;
				loan = 1;
			}
			else {
				loan = 0;
			}
			result.push_front((int)subResult);
		}
		while (loan != 0 && (bigIr != bigMag.rend()))
		{
			long subResult = (long)*bigIr - loan;
			bigIr++;
			if (subResult < 0) {
				subResult += 1000000000;
				loan = 1;
			}
			else {
				loan = 0;
			}
			result.push_front((int)subResult);
		}

		while (bigIr != bigMag.rend())
		{
			result.push_front(*bigIr);
			bigIr++;
		}
		auto resultIr = result.begin(); // ȥ��0��
		int popNum = 0;
		while (resultIr != result.end()) {
			if (*resultIr == 0) {
				popNum++;
				resultIr++;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < popNum; i++) {
			result.pop_front();
		}
		return result;
	}
	else
	{ // size ���
		long loan = 0;//��֮ǰ��һλ���
		int subNum = smallMag.size();
		auto bigIr = bigMag.rbegin();
		auto smallIr = smallMag.rbegin();
		for (int i = 0; i < subNum; i++)
		{
			long subResult = (long)*bigIr - (long)*smallIr - loan;
			bigIr++;
			smallIr++;
			if (subResult < 0)
			{
				subResult += 1000000000;
				loan = 1;
			}
			else {
				loan = 0;
			}
			result.push_front((int)subResult);
		}
		auto resultIr = result.begin(); // ȥ��0��
		int popNum = 0;
		while (resultIr != result.end()) {
			if (*resultIr == 0) {
				popNum++;
				resultIr++;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < popNum; i++) {
			result.pop_front();
		}
		return result;
	}
}

const list<int> operator*(const list<int>& leftMag, const list<int>& rightMag) 
{
	list<list<int>> resultRows;
	int numOfSize = 0; // ��С������ 9 0000 0000 0 ��numOfSize == 1;
	for (auto rightIr = rightMag.rbegin(); rightIr != rightMag.rend(); rightIr++) {
		list<int> tmpResult;
		for (int i = 0; i < numOfSize; i++) {
			tmpResult.push_front(0);
		}
		numOfSize++;
		long long leftNum = 0;
		for (auto leftIr = leftMag.rbegin(); leftIr != leftMag.rend(); leftIr++) {
			long long tmpVal = ((long long)(*rightIr)) * ((long long)(*leftIr)) + leftNum;
			vector<int> result = splitDec(tmpVal);
			if (result.size() == 2) {
				leftNum = result[0];
				tmpResult.push_front(result[1]);
			}
			else {
				leftNum = 0;
				tmpResult.push_front(result[0]);
			}
		}
		if (leftNum != 0) {
			tmpResult.push_front(leftNum);
		}
		resultRows.push_front(tmpResult);
	}

	list<int> sum;
	for (auto ir = resultRows.begin() ; ir != resultRows.end(); ir++) 
	{
		sum = sum + *ir;
	}
	return sum;
}

const list<int> operator*(const list<int>& leftMag, int num) {
	list<int> tmp;
	tmp.push_back(num);
	return leftMag * tmp;
}

const list<int> operator/(const list<int>& leftMag, const list<int>& rightMag) {
	list<int> result;
	if (leftMag.size() == rightMag.size())
	{
		int divideResult = divideBasic(leftMag, rightMag, 999999999, 8);
		if (divideResult == 0) {
			return result;
		}
		result.push_back(divideResult);
		return result;
	}
	else if (leftMag.size() < rightMag.size())
	{
		return result;
	}
	else
	{ // leftMag.size() > rightMag.size()
		auto leftIr = leftMag.begin();
		list<int> head;
		while (leftIr != leftMag.end()) {
			int headSize = head.size();
			for (int i = 0; i < (rightMag.size() - headSize); i++) {
				head.push_back(*leftIr);
				leftIr++;
			}
			int partResult = divideBasic(head , rightMag, 999999999, 8);
			if (partResult == 0) {
				if (leftIr == leftMag.end()) {
					if (result.size() != 0) {
						result.push_back(0);
					}
					return result;
				}
				head.push_back(*leftIr);
				leftIr++;
				partResult = divideBasic(head, rightMag, 999999999, 8);
				result.push_back(partResult);
				head = head - (rightMag * partResult);
			}
			else {
				head = head - (rightMag * partResult);
				result.push_back(partResult);
			}
		}
		return result;
	}
}

Bignum::Bignum(const string& val)
{
	init(val);
}


Bignum::~Bignum()
{

}

void Bignum::init(const string& val) 
{
	//Լ�������룺 sign = -2;
	//�ٶ������ַ�������û�пհף� ����+��-û���������м�

	//��һ����ȷ�����ź���Ч���ֵ�λ��
	if (val.size() == 0) {
		sign = -2;
		cout << "length  ==  0 . " << endl;
		return;
	}


	int index = 0, numOfDigits;
	unsigned int pos1 = val.find_first_of('+');
	unsigned int pos2 = val.find_last_of('-');
	if (pos2 != string::npos) {//�ҵ��� -
		if (pos2 != 0) {
			sign = -2; // �ҵ����ǲ��ڵ�һλ
			cout << "Wrong format. " << endl;
			return;
		}
		sign = -1; //����
		index++;
		if (val.size() == 1) {
			cout << "no digits" << endl;
			return;
		}
	}
	else if (pos1 != string::npos) {
		if (pos1 != 0) {
			sign = -2;
			cout << "Wrong format. " << endl;
			return;
		}
		sign = 1;
		index++;
		if (val.size() == 1) {
			cout << "no digits" << endl;
			return;
		}
	}
	else {
		sign = 1;
	}
	// �����������������ֵ������
	// ȥ����ͷ��00000
	for (; index < val.size(); index++) {
		if (val[index] != '0') {
			break;
		}
	}
	if (index == val.size()) {
		sign = 0;
		return;
	}

	numOfDigits = val.size() - index;
	// ������Ҫ��bitλ����Ȼ��ȷ����Ҫ���ٸ��ֽ�
	int numOfBits = (numOfDigits * (bitsPerDigit / 1024 + 1));
	int numOfWords = (numOfBits + 31) / 32;
	// �ֳɶ���飬װ��vector��

	int firstGroupLength = numOfDigits % digitsPerInt;
	if (firstGroupLength == 0) {
		firstGroupLength = digitsPerInt;
	}
	string group = val.substr(index, firstGroupLength);//ÿһ���Ӧ���ַ���
	index += firstGroupLength;
	int groupValue = atoi(group.c_str());
	if (groupValue < 0) 
	{
		cout << "Illegal Digits! " << endl;
		sign = -2;
		return;
	}
	mag.push_back(groupValue);
	while (index < val.size()) {
		group = val.substr(index, digitsPerInt);
		groupValue = atoi(group.c_str());
		if (groupValue < 0) { 
			cout << "Illegal Digits! " << endl;
			sign = -2;
			return;
		}
		mag.push_back(groupValue);
		index += digitsPerInt;
	}
}

const string Bignum::toString() const 
{
	ostringstream oss;
	if (sign == -2) {
		return "no such number.";
	}
	if (sign == 0) {
		return "0";
	}

	if (sign == -1) {
		oss << "-";
	}
	for (auto ir = mag.begin(); ir != mag.end();ir++) {
		
		if (*ir == 0) {
			if (ir == mag.begin()) {
				continue;
			}
			oss << "000000000";
		}
		else {
			if (ir == mag.begin()) {
				oss << *ir;
				continue;
			}
			ostringstream tmp;
			tmp << *ir;
			string tmpStr = tmp.str();
			if (tmpStr.size() < 9) {
				for (int i = 0; i < (9 - tmpStr.size()); i++) {
					tmpStr = "0" + tmpStr;
				}
			}
			oss << tmpStr;
		}
	}
	return oss.str();

}

const Bignum operator+(const Bignum& left, const Bignum& right)
{
	if (left.sign == 0) {
		return right;
	}
	if (right.sign == 0) {
		return left;
	}
	
	if (left.sign == -2) {
		cout << "left number incorrect!" << endl;
		return right;
	}
	if (right.sign == -2) {
		cout << "right number incorrect!" << endl;
		return left;
	}

	if (left.sign == right.sign) {
		return Bignum(left.mag+right.mag , left.sign);
	}
	else {
		if (gt(left.mag, right.mag)) 
		{

			return Bignum(left.mag - right.mag , left.sign);
		}
		else if (gt(left.mag, right.mag))
		{
			return Bignum(right.mag - left.mag , right.sign);
		}
		else
		{
			list<int> empty;
			return Bignum(empty , 0);
		}
	}
}

const Bignum operator-(const Bignum& left, const Bignum& right) 
{
	if (left.sign == 0) {
		return right;
	}
	if (right.sign == 0) {
		return left;
	}

	if (left.sign == -2) {
		cout << "left number incorrect!" << endl;
		return right;
	}
	if (right.sign == -2) {
		cout << "right number incorrect!" << endl;
		return left;
	}

	if (left.sign != right.sign) {
		if (left.sign == 1) {
			Bignum newRight = right;
			newRight.sign = 1;
			return left + newRight;
		}
		else {
			Bignum newRight = right;
			newRight.sign = -1;
			return left + newRight;
		}
	}
	else { 
		// ������ȣ����������ļ���
		//ȷ������
		int sign = 0;
		list<int> result;
		if (left > right) {
			sign = 1;
			if (left.sign == -1) { // ���� - ����
				return Bignum(right.mag - left.mag , sign);
			}
			else
			{ // ���� - ����
				return Bignum(left.mag - right.mag , sign);
			}			
		} 
		else if (right > left) {
			sign = -1;
			if (left.sign == -1) 
			{ // ���� - ���� < 0
				return Bignum(left.mag - right.mag , sign);
			}
			else
			{
				return Bignum(right.mag - left.mag , sign);
			}
		}
		else {
			sign = 0;
			return Bignum(result, sign);
		}

	}
}

const Bignum operator*(const Bignum& left, const Bignum& right) 
{
	int sign = 0;
	if (left.sign == 0 || right.sign == 0) 
	{
		list<int> empty;
		return Bignum(empty , 0);
	}
	if (left.sign == -2 || right.sign == -2)
	{
		list<int> empty;
		return Bignum(empty, -2);
	}

	if (left.sign == right.sign) 
	{
		return Bignum(left.mag * right.mag , 1);
	}
	else 
	{
		return Bignum(left.mag * right.mag , -1);
	}
}

const Bignum operator/(const Bignum& left, const Bignum& right) 
{
	list<int> result;
	if (left.sign == 0)
	{
		return Bignum(result , 0);
	}
	if (right.sign == 0)
	{
		cout << "���� ���������" << endl;
		return Bignum(result , 0);
	}

	if (right.sign == -2 || left.sign == -2)
	{
		cout << "������������" << endl;
		return Bignum(result , -2);
	}

	if (right.sign != left.sign)
	{
		result = left.mag / right.mag;
		if (result.size() == 0)
		{
			return Bignum(result , 0);
		}
		return Bignum( result, -1);
	}
	else
	{
		result = left.mag / right.mag;
		if (result.size() == 0)
		{
			return Bignum(result, 0);
		}
		return Bignum(result, 1);
	}
}

ostream& operator<<(ostream& os, const Bignum& num) {
	os << num.toString();
	return os;
}

ofstream& operator<<(ofstream& os, const Bignum& num) {
	os << num.toString().c_str();
	return os;
}

istream& operator>>(istream& is, Bignum& num) 
{
	string numStr;
	cin >> numStr;
	num = Bignum(numStr);
	return is;
}

string& operator>>(string& line, Bignum& num)
{
	line = Util::trim(line);
	if (line.size() == 0)
	{
		list<int> result;
		num = Bignum(result , -2);
		return line;
	}
	unsigned int index = line.find_first_of(' ');
	if (index == string::npos) {
		// Ӧ����û�г���
		num = Bignum(line);
		line = "";
		return line;
	}
	else {
		num = Bignum(line.substr(0 , index));
		line = line.substr(index + 1);
		return line;
	}
}