// TestCplus.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <set>
#include <unordered_set>
#include <iostream>
#include <map>
using namespace std;
int main()
{
	unordered_set<int> ss;
	ss.erase(1);
    
	std::multimap<char, int> mymm;

	mymm.insert(std::pair<char, int>('a', 10));
	mymm.insert(std::pair<char, int>('b', 20));
	mymm.insert(std::pair<char, int>('b', 30));
	mymm.insert(std::pair<char, int>('b', 40));
	mymm.insert(std::pair<char, int>('c', 50));
	mymm.insert(std::pair<char, int>('c', 60));
	mymm.insert(std::pair<char, int>('d', 60));

	for (auto i:mymm)
	{
		cout <<"key  " << i.first<< ' ' << i.second<<endl;
	}

	int i;
	cin >> i;

	return 0;
}

