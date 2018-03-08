// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<map>
#include <algorithm>
#include <stdarg.h>

using namespace std;
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;
struct s_Key_Job_JobLv_LearnLv {
	uint32 joblv;
	uint16 LearnLv;
	uint32 CateGoryId;
	friend bool operator < (const struct s_Key_Job_JobLv_LearnLv &k1, const struct s_Key_Job_JobLv_LearnLv &k2);
};

inline bool operator < (const struct s_Key_Job_JobLv_LearnLv &k1, const struct s_Key_Job_JobLv_LearnLv &k2) {
	return k1.LearnLv < k2.LearnLv ||  k1.joblv < k2.joblv;
	/*if (k1.LearnLv < k2.LearnLv || k1.joblv < k2.joblv)
		return true;
	else if(k1.LearnLv == k2.LearnLv && k1.joblv == k2.joblv)
	{
		return k1.CateGoryId < k2.CateGoryId;
	}*/
	//return k1.LearnLv < k2.LearnLv ||  k1.joblv < k2.joblv;
}
typedef map<s_Key_Job_JobLv_LearnLv, uint32> SkillLearnConditionMap_new;
typedef map<uint32, uint32> testMap;
 

//可变参数采用<ArgType, ArgValue>的形式传递，以处理不同的变参类型
typedef enum {
	CHAR_TYPE = 1,
	INT_TYPE,
	LONG_TYPE,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	STR_TYPE
}E_VAR_TYPE;
void ParseVarArgType(int dwArgNum, ...) {
	va_list pArgs = NULL;
	va_start(pArgs, dwArgNum);

	/*int i = 0;
	for (i = 0; i < dwArgNum; i++) {
		E_VAR_TYPE eArgType = va_arg(pArgs, int);
		switch (eArgType) {
		case INT_TYPE:
			printf("The %dth Argument: %d\n", i + 1, va_arg(pArgs, int));
			break;
		case STR_TYPE:
			printf("The %dth Argument: %s\n", i + 1, va_arg(pArgs, char*));
			break;
		default:
			break;
		}
	}
	va_end(pArgs);*/
}

//第一个参数定义可变参数个数，用于循环获取变参内容
void ParseVarArgByNum(int dwArgNum, ...) {
	va_list pArgs = NULL;
	va_start(pArgs, dwArgNum);
	int dwArgIdx;
	int dwArgVal = 0;
	for (dwArgIdx = 1; dwArgIdx <= dwArgNum; dwArgIdx++) {
		dwArgVal = va_arg(pArgs, int);
		printf("The %dth Argument: %d\n", dwArgIdx, dwArgVal);
	}
	va_end(pArgs);
}

#include <iostream>
#include <map>
int const MAX = 20;

class MyClass
{
public:
	//MyClass();
	MyClass(string t);
	//MyClass();
	~MyClass();

public:
	std::string& name;
	const int i;
};
 
MyClass::MyClass(string t):name(t),i(1)
{
	cout << i << " * " << name.c_str();
}

//MyClass::MyClass()
//{
//}

MyClass::~MyClass()
{
}

extern void testExtern();

//int main()
//{
//	string test = "ssssss";
//	string& test1 = test;
//	MyClass cs(test);
//	/*MyClass cs0(cs);
//	MyClass cs1 = cs;*/
//	//cout << cs.i <<" "<<cs.name.c_str();//奇怪，为什么会报错
//
//	testExtern();
//
//	int t = -1;
//	cout <<"unsigned "<< unsigned(-1) << endl;
//
//	getchar();
//	return 0;
//}

int main()
{
	std::map<int, int> mymap;
	std::map<int, int>::iterator itlow, itup;

	mymap[10] = 20;
	mymap[20] = 40;
	mymap[30] = 60;
	mymap[40] = 80;
	mymap[50] = 100;

	itlow = mymap.lower_bound(60);  // itlow points to b
	if (itlow==mymap.begin())
	{
		cout << "" << endl;
	}
	--itlow;
	if (itlow==mymap.begin())
	{
		cout << "" << endl;
	}
	if (itlow==mymap.end())
	{
		cout << "" << endl;
	}
	itup = mymap.upper_bound(20);   // itup points to e (not d!)

	 
	if (itlow == mymap.end())--itlow;
	if (itup == mymap.end())--itup;
	//--itlow;
	std::cout << itlow->first << " == " << itup->first<<endl;

	SkillLearnConditionMap_new mapnew;

	for (int i=0;i<10;++i)
	{
		s_Key_Job_JobLv_LearnLv key;
		key.joblv = 1;
		key.LearnLv = 0;
		key.CateGoryId = i+100;

		mapnew[key] = i+1000;
	}

	for (auto it = mapnew.begin();it!=mapnew.end();++it)
	{
		cout << it->first.joblv << " hh " << it->first.CateGoryId <<"  "<< it->second << endl;
	}

	/*for (int i = 0; i < 10; ++i)
	{
		s_Key_Job_JobLv_LearnLv key;
		key.joblv = 1;
		key.LearnLv = 0;
		key.CateGoryId = i + 100;

		if (auto it = mapnew.find(key) != mapnew.end())
			cout << "cate " <<key.CateGoryId<<" "<< endl;
	}*/

	for (int i = 0; i < 10; ++i)
	{
		s_Key_Job_JobLv_LearnLv key;
		key.joblv = 1;
		key.LearnLv = 0;
		key.CateGoryId = 100;
		auto it = mapnew.upper_bound(key);
		if ( it != mapnew.end())
			cout << "joblv " <<it->first.joblv<<" cateid: "<< it->first.CateGoryId << " Learnlv: "<<it->first.LearnLv << endl;
	}

	getchar();
	return 0;
}

//int main()
//{
	//map<int, int> m;
	////bar(m);

	//s_Key_Job_JobLv_LearnLv key_new;
	////key_new.job = 1;
	//key_new.joblv = 2;
	//key_new.LearnLv = 3;
	//SkillLearnConditionMap_new m_SkillLearnCondition_new;
	////auto it = lower_bound(m_SkillLearnCondition_new.begin(), m_SkillLearnCondition_new.end(), key_new);
	//testMap tmap;
	//auto it2 = tmap.lower_bound(2);

	//ParseVarArgByNum(3, 11, 22, 33);

	//int test = 1;
	//test = test << 2;
	//cout << test << endl;
	//getchar();
 //   return 0;
//}

