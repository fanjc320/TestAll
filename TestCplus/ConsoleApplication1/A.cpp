#include "A.h"
#include <string>
#include <iostream>
#include <time.h>
#include <windows.h>
extern void TestExtern1();

using namespace  std;
void testExtern()
{
	int k = 1;
	int j = 2;

	TestExtern1();

	char a[16];
	size_t i;

	//snprintf
	/*(1) 如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，并给其后添加一个字符串结束符('\0')；
	(2) 如果格式化后的字符串长度 >= size，则只将其中的(size - 1)个字符复制到str中，并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度。*/

	i = snprintf(a, 16, "%012d", 12345);  // 第 1 种情况
	printf("i0 = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 000000012345

	i = snprintf(a, 9, "%012d", 12345);   // 第 2 种情况
	printf("i1 = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 00000001

	i = snprintf(a, 16, "%017d", 12345);   // 第 2 种情况
	printf("i2 = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 00000001

	//i = sprintf_s(a, 12, "%012d", 12345); //崩溃
	i = sprintf_s(a, 13, "%012d", 12345);
	printf("i3 = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 000000012345

	i = sprintf_s(a, 16, "%012d", 12345);
	printf("i4 = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 000000012345

	DWORD t0 = GetTickCount();
	for (int i = 0; i < 100000; i++)
	{
		char b[4096];
		snprintf(b, 4096, "%d", i);
	}
	DWORD t1 = GetTickCount();
	printf("time1 :%d ", t1 - t0);

	for (int i = 0; i < 100000; i++)
	{
		char b[40];
		snprintf(b, 40, "%d", i);
	}
	DWORD t2 = GetTickCount();
	printf("time2 :%d ", t2 - t1);

	DWORD t3 = GetTickCount();
	for (int i = 0; i < 100000; i++)
	{
		char b[4096];
		sprintf_s(b, 4096, "%d", i);
	}
	DWORD t4 = GetTickCount();
	printf("time1 :%d ", t4 - t3);

	for (int i = 0; i < 100000; i++)
	{
		char b[40];
		sprintf_s(b, 40, "%d", i);
	}
	DWORD t5 = GetTickCount();
	printf("time2 :%d ", t5 - t4);
}
