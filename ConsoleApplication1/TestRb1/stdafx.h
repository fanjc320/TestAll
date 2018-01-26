// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#pragma execution_character_set("utf-8")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "lua51.lib")
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "hiredis.lib")
#pragma comment(lib, "ziplib.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "psapi.lib")


//#ifdef _DEBUG 
//#pragma comment(lib, "shared_d.lib")
//#pragma comment(lib, "luabind_d.lib")
//#else
#pragma comment(lib, "shared.lib")	
#pragma comment(lib, "luabind.lib")
//#endif


#include <list>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <search.h>
#include <fcntl.h>
#include <signal.h>
#include <bitset>
#include <math.h>
#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <chrono>

#include "FactoryClass.h" 
#include "Common.h"
#include <Psapi.h> 
#include "MersenneTwister.h"

//fjc


#include "WorldPacket.h"
#include "Log.h"
#include "ByteBuffer.h"
#include "StackBuffer.h"
#include "Config/ConfigEnv.h"
#include "crc32.h"
#include "LocationVector.h"
#include "ConsoleCmdDispatcher.h"
#include "Updatable.h"
#include "Database/DatabaseEnv.h"
#include "Timer.h"
//

#include "TLog/TLogWrapper.h"

#include <Network/Network.h>

#include "Auth/MD5.h"
#include "Auth/BigNumber.h"
#include "Auth/Sha1.h"
#include "Auth/WowCrypt.h"
#include "FastQueue.h"
#include "CircularQueue.h"
#include "Threading/RWLock.h"
#include "Threading/Condition.h"
#include "Threading/EventLoop.h"

#include "InvokerScriptParser.h"
#include "Threading/thread_pool.h"


//json解析库
#define RAPIDJSON_HAS_STDSTRING 1
#include "rapidjson_reader/JsonWriter.h"
#include "ZipLibAdapter.h"
#include "Communication/protocols.h"


#include "Communication/protocols.h"


#include "sysservice/service_base.h"
#include "sysservice/service_installer.h"
#include "CrashHandler.h"

#include "dir.h"
#include "Storage.h"
#include "PerfCounters.h"
//
//#include "MemJson.h"
//
//
//
#include "../common/GameTypes.h"
Use_Ns_CrossGate


#include "Storage.h"
#include "PerfCounters.h"
#include "Communication/Protocols.h"
#include "Threading/EventLoop.h"
#include "Communication/MessageSocket.h"
//#include "../logonserver/LogonOpcodes.h"
//
//
#include "../common/DataDefine.h"
#include "../Common/Opcodes.h"
#include "../Common/ServerOpcode.h"

#include "MessageDispatcher.h"
#include "Master.h"
#include "InstanceMgr.h"
#include "RbConfig.h"

#include "RPlayer.h"
#include "RSocket.h"
#include "RSession.h"
#include "World.h"


#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define DELTA_EPOCH_IN_USEC  11644473600000000ULL

extern "C" {
#include "../../dependencies/VC/include/pcre.h"
};

static char StringConversionStorage[2048];
extern const char* StringToANSI(const char*   pUtf8Buf);


