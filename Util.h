#pragma once
#include <vector>
#include <string>
using namespace std;

class Util
{
public:
	Util();
	~Util();
	static vector<string> split(const string &s, const string &seperator);
	static string trim(string &s);
};

