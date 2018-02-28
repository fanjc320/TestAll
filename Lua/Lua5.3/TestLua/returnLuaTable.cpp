
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
	//��key��val���õ�table�У�������key��val����ʱtableλ�ñ�Ϊ-1
	lua_settable(L, -3);
	stack_dump(L, "writeGlobalTable3");
	//stack->lua����table��ֵ��lua�У�������table
	lua_setglobal(L, "global_c_write_table");
	stack_dump(L, "writeGlobalTable4");
}