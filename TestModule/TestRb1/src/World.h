#pragma once

typedef vector<RSession*> SessionList;
typedef vector<ServerConf> ServerCfgList;

static const size_t ExcuteSessionCount = 200;

class World
{
public:
	World();
	~World();
	bool Initialize();
	void Update();
	void Destory();

	void QueneFunc(ThreadingFunc functor) { m_FuncReactor.AddFunctor(functor); }
	//ControlMgr* GetControlMgr() { return &m_controlMgr; }
	ServerConf* GetServerCfg();
	ServerConf* GetEnterCfg();
	bool ReloadServerCfg();
	bool ReloadEnterCfg();
	bool ReloadLuaVM();
	string GetUserOpenId(uint32 instanceId);
	
	/*机器人服务器instanceID*/
	uint64 GetServerInstanceId();
	void SetServerInstanceId(uint64 serverInstanceId);
public:
	
private:
	void UpdateSession();
	void BatchHandleCreate(uint32 ticket);
	void CreateRobotSession(uint32 count);
	void DestroyRobotSession();
	void UpdateShowMemory(uint32 ticket);
	void ShowMemoryInfo();

private:
	ThreadingFuncReactor m_FuncReactor;
	SessionList m_sessionList;
	ServerCfgList m_serverList;
	ServerCfgList m_enterList;
	//ControlMgr m_controlMgr;
	uint32 m_curIndex = 0;
	uint32 m_lastBatchHandleTime;

private:
	atomic<bool> m_guildPvPOpenMark = false;
	bool m_bNeedCheckActOpen = false;			//家族战是否需要检查重复开启活动
	uint32 m_nextGuildActOpenTime = 0;
	uint32 m_lastCheckOpenTime = 0;
	uint32 m_lastMemoryShowTime = 0;
	bool m_AlloShowMemory = false;

private:
	bool m_bOpenPerfor = false;
public:
	atomic<TickInt> m_LastTick = 0;
	uint32 m_MoveCount = 0;
	uint32 totalMessages = 0;
	uint32 maxMessages = 0;
	uint32 TotalHit = 0;
	uint32 maxHit = 0;
	uint32 m_TotalTick = 0;
};

extern World sWorld;