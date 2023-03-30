#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>

using namespace std;

class check_x
{
public:
	check_x(long long x) : x_(x) {}
	bool operator()(const std::pair<long long, long long>& v) const
	{
		return v.first >= x_;
	}
private:
	long long x_;
};

class Reader
{
public:
	Reader(long long l, string fileName, map<long long, long long>& um)
	{
		int length, value;
		std::ifstream infile(fileName);
		while (infile >> length >> value)
		{
			if (length <= l && value != 0)
				um[length] = value;
		}
		infile.close();
	}
};

void Run(long long l, map<long long, long long> &um, long long s, long long &maxS)
{
	auto it = std::find_if(um.begin(), um.end(), check_x(l));
	map <long long, long long> m;
	int res = 0;
	for (const auto& el : um)
	{
		if (it == um.end())
		{
			it = --it;
		}
		if (el.first <= it->first)
			res = s + el.second;
		if (l >= el.first)
		{
			m[l - el.first] = res;
			maxS = (maxS < res) ? res : maxS;
		}
	}
	if (!m.empty())
		for (const auto& el : m)
			Run(el.first, um, el.second, maxS);
}

int main()
{
	string fileName = "data.txt";
	map<long long, long long> um;
	long long l = 1000;
	Reader(l, fileName, um);

	for (const auto& el : um)
	{
		cerr << el.first << " " << el.second << "\n";
	}
	long long maxS = 0;
	Run(l, um, 0, maxS);
	cerr << "maxS = " << maxS << endl;

	return 0;
}