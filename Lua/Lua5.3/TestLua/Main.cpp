// TestLua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

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

void readGlobalArray(lua_State* L)
{
	//lua->stack，得到全局数组，位置-1
	lua_getglobal(L, "global_c_read_array");
	//得到数组长度
	lua_Integer array_len = luaL_len(L, -1);
	for (lua_Integer i = 1; i <= array_len; ++i) {
		//lua->stack,全局数组位置-1,然后i为对应的索引值，将返回值放到-1的位置
		int ret_type = lua_rawgeti(L, -1, i);

		//--------------被替代的原操作table函数-------------
		//lua_pushinteger(L, i);
		//int ret_type = lua_gettable(L, -2); //也可以使用int ret_type = lua_rawget(L, -2);    

		//stack->c
		if (ret_type == LUA_TNUMBER) {
			if (lua_isinteger(L, -1)) {
				printf("%lld\n", lua_tointeger(L, -1));
			}
			else if (lua_isnumber(L, -1)) {
				printf("%g\n", lua_tonumber(L, -1));
			}
		}
		else if (ret_type == LUA_TSTRING) {
			printf("%s\n", lua_tostring(L, -1));
		}

		lua_pop(L, 1);
	}
}

void writeGlobalArray(lua_State* L)
{
	/*void lua_rawseti(lua_State *L, int index, int n);
	Does the equivalent of t[n] = v, where t is the value at the given valid index and v is the value at the top of the stack.
	This function pops the value from the stack.The assignment is raw; that is, it does not invoke metamethods.*/

	//c->stack，创建一个新的table放到-1的位置
	lua_newtable(L);
	//c->stack，创建对应的key-val
	lua_pushinteger(L, 7); //设置值
	lua_rawseti(L, -2, 2);//对应key-val //fjc:必须是-2，-1就报错,因为-2才是table，-1是上面入栈的7

	lua_pushnumber(L, 8.9); //设置值
	lua_rawseti(L, -2, 1);//对应key-val

	lua_pushstring(L, "test_string");//设置值
	lua_rawseti(L, -2, 3);//对应key-val

						  //--------------被替代的原操作table函数-------------
						  //lua_pushinteger(L, 1); //设置key
						  //lua_pushinteger(L, 7);//设置值
						  //lua_settable(L, -3); //也可以使用lua_rawset(L,-3);

						  //lua_pushinteger(L, 2); //设置key
						  //lua_pushnumber(L, 8.9);//设置值
						  //lua_settable(L, -3); //也可以使用lua_rawset(L,-3);

						  //lua_pushinteger(L, 3); //设置key
						  //lua_pushstring(L, "test_string");//设置值
						  //lua_settable(L, -3); //也可以使用lua_rawset(L,-3);


						  //stack->lua，将数组赋值到lua中，并弹出数组
	lua_setglobal(L, "global_c_write_array");
}

void readGlobaleVar(lua_State* L)
{
	//lua->stack
	lua_getglobal(L, "global_c_read_val");
	//stack->c
	if (const char* val = lua_tostring(L, -1)) {
		std::cout << val << std::endl;
	}
}

void writeGlobalVar(lua_State* L)
{
	//c->stack
	lua_pushstring(L, "test new value");
	//stack->lua
	lua_setglobal(L, "global_c_write_val");
}

int main()
{

	/*lua_State *l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l, "main.lua");
	lua_close(l);
	system("pause");*/

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	/*readGlobaleVar(L);
	writeGlobalTable(L);
	func_return_table(L);
	writeGlobalArray(L);*/
	//readGlobalArray(L); //会报错

	CreateMatrix(L);
	make_matrix(L);
	 
	lua_newtable(L);
	for (int i = 0; i < 5; i++) {
		lua_pushnumber(L, i + 1);    // parent table index
		lua_newtable(L);             // child table
		for (int j = 0; j < 3; j++) {
			lua_pushnumber(L, j + 1);  // this will be the child's index
			lua_pushnumber(L, j*10 + 1);  // this will be the child's value
			lua_settable(L, -3);
		}
		lua_settable(L, -3);
	}
	lua_setglobal(L, "g_npcPos1");

	//luaL_dofile(L, "main.lua");
	luaL_dofile(L, "E:/TestProjs/Lua/Lua5.3/TestLua/main.lua");
	//luaL_dofile(L, "E:\\TestProjs\\Lua\\Lua5.3\\TestLua\\main.lua");
	//luaL_dofile(L, "E:\TestProjs\Lua\Lua5.3\TestLua\main.lua");

	luaL_dofile(L, "E:/CrossgateS/binExe/configs/npclua/wanfalog.lua");
	cout << "dofile ok----------------------" << endl;

	lua_close(L);
	system("pause");


	


	return 0;
}

