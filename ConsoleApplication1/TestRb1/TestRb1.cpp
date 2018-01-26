// TestRb1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Singleton.h"

//uint8 loglevel = DEFAULT_LOG_LEVEL;
std::string GApplicationPath;

int win32_main(int argc, char ** argv)
{
	//sLog.open();
	SetThreadName("Main Thread");

	THREAD_TRY_EXECUTION
	{
		//InitGlobal();
		sMaster.Run();
	}
	THREAD_HANDLE_CRASH;
	exit(0);
}

void OnCrash(bool Terminate)
{
	try {
		//sLuncher.Terminate();
	}
	catch (...) {
		sLog.outError("OnCrash", "exception catched in oncrash handler");
	}
}

int main(int argc, char ** argv)
{
	//sSocketMgr.GetCompletionPort();
#ifdef WIN32	
	win32_main(argc, argv);
#else
	unix_main(argc, argv);
#endif
}

