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
		// 例如 9123456789 -> 9 | 123456789
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
	// 长度相等，从头比到尾巴
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
		cout << "出现严重错误，比较不可比较的数字！" << endl;
		return false;
	}
	if (left.sign > right.sign) {
		return true;
	}

	if (left.sign < right.sign) {
		return false;
	}

	// 符号相等的情况
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
	// 处理 bigMag.size() == smallMag.size();
	// 和 bigMag.size() - smallMag.size() == 1;
	// 适用于 bigMag[0] < smallMag[0] && bigMag.size() - smallMag.size() == 1; 10^9



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
		int addNum = rightMag.size(); // 内部元素相加次数
		auto rightIr = rightMag.rbegin();
		auto leftIr = leftMag.rbegin();
		long leftNum = 0; // 需要进位的元素
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
		int addNum = rightMag.size(); // 内部元素相加次数
		auto rightIr = rightMag.rbegin();
		auto leftIr = leftMag.rbegin();
		long leftNum = 0; // 需要进位的元素
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
	// 默认大数 减去 小的数
	list<int> result;
	if (gt(smallMag,bigMag))
	{
		cout << "错误调用operator-: 小数减去大数" << endl;
		return result;
	}

	if (!gt(bigMag, smallMag))
	{
		cout << "错误调用operator-: 两个数相等了" << endl;
		return result; // size == 0;
	}

	// 分成两种情况： 第一种，size更大，第二种，size相等
	if (bigMag.size() > smallMag.size())
	{
		long loan = 0;//向之前的一位借贷
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
		auto resultIr = result.begin(); // 去掉0；
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
	{ // size 相等
		long loan = 0;//向之前的一位借贷
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
		auto resultIr = result.begin(); // 去掉0；
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
	int numOfSize = 0; // 大小，例如 9 0000 0000 0 的numOfSize == 1;
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
	//约定错误码： sign = -2;
	//假定给的字符串两边没有空白， 并且+、-没有在数字中间

	//第一步，确定符号和有效数字的位数
	if (val.size() == 0) {
		sign = -2;
		cout << "length  ==  0 . " << endl;
		return;
	}


	int index = 0, numOfDigits;
	unsigned int pos1 = val.find_first_of('+');
	unsigned int pos2 = val.find_last_of('-');
	if (pos2 != string::npos) {//找到了 -
		if (pos2 != 0) {
			sign = -2; // 找到但是不在第一位
			cout << "Wrong format. " << endl;
			return;
		}
		sign = -1; //负数
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
	// 下面的情况都是有数字的情况。
	// 去掉开头的00000
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
	// 计算需要的bit位数，然后确定需要多少个字节
	int numOfBits = (numOfDigits * (bitsPerDigit / 1024 + 1));
	int numOfWords = (numOfBits + 31) / 32;
	// 分成多个组，装入vector中

	int firstGroupLength = numOfDigits % digitsPerInt;
	if (firstGroupLength == 0) {
		firstGroupLength = digitsPerInt;
	}
	string group = val.substr(index, firstGroupLength);//每一组对应的字符串
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
		// 符号相等，就是正常的减法
		//确定符号
		int sign = 0;
		list<int> result;
		if (left > right) {
			sign = 1;
			if (left.sign == -1) { // 负数 - 负数
				return Bignum(right.mag - left.mag , sign);
			}
			else
			{ // 正数 - 正数
				return Bignum(left.mag - right.mag , sign);
			}			
		} 
		else if (right > left) {
			sign = -1;
			if (left.sign == -1) 
			{ // 负数 - 负数 < 0
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
		cout << "错误： 除零操作！" << endl;
		return Bignum(result , 0);
	}

	if (right.sign == -2 || left.sign == -2)
	{
		cout << "输入错误的数字" << endl;
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
		// 应该是没有出错。
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