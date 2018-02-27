// TestLua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include <stdio.h>
//#include <tchar.h>
//#include <iostream>
//#include <string>
//using namespace std;
//extern "C" {
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//#pragma  comment(lib,"Lua5.3.lib")
//};


int generate()
{
	 

	// 初始化Lua运行时环境.  
	lua_State* luaEnv = initLuaEnv();
	if (!luaEnv)
	{
		return -1;
	}

	// 加载脚本到Lua环境中.  
	if (!loadLuaFile(luaEnv, ".\\GenerateNoteXML.lua"))
	{
		cout << "Load Lua File FAILED!" << endl;
		return -1;
	}

	// 获取Note信息.  
	string fromName;
	string toName;
	string msgContent;

	cout << "Enter your name:" << endl;
	cin >> fromName;

	cout << "\nEnter destination name:" << endl;
	cin >> toName;

	cout << "\nEnter message content:" << endl;
	cin.ignore();//fjc:ignore \n from last cin. cin will ignore whitespace,but getlin will not
	getline(cin, msgContent);
	//getline(cin, msgContent);

	// 将要调用的函数和函数调用参数入栈.  
	lua_getglobal(luaEnv, "generateNoteXML");
	lua_pushstring(luaEnv, fromName.c_str());
	lua_pushstring(luaEnv, toName.c_str());
	lua_pushstring(luaEnv, msgContent.c_str());

	// 调用Lua函数（3个参数,一个返回值）.  
	lua_pcall(luaEnv, 3, 1, 0);

	// 获取返回值.  
	if (lua_isboolean(luaEnv, -1))
	{
		int success = lua_toboolean(luaEnv, -1);
		if (success)
		{
			cout << "\nGenerate Note File Successful!" << endl;
		}
	}

	// 将返回值出栈.  
	lua_pop(luaEnv, 1);

	// 释放Lua运行时环境.  
	lua_close(luaEnv);

	system("pause");
	

    return 0;
}

//C调用LUA文件中的函数方法
//
//lua_getglobal(L, <function name>) //获取lua中的函数
//lua_push*() //调用lua_push系列函数，把输入参数压栈。例如lua_pushnumber(L, x)
//lua_pcall(L, <arguments nums>, <return nums>, <错误处理函数地址>)
