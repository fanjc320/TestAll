#pragma once

class RSession;

class RPlayer
{
public:
	RPlayer(uint32 instanceId, PlayerInfo& playInfo, RSession* session);
	RPlayer();
	~RPlayer();

	void Update(uint32 ticket);
	//RSession* GetSession() { return m_session; }
	void Init();
	void SetServerInstanceId(uint64 serverInstanceId);
private:
	uint32 m_instanceId;
	uint64 m_serverInstanceId = 0;
	PlayerInfo m_playInfo;
	RSession* m_session = nullptr;
};

