#pragma once


lua_State* initLuaEnv();
bool loadLuaFile(lua_State* luaEnv, const string& fileName);
lua_CFunction getGlobalProc(lua_State* luaEnv, const string& procName);