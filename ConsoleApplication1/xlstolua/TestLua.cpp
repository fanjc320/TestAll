//extern "C" {
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//}
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//int main()
//{
//	lua_State *L = lua_open();    //��ʼ��lua
//	luaL_openlibs(L);    //��������lua��׼��
//
//	string s;
//	while (getline(cin, s))    //��cin�ж���һ�е�s
//	{
//		//����s���lua�����ִ��
//		bool err = luaL_loadbuffer(L, s.c_str(), s.length(),
//			"line") || lua_pcall(L, 0, 0, 0);
//		if (err)
//		{
//			//���������ʾ
//			cerr << lua_tostring(L, -1);
//			//����������Ϣ���ڵ����ϲ�ջ
//			lua_pop(L, 1);
//		}
//	}
//
//	lua_close(L);//�ر�
//	return 0;
//}



//#include <stdio.h>
//#include <tchar.h>
//#include <iostream>
//using namespace std;
//extern "C" {
//#include "lua.h"
//#include "lualib.h"
//#include "lauxlib.h"
//}
//
//int main()
//{
//	lua_State *l = luaL_newstate();
//	luaL_openlibs(l);
//	luaL_dofile(l, "test.lua");
//	lua_close(l);
//	system("pause");
//	return 0;
//}