// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <windows.h>
#include <tchar.h>
using namespace std;

int main()
{
	//64位过大，赋值给32位，会被截断
	unsigned long long tick = 50LL * 24L * 3600L * 1000L;
	unsigned long long tick1 = 50 * 24 * 3600 * 1000;
	unsigned int begin = tick;
	tick = tick + 10 * 60 * 1000;
	unsigned int s = (tick - begin) / 1000;
	cout << begin <<" "<< s << endl;


	int* p = new int;
	delete p;
	cout << "p: " << p << endl;

	float testf = 0.51f;
	float testf1 = 0.51f;
	cout << "floatf " << (unsigned int)testf << testf-testf1<<" "<<bool(testf==testf1)<<endl;

	unordered_map<int, int> testu;
	for (int i=1;i<100;i++)
	{
		testu[i] = 100 + i;
	}
	string t1 = "你好";
	//MessageBox(NULL, _T(t1.c_str()), _T("哈哈"), MB_OKCANCEL | MB_ICONERROR);
	MessageBox(NULL, _T("好帅"), _T("哈哈"), MB_OKCANCEL | MB_ICONERROR);
	MessageBox(NULL, _T("好帅"), _T("哈哈"), MB_OKCANCEL | MB_ICONERROR);

	getchar();
    return 0;
}

