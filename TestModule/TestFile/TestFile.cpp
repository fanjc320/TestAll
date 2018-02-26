// TestFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream> 
#include <iostream>
using namespace std;
int main()
{
	ofstream out("out.txt", ios::app);
	if (out.is_open())
	{
		out << "This is a line.\n";
		out << "This is another line.\n";
		out.close();
	}

	getchar();
    return 0;
}

