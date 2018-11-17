#include "stdafx.h"
#include "Util.h"


Util::Util()
{
}


Util::~Util()
{
}

vector<string> Util::split(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//�ҵ��ַ������׸������ڷָ�������ĸ��
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

string Util::trim(string &s)
{
	// remain to be tested
	if (s.empty())
	{
		return s;
	}
	while (true) {
		if (s.empty())
		{
			return s;
		}
		unsigned int pos = 0;
		if ((pos = s.find_first_not_of(" ")) != 0) {
			s.erase(0, pos);
			continue;
		}
		if ((pos = (s.find_last_not_of(" ") + 1)) != s.size()) {
			s.erase(pos);
			continue;
		}
		if ((pos = s.find_first_not_of("\t")) != 0) {
			s.erase(0, pos);
			continue;
		}
		if ((pos = (s.find_last_not_of("\t") + 1)) != s.size()) {
			s.erase(pos);
			continue;
		}
		if ((pos = s.find_first_not_of("\r")) != 0) {
			s.erase(0, pos);
			continue;
		}
		if ((pos = (s.find_last_not_of("\r") + 1)) != s.size()) {
			s.erase(pos);
			continue;
		}
		if ((pos = s.find_first_not_of("\n")) != 0) {
			s.erase(0, pos);
			continue;
		}
		if ((pos = (s.find_last_not_of("\n") + 1)) != s.size()) {
			s.erase(pos);
			continue;
		}
		break;
	}
	return s;
}
