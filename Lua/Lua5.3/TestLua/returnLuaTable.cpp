
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
	//将key和val设置到table中，并弹出key和val，此时table位置变为-1
	lua_settable(L, -3);
	stack_dump(L, "writeGlobalTable3");
	//stack->lua，将table赋值到lua中，并弹出table
	lua_setglobal(L, "global_c_write_table");
	stack_dump(L, "writeGlobalTable4");
}