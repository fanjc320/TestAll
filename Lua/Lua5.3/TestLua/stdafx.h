// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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
#include "returnLuaTable.h"

// TODO:  在此处引用程序需要的其他头文件
