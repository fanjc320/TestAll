// TestLua.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#pragma  comment(lib,"Lua5.3.lib")
};

// 初始化Lua环境.  
lua_State* initLuaEnv()
{
	lua_State* luaEnv = luaL_newstate();
	luaopen_base(luaEnv);
	luaL_openlibs(luaEnv);

	return luaEnv;
}

// 加载Lua文件到Lua运行时环境中
bool loadLuaFile(lua_State* luaEnv, const string& fileName)
{
	int result = luaL_loadfile(luaEnv, fileName.c_str());
	if (result)
	{
		return false;
	}

	result = lua_pcall(luaEnv, 0, 0, 0);
	return result == 0;
}

// 获取全局函数
lua_CFunction getGlobalProc(lua_State* luaEnv, const string& procName)
{
	lua_getglobal(luaEnv, procName.c_str());
	if (!lua_iscfunction(luaEnv, 1))
	{
		return 0;
	}

	return lua_tocfunction(luaEnv, 1);
}

int main()
{
	/*lua_State *l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l,"main.lua");
	lua_close(l);
	system("pause");*/


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
	getline(cin, msgContent);
	getline(cin, msgContent);

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

    return 0;
}

