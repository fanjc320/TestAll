// TestLua.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
//#include <stdio.h>
//#include <tchar.h>
//#include <iostream>
//#include <string>
//using namespace std;
//extern "C" {
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//#pragma  comment(lib,"Lua5.3.lib")
//};


int generate()
{
	 

	// ��ʼ��Lua����ʱ����.  
	lua_State* luaEnv = initLuaEnv();
	if (!luaEnv)
	{
		return -1;
	}

	// ���ؽű���Lua������.  
	if (!loadLuaFile(luaEnv, ".\\GenerateNoteXML.lua"))
	{
		cout << "Load Lua File FAILED!" << endl;
		return -1;
	}

	// ��ȡNote��Ϣ.  
	string fromName;
	string toName;
	string msgContent;

	cout << "Enter your name:" << endl;
	cin >> fromName;

	cout << "\nEnter destination name:" << endl;
	cin >> toName;

	cout << "\nEnter message content:" << endl;
	cin.ignore();//fjc:ignore \n from last cin. cin will ignore whitespace,but getlin will not
	getline(cin, msgContent);
	//getline(cin, msgContent);

	// ��Ҫ���õĺ����ͺ������ò�����ջ.  
	lua_getglobal(luaEnv, "generateNoteXML");
	lua_pushstring(luaEnv, fromName.c_str());
	lua_pushstring(luaEnv, toName.c_str());
	lua_pushstring(luaEnv, msgContent.c_str());

	// ����Lua������3������,һ������ֵ��.  
	lua_pcall(luaEnv, 3, 1, 0);

	// ��ȡ����ֵ.  
	if (lua_isboolean(luaEnv, -1))
	{
		int success = lua_toboolean(luaEnv, -1);
		if (success)
		{
			cout << "\nGenerate Note File Successful!" << endl;
		}
	}

	// ������ֵ��ջ.  
	lua_pop(luaEnv, 1);

	// �ͷ�Lua����ʱ����.  
	lua_close(luaEnv);

	system("pause");
	

    return 0;
}

//C����LUA�ļ��еĺ�������
//
//lua_getglobal(L, <function name>) //��ȡlua�еĺ���
//lua_push*() //����lua_pushϵ�к��������������ѹջ������lua_pushnumber(L, x)
//lua_pcall(L, <arguments nums>, <return nums>, <����������ַ>)
