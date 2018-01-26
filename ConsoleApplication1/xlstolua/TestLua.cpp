//extern "C" {
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//}
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//int main()
//{
//	lua_State *L = lua_open();    //初始化lua
//	luaL_openlibs(L);    //载入所有lua标准库
//
//	string s;
//	while (getline(cin, s))    //从cin中读入一行到s
//	{
//		//载入s里的lua代码后执行
//		bool err = luaL_loadbuffer(L, s.c_str(), s.length(),
//			"line") || lua_pcall(L, 0, 0, 0);
//		if (err)
//		{
//			//如果错误，显示
//			cerr << lua_tostring(L, -1);
//			//弹出错误信息所在的最上层栈
//			lua_pop(L, 1);
//		}
//	}
//
//	lua_close(L);//关闭
//	return 0;
//}



//#include <stdio.h>
//#include <tchar.h>
//#include <iostream>
//using namespace std;
//extern "C" {
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//}
//
//int main()
//{
//	lua_State *l = luaL_newstate();
//	luaL_openlibs(l);
//	luaL_dofile(l, "test.lua");
//	lua_close(l);
//	system("pause");
//	return 0;
//}