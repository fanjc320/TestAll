#pragma once

enum ConnectionState
{
	Connect_Success = 0,
	Connect_Unable_Connect,
	Connect_Unable_Reconnection
};

enum RobotSessionState
{
	Session_UnConnect,
	Session_ConnectEnterServer,			//链接登录
	Session_ValidateEnter,					//临时排队状态
	Session_ConnectGateServer,
	Session_Login,
	Session_InGame
};

typedef FastQueue<WorldPacket*, DummyLock> WorldPacketQueue;

class RSession
{
public:
	friend class World;
	//发包处理
	uint32 GetSessionId() { return m_instanceId; }
	void SetLoginData(PlayerInfo& data);
	void SendPing();
	void SendGMCmd(string cmd, string p1 = "", string p2 = "", string p3 = "", string p4 = "");
	void StartUserAuth();
	void SendUserAuthReq();
	void SendRoleSelectReq();
	void SendCreateRoleReq();

	void SendQueuingRequest();
	void SetPackKey(const std::string& key) 
	{ 
		m_packKey = key; 
	}
	const std::string& GetPackKey()
	{
		return m_packKey;
	}
	bool isRepeat = false;
	string ConvertLoginDateString(string& str);
	
public:
	RSession(uint32 instanceId);
	~RSession();
	void Update(uint32 ticket);

	void InitializePlayer(uint64 serverInstanceId,PlayerInfo& info);
	RPlayer* GetPlayer() { return m_player; }
	bool IsConnected();
	bool IsPlayerRun();
	void OnConnected();
	void OnDisconnected();
	void QueneMsg(WorldPacket* msg);
	void SendPacket(WorldPacket* msg);
	bool CheckMessage();
	void CloseSocket();
	void OnEnterSocketEvent(Socket* socket, SocketEventType event);
	void OnGateSocketEvent(Socket* socket, SocketEventType event);

	void SetSessionState(RobotSessionState state) { m_state = state; }
	void SetAllowAccess(bool state) { m_allowAccess = state; }
	void SetBoConfirm(uint8 val) { m_boConfirm = val; }
	void SetGateIpAndPort(const string& ip, const string& port) { 
		m_gateIp = ip; 
		m_gatePort = port;
	}
	void SetEnterKey(string& serverId, string& ticke, string& key) {
		m_serverId = serverId;
		m_ticke = ticke;
		m_key = key;
	}
	void AllowConnectToGate();
	void SetIsEnter(bool isEnter) { m_isEnter = isEnter; }
private:
	ConnectionState KeepConnectGate(uint32 ticket);
	void connected();
	void DispatchMsg();
	void FlushMsg();
	//player对象处理
	RPlayer* CreatePlayer(uint32 instanceId, PlayerInfo& info, RSession* session);
	void DestoryPlayer();

private:
	//登录服务器
	void KeepConnectEnterServer(uint32 ticket);
	void ConnectEnterServer();
	void KeepQueuingRequest(uint32 ticket);
	RobotSessionState GetSessionState() { return m_state; }
private:
	//instanceId是固定不变的
	uint32 m_instanceId;
	mutex m_sokcetLock;
	RSocket* m_rSocket = nullptr;
	mutex m_queneLock;
	WorldPacketQueue m_recvQuene;
	
	//异步链接回调
	SocketEventCallback enterCallback;
	SocketEventCallback gateCallback;
	recursive_mutex m_connectingSocketLock;
	Socket* m_connectingSocket = nullptr;

	uint32 m_lastConnectTime = 0;

	PlayerInfo m_loginData = {};
	RobotSessionState m_state = Session_UnConnect;

	RPlayer* m_player = nullptr;

	//enterserver
	uint32 m_lastConnectEnterTime = 0;
	uint32 m_lastValidateTime = 0;
	bool m_allowAccess = false;				//收到回报允许登录gate才能连接gate，一次有效
	bool m_firstLogin = false;
	bool m_firstValidate = false;
	uint8 m_boConfirm = 0;
	string m_gateIp;
	string m_gatePort;
	string m_serverId;
	string m_ticke;
	string m_key;
	bool m_isEnter = false;
	std::string m_packKey;
	atomic<uint32> m_TotalBuffers = 0;
};

