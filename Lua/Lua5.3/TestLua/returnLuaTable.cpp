
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