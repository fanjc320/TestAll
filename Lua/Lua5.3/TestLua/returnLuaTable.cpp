
#include "stdafx.h"

int func_return_table(lua_State *L)
{
	lua_newtable(L);//创建一个表格，放在栈顶  
	lua_pushstring(L, "mydata");//压入key  
	lua_pushnumber(L, 66);//压入value  
	lua_settable(L, -3);//弹出key,value，并设置到table里面去  
	lua_pushstring(L, "subdata");//压入key  
	lua_newtable(L);//压入value,也是一个table  
	lua_pushstring(L, "mydata");//压入subtable的key  
	lua_pushnumber(L, 53);//value  
	lua_settable(L, -3);//弹出key,value,并设置到subtable  
	lua_settable(L, -3);//这时候父table的位置还是-3,弹出key,value(subtable),并设置到table里去  
	lua_pushstring(L, "mydata2");//同上  
	lua_pushnumber(L, 77);
	lua_settable(L, -3);
	return 1;//堆栈里现在就一个table.其他都被弹掉了。  
}

//返回的表结构是:
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
	//c->stack，创建一个新的table放到-1的位置
	lua_newtable(L);
	stack_dump(L,"writeGlobalTable0");
	//c->stack，增加一个key,放在-1的位置，table位置变为-2
	lua_pushstring(L, "integer_val");
	stack_dump(L, "writeGlobalTable1");
	//c->stack，增加key对应的值，放在-1位置，key位置变为-2，table位置变为-3
	lua_pushinteger(L, 1);
	stack_dump(L, "writeGlobalTable2");

	//lua_settable 就是把表在lua堆栈中的值弹出来，index 是table 在堆栈中的位置，假如 table 在 -3, 则key 应该是 -2，value 是 -1
	//相当于 table[key] = value.
	//将key和val设置到table中，并弹出key和val，此时table位置变为-1
	lua_settable(L, -3);//fjc:-3是因为此时table的位置在-3，所以table的index是-3，是因为上面的入栈操作把本来是-1的table挤到-3，一般情况下都是-3
	stack_dump(L, "writeGlobalTable3");
	//stack->lua，将table赋值到lua中，并弹出table
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
//This function pops both the key and the value from the stack.As in Lua, this function may trigger a metamethod for the "newindex" event(see §2.8).

//void lua_setglobal(lua_State *L, const char *name);
//Pops a value from the stack and sets it as the new value of global name.It is defined as a macro :
//
//#define lua_setglobal(L,s)   lua_setfield(L, LUA_GLOBALSINDEX, s)