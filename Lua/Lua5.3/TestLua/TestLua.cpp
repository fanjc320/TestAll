// TestLua.cpp : �������̨Ӧ�ó������ڵ㡣
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

// ��ʼ��Lua����.  
lua_State* initLuaEnv()
{
	lua_State* luaEnv = luaL_newstate();
	luaopen_base(luaEnv);
	luaL_openlibs(luaEnv);

	return luaEnv;
}

// ����Lua�ļ���Lua����ʱ������
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

// ��ȡȫ�ֺ���
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


	
	

    return 0;
}

