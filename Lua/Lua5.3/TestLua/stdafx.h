// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
 
#include <iostream>
#include <string>
using namespace std;
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#pragma  comment(lib,"Lua5.3.lib")
};

#include "common.h"

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
