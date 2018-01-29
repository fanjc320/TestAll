 

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int foo(lua_State *L)
{
	lua_pushnumber(L, 1);
	return 1;
}

static const struct luaL_Reg modulename[] = {
	{ "foo", foo },
	{ NULL,NULL },
};

//extern  int  luaopen_modulename(lua_State *L)
int __declspec(dllexport)  luaopen_modulename(lua_State *L)
{
	//luaL_newlib(L, modulename); 
	// 5.2之前使用
	luaL_register(L, "modulename", modulename);
	return 1;
}

//#  define luaL_newlib(L,libs) (\
//        lua_createtable(L, 0, sizeof(libs)/sizeof(libs[0])), \
//        luaL_register(L, NULL, libs))
//
//int __declspec(dllexport) luaopen_mycdll1(lua_State *L)
//{
//	luaL_newlib(L, myclib1);
//	return 1;
//}