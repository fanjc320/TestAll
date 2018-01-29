

#include "stdafx.h"

World sWorld;
World::World()
{

}

World::~World()
{

}

bool World::Initialize()
{
	//sInsMgr.Load();
	if (!sStressCfg.LoadCfg())
		return false;
	
	if (!ReloadServerCfg()) {
		return false;
	}
	/*if (!m_controlMgr.Initialize()) {
		return false;
	}*/
	if (!ReloadEnterCfg()) {
		return false;
	}
	/*脚本加载*/
	if (!ReloadLuaVM()) {
		return false;
	}
	//注册协议
	sMsgDispatcher.Init();


	return true;
}

void World::Update()
{
	m_LastTick = getMSTime();

	UpdateSession();
	m_FuncReactor.Dispatch();
	//m_controlMgr.Update();
}

void World::Destory()
{

}

ServerConf* World::GetServerCfg()
{
	return nullptr;
}

ServerConf* World::GetEnterCfg()
{
	if (m_enterList.size() > 0) {
		return &m_enterList[0];
	}
	return nullptr;
}

bool World::ReloadServerCfg()
{
	return true;
}

bool World::ReloadEnterCfg()
{
	m_enterList.clear();
	string buff = Config.MainConfig.GetStringDefault("EnterServer", "Host", "");
	if (buff == "") {
		sLog.outError("Config", "Load EnterServer Host Error!");
		return false;
	}

	vector<string> strVec;
	strVec = StrSplit(buff, ";");
	if (strVec.size() == 0) {
		sLog.outError("Config", "Load EnterServer Host Error!");
		return false;
	}
	vector<string> strHost;
	for (size_t i = 0; i < strVec.size(); i++)
	{
		strHost.clear();
		string& host = strVec[i];
		strHost = StrSplit(host, ":");
		if (strHost.size() == 2) {
			ServerConf cfg = {};
			cfg.Host = strHost[0];
			cfg.Port = strtouint32(strHost[1].c_str());
			m_enterList.push_back(cfg);
		}
	}
	return true;
}

bool World::ReloadLuaVM()
{
	return true;
}

string World::GetUserOpenId(uint32 instanceId)
{
	return to_string(instanceId);
}

void World::UpdateSession()
{
	uint32 ticket = getMSTime();
	//分批次和间隔创建session	
	BatchHandleCreate(ticket);
	//
	size_t sessionSize = m_sessionList.size();
	uint32 loopCount = min(sessionSize, ExcuteSessionCount);
	RSession* session = nullptr;
	uint32 totalTick = 0;
	m_MoveCount = 0;
	totalMessages = 0;
	//beginTick = getMSTime();

	while (loopCount)
	{
		uint32 tick = getMSTime();
		session = m_sessionList[m_curIndex];
		if (!session) {
			sLog.outError("World", "World Session Manager List Have Null Session Index = %d !", m_curIndex);
			continue;;
		}
		session->Update(ticket);
		uint32 loopTick = getMSTime() - tick;
		totalTick += loopTick;

		if (++m_curIndex == sessionSize)
			m_curIndex = 0;
		loopCount--;
	}

}

void World::BatchHandleCreate(uint32 ticket)
{

	static int insid = 0;
	if (ticket > m_lastBatchHandleTime) {
		uint32 haveSessionCount = m_sessionList.size();
		if (haveSessionCount>=1)
		{
			return;
		}
		for (size_t i = 0; i < 100; i++)
		{
			RSession* session = new RSession(++insid);
			if (!session) {
				sLog.outError("World", "Create Robot Error!");
				continue;
			}
			m_sessionList.push_back(session);
		}  
		m_lastBatchHandleTime = ticket +20;
	}

}

void World::CreateRobotSession(uint32 count)
{

}

void World::DestroyRobotSession()
{

}

void World::UpdateShowMemory(uint32 ticket)
{

}

void World::ShowMemoryInfo()
{
}
