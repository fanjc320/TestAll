// mydll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "mydll.h"


// 这是导出变量的一个示例
MYDLL_API int nmydll=10;

// 这是导出函数的一个示例。
MYDLL_API int fnmydll(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 mydll.h
Cmydll::Cmydll()
{
    return;
}

int Cmydll::dllAdd(int plus1, int plus2)
{
	return plus1 + plus2;
}
