// TestLua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <lua.hpp>

int main()
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l,"main.lua");
	lua_close(l);
	system("pause");
    return 0;
}

