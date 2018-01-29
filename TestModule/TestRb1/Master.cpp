

#include "stdafx.h"
#include "Singleton.h"
//#include "Master.h"

volatile bool Master::m_stopEvent;

createFileSingleton(Master);


Master::Master()
{
}

Master::~Master()
{
}

bool Master::Run()
{
	system("chcp 65001");

	system("cls");
	if (!StartServer())
		return false;

	while (!m_stopEvent)
	{
		m_CmdDispatcher.DispatchCommands();
	}

	StopServer();
	return true;
}

bool Master::StartServer()
{
	m_stopEvent = false;
	InitializeLogger();
	if (!LoadConfig())
		return false;
	ThreadPool.Startup();

	InitializeNetLib();

	m_WorldThread = new thread(&Master::MainThreadLoop, this);
	return true;
}

bool Master::StopServer()
{
	return false;
}

void Master::Terminate()
{
}

void Master::InitializeLogger()
{
	UNIXTIME = time(NULL);
	sLog.Init(5, 3);
}

bool Master::LoadConfig()
{
	if (!Config.MainConfig.SetSource(Default_Config_File)) {
		sLog.outError("Config", ">> %s error!", Default_Config_File);
		return false;
	}

	int32 scrLogLv = Config.MainConfig.GetIntDefault("LogLevel", "Screen", 0);
	int32 fileLogLv = Config.MainConfig.GetIntDefault("LogLevel", "File", 0);
	sLog.Init(fileLogLv, scrLogLv);
	return true;
}

void Master::InitializeNetLib()
{
	new SocketMgr;
	new SocketGarbageCollector;
	sSocketMgr.SpawnWorkerThreads();
}

void Master::_HookSignals()
{
}

void Master::_UnhookSignals()
{
}

void Master::MainThreadLoop()
{
	if (!sWorld.Initialize())
		Terminate();

	uint32 now = 0;
	uint32 slow_Ticket = 0;
	while (!m_stopEvent)
	{
		UNIXTIME = time(nullptr);
		sWorld.Update();
		now = getMSTime();
		if (now > slow_Ticket) {
			//sSocketGarbageCollector.Update();
			slow_Ticket = now + 10000;
		}
		Sleep(1);
	}
	sWorld.Destory();
}
