
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