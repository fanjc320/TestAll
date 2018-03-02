// TestLua.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

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

void readGlobalArray(lua_State* L)
{
	//lua->stack���õ�ȫ�����飬λ��-1
	lua_getglobal(L, "global_c_read_array");
	//�õ����鳤��
	lua_Integer array_len = luaL_len(L, -1);
	for (lua_Integer i = 1; i <= array_len; ++i) {
		//lua->stack,ȫ������λ��-1,Ȼ��iΪ��Ӧ������ֵ��������ֵ�ŵ�-1��λ��
		int ret_type = lua_rawgeti(L, -1, i);

		//--------------�������ԭ����table����-------------
		//lua_pushinteger(L, i);
		//int ret_type = lua_gettable(L, -2); //Ҳ����ʹ��int ret_type = lua_rawget(L, -2);    

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

	//c->stack������һ���µ�table�ŵ�-1��λ��
	lua_newtable(L);
	//c->stack��������Ӧ��key-val
	lua_pushinteger(L, 7); //����ֵ
	lua_rawseti(L, -2, 2);//��Ӧkey-val //fjc:������-2��-1�ͱ���,��Ϊ-2����table��-1��������ջ��7

	lua_pushnumber(L, 8.9); //����ֵ
	lua_rawseti(L, -2, 1);//��Ӧkey-val

	lua_pushstring(L, "test_string");//����ֵ
	lua_rawseti(L, -2, 3);//��Ӧkey-val

						  //--------------�������ԭ����table����-------------
						  //lua_pushinteger(L, 1); //����key
						  //lua_pushinteger(L, 7);//����ֵ
						  //lua_settable(L, -3); //Ҳ����ʹ��lua_rawset(L,-3);

						  //lua_pushinteger(L, 2); //����key
						  //lua_pushnumber(L, 8.9);//����ֵ
						  //lua_settable(L, -3); //Ҳ����ʹ��lua_rawset(L,-3);

						  //lua_pushinteger(L, 3); //����key
						  //lua_pushstring(L, "test_string");//����ֵ
						  //lua_settable(L, -3); //Ҳ����ʹ��lua_rawset(L,-3);


						  //stack->lua�������鸳ֵ��lua�У�����������
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
	//readGlobalArray(L); //�ᱨ��

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

