
#include "stdafx.h"

int func_return_table(lua_State *L)
{
	lua_newtable(L);//����һ����񣬷���ջ��  
	lua_pushstring(L, "mydata");//ѹ��key  
	lua_pushnumber(L, 66);//ѹ��value  
	lua_settable(L, -3);//����key,value�������õ�table����ȥ  
	lua_pushstring(L, "subdata");//ѹ��key  
	lua_newtable(L);//ѹ��value,Ҳ��һ��table  
	lua_pushstring(L, "mydata");//ѹ��subtable��key  
	lua_pushnumber(L, 53);//value  
	lua_settable(L, -3);//����key,value,�����õ�subtable  
	lua_settable(L, -3);//��ʱ��table��λ�û���-3,����key,value(subtable),�����õ�table��ȥ  
	lua_pushstring(L, "mydata2");//ͬ��  
	lua_pushnumber(L, 77);
	lua_settable(L, -3);
	return 1;//��ջ�����ھ�һ��table.�������������ˡ�  
}

//���صı�ṹ��:
//{
//	"mydata" = 66,
//		"mydate2" = 77,
//		"subdata" =
//	{
//		"mydata" = 53
//	}
//}

void writeGlobalTable(lua_State* L)
{
	stack_dump(L, "writeGlobalTable00");
	//c->stack������һ���µ�table�ŵ�-1��λ��
	lua_newtable(L);
	stack_dump(L,"writeGlobalTable0");
	//c->stack������һ��key,����-1��λ�ã�tableλ�ñ�Ϊ-2
	lua_pushstring(L, "integer_val");
	stack_dump(L, "writeGlobalTable1");
	//c->stack������key��Ӧ��ֵ������-1λ�ã�keyλ�ñ�Ϊ-2��tableλ�ñ�Ϊ-3
	lua_pushinteger(L, 1);
	stack_dump(L, "writeGlobalTable2");

	//lua_settable ���ǰѱ���lua��ջ�е�ֵ��������index ��table �ڶ�ջ�е�λ�ã����� table �� -3, ��key Ӧ���� -2��value �� -1
	//�൱�� table[key] = value.
	//��key��val���õ�table�У�������key��val����ʱtableλ�ñ�Ϊ-1
	lua_settable(L, -3);//fjc:-3����Ϊ��ʱtable��λ����-3������table��index��-3������Ϊ�������ջ�����ѱ�����-1��table����-3��һ������¶���-3
	stack_dump(L, "writeGlobalTable3");
	//stack->lua����table��ֵ��lua�У�������table
	lua_setglobal(L, "global_c_write_table");
	stack_dump(L, "writeGlobalTable4");
}

int CreateMatrix(lua_State *L) {
	lua_newtable(L);
	for (int i = 0; i < 5; i++) {
		lua_pushnumber(L, i + 1);    // parent table index
		lua_newtable(L);             // child table
		for (int j = 0; j < 3; j++) {
			lua_pushnumber(L, j + 1);  // this will be the child's index
			lua_pushnumber(L, j + 1);  // this will be the child's value
			lua_settable(L, -3);
		}
		lua_settable(L, -3);
	}
	lua_setglobal(L, "global_c_Matrix");
	return 1;
}

int make_matrix(lua_State *L) {
	lua_createtable(L, 5, 0);
	for (int i = 0; i < 5; ++i) {
		lua_createtable(L, 5, 0);
		for (int j = 0; j < 5; ++j) {
			lua_pushnumber(L, i + j);  // push some value, e.g. "pos[i][j]"
			lua_rawseti(L, -2, j + 1);
		}
		lua_rawseti(L, -2, i + 1);
	}
	lua_setglobal(L, "global_c_matrix");
	return 1;
}

//void lua_settable(lua_State *L, int index);
//Does the equivalent to t[k] = v, where t is the value at the given valid index, v is the value at the top of the stack, and k is the value just below the top.
//
//This function pops both the key and the value from the stack.As in Lua, this function may trigger a metamethod for the "newindex" event(see ��2.8).

//void lua_setglobal(lua_State *L, const char *name);
//Pops a value from the stack and sets it as the new value of global name.It is defined as a macro :
//
//#define lua_setglobal(L,s)   lua_setfield(L, LUA_GLOBALSINDEX, s)