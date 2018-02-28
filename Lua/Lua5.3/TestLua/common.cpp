#include "stdafx.h"
//#include "common.h"

void stack_dump(lua_State* L,string flag) {
	printf("\n------ stack dump begin  %s ------\n",flag.c_str());
	for (int i = 1; i <= lua_gettop(L); ++i) {//lua_gettop取得栈中元素个数
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TNONE: {
			printf("LUA_TNONE\n");
		}break;

		case LUA_TNIL: {
			printf("LUA_TNIL\n");
		}break;

		case LUA_TBOOLEAN: {
			printf("LUA_TBOOLEAN : %s\n", lua_toboolean(L, i) ? "true" : "false");
		}break;

		case LUA_TLIGHTUSERDATA: {
			printf("LUA_TLIGHTUSERDATA\n");
		}break;

		case LUA_TNUMBER: {
			//整形
			if (lua_isinteger(L, i)) {
				printf("LUA_TNUMBER integer : %lld \n", lua_tointeger(L, i));
			}
			else if (lua_isnumber(L, i)) {
				printf("LUA_TNUMBER number: %g\n", lua_tonumber(L, i));
			}
		}break;

		case LUA_TSTRING: {
			printf("LUA_TSTRING : %s\n", lua_tostring(L, i));
		}break;

		case LUA_TTABLE: {
			printf("LUA_TTABLE\n");
		}break;

		case LUA_TFUNCTION: {
			printf("LUA_TFUNCTION\n");
		}break;

		case LUA_TUSERDATA: {
			printf("LUA_TUSERDATA\n");
		}break;

		case LUA_TTHREAD: {
			printf("LUA_TTHREAD\n");
		}break;

		case LUA_NUMTAGS: {
			printf("LUA_NUMTAGS\n");
		}break;

		default: {
			printf("%s\n", lua_typename(L, t));
		}break;
		}
	}

	std::cout << "------ stack dump end ------" << std::endl;
}