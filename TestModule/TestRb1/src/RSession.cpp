#include "stdafx.h"
#include "RSession.h"


RSession::~RSession()
{
	CloseSocket();
	while (m_recvQuene.HasItems()) {
		WorldPacket* data = m_recvQuene.front();
		m_recvQuene.Pop();
		delete data;
	}
	DestoryPlayer();
	sLog.outError("", "Session closed, id = %u", m_instanceId);
}

void RSession::AllowConnectToGate()
{
	if (m_state == Session_ValidateEnter && m_allowAccess) {
		SetSessionState(Session_ConnectGateServer);
		SetAllowAccess(false);
	}
}

void RSession::CloseSocket()
{
	//socket关掉play对象有也清除
	DestoryPlayer();
	m_sokcetLock.lock();
	if (m_rSocket) {
		m_rSocket->UnBindSession();
		m_rSocket->Disconnect();
		m_rSocket = nullptr;
 
		if (GetSessionState() >= Session_Login) {
			//认证失败直接链接gate
			//登录过才算机器人
			//sWorld.GetControlMgr()->DecreaseOnlineRobot();
		}
		if (m_state == Session_ValidateEnter && m_allowAccess) {
			AllowConnectToGate();
		}
		else {
			SetSessionState(Session_UnConnect);
		}
	}
	m_sokcetLock.unlock();
}

void RSession::OnEnterSocketEvent(Socket* socket, SocketEventType event)
{
	if (!socket) return;

	lock_guard<recursive_mutex> lock(m_connectingSocketLock);
	switch (event)
	{
	case socket_event_connecting:
		m_connectingSocket = socket;
#ifdef LogDebug
		sLog.outInfo("", "Connecting EnterServer...");
#endif
		break;
	case socket_event_connected:
		if (socket == m_connectingSocket) {
			m_connectingSocket = nullptr;

			m_sokcetLock.lock();
			m_rSocket = (RSocket*)socket;
			m_rSocket->BindSession(this);
			SetSessionState(Session_ValidateEnter);
			m_firstValidate = true;
			m_sokcetLock.unlock();
			//sWorld.GetControlMgr()->AddConnectEnterCount();
 
		}
		else
		{
			socket->Disconnect();
		}
		break;
	case socket_event_close:
		m_connectingSocket = nullptr;
		break;
	case socket_event_error:
		m_connectingSocket = nullptr;
		sLog.outError("RSession::OnEnterSocketEvent", "Connect EnterServer Error!");
		break;
	default:
		break;
	}
}

void RSession::OnGateSocketEvent(Socket* socket, SocketEventType event)
{
	if (!socket) return;

	lock_guard<recursive_mutex> lock(m_connectingSocketLock);
	switch (event)
	{
	case socket_event_connecting:
		m_connectingSocket = socket;
#ifdef LogDebug
			sLog.outInfo("", "Connecting GateServer...");
#endif
		break;
	case socket_event_connected:
		if (socket == m_connectingSocket) {
			m_connectingSocket = nullptr;
			m_sokcetLock.lock();
			m_rSocket = (RSocket*)socket;
			m_rSocket->BindSession(this);
			SetSessionState(Session_Login);
			m_firstLogin = true;
			m_sokcetLock.unlock();

			sLog.outInfo("", "GateServer Connected...");
		}
		else {
			sLog.outInfo("", "Connecting Gate server OutTime");
			socket->Disconnect();
		}
		break;
	case socket_event_close:
		m_connectingSocket = nullptr;
		sLog.outError("RSession::OnGateSocketEvent", "Connect GateServer close!");
		break;
	case socket_event_error:
		m_connectingSocket = nullptr;
		sLog.outError("RSession::OnGateSocketEvent", "Connect GateServer Error!");
		break;
	default:
		break;
	}
}

void RSession::Update(uint32 ticket)
{
	switch (m_state)
	{
	case Session_UnConnect:
		KeepConnectEnterServer(ticket);
		break;
	case Session_ValidateEnter:
		KeepQueuingRequest(ticket);
		break;
	case Session_ConnectGateServer:
		if (KeepConnectGate(ticket) != ConnectionState::Connect_Success)
			return;
		break;
	case Session_Login:
		StartUserAuth();
		break;
	case Session_InGame:
		if (IsPlayerRun()) {
			m_player->Update(ticket);
		}
		break;
	default:
		break;
	}
 	DispatchMsg();
 	FlushMsg();
}

bool RSession::IsConnected()
{
	bool able = false;
	m_sokcetLock.lock();
	if (m_rSocket && m_rSocket->IsConnected())
		able = true;
	m_sokcetLock.unlock();
	return able;
}

bool RSession::IsPlayerRun()
{
	return ((m_player) && (m_state == Session_InGame));
}

void RSession::KeepConnectEnterServer(uint32 ticket)
{
	if (IsConnected())
		CloseSocket();

	if (ticket > m_lastConnectEnterTime) {
		ConnectEnterServer();
	}
}

void RSession::ConnectEnterServer()
{
	m_packKey = "";
	m_isEnter = false;
	ServerConf* enterServer = sWorld.GetEnterCfg();
	if (!enterServer) {
		return;
	}

	sLog.outInfo("", "Connecting enter server [%s:%u] ...", enterServer->Host.c_str(), enterServer->Port);

	if (m_rSocket) {
		m_sokcetLock.lock();
		if (m_rSocket) {
			m_rSocket->Disconnect();
			m_rSocket = nullptr;
		}
		m_sokcetLock.unlock();
	}

	m_lastConnectEnterTime = getMSTime() + MsTimeVariables::MSTIME_30SECONDS;
	ConnectTCPSocketEx<RSocket>(enterServer->Host.c_str(), enterServer->Port, enterCallback);
}

void RSession::KeepQueuingRequest(uint32 ticket)
{
	if (IsConnected()) {
		//连接不成功，服务器主动断开
		if (m_firstValidate) {
			m_firstValidate = false;
			SendQueuingRequest();
		}
	}
	else
	{
		sLog.outError("rsession ", "is not connected ----------------- ");
	}
}

ConnectionState RSession::KeepConnectGate(uint32 ticket)
{
	if (IsConnected()) {
		CloseSocket();
	}

	if (ticket > m_lastConnectTime) {
		m_lastConnectTime = ticket + MsTimeVariables::MSTIME_15SECONDS;
		connected();
	}
	return Connect_Success;
}

void RSession::connected()
{
	if (m_rSocket) {
		m_sokcetLock.lock();
		if (m_rSocket) {
			m_rSocket->Disconnect();
			m_rSocket = nullptr;
		}
		m_sokcetLock.unlock();
	}

	ConnectTCPSocketEx<RSocket>(m_gateIp.c_str(), atoi(m_gatePort.c_str()), gateCallback);
}

void RSession::OnConnected()
{
	m_sokcetLock.lock();
	if (m_rSocket) {

	}
	m_sokcetLock.unlock();
}

void RSession::OnDisconnected()
{
	m_sokcetLock.lock();
	if (m_rSocket) {
		m_rSocket = nullptr;
		if (GetSessionState() == Session_ValidateEnter  && m_allowAccess == true) {
			AllowConnectToGate();
			//sLog.outError("RSession::OnDisconnected", " Session state: Session_ConnectGateServer!");
		}
		else {
			SetSessionState(Session_UnConnect);
			//sLog.outError("OnDisconnected", " Session state: Session_UnConnect!");
		}
	}
	m_sokcetLock.unlock();
}

void RSession::DispatchMsg()
{
	if (m_recvQuene.HasItems()) {
		WorldPacketQueue quene;
		m_queneLock.lock();
		m_recvQuene.PushAllToOther(quene);
		m_queneLock.unlock();

		sWorld.totalMessages += quene.GetNubs();
		while (quene.HasItems()) {
			WorldPacket* msg = quene.front();
			m_TotalBuffers -= msg->size();
			sMsgDispatcher.DispatcherMsg(*msg, this);
			quene.Pop();
			delete msg;
		}
	}
}

bool RSession::CheckMessage()
{
	if (m_state == Session_InGame) {
		if (!IsPlayerRun())
			return false;
	}
	return true;
}

void RSession::FlushMsg()
{
	m_sokcetLock.lock();
	if (m_rSocket) {
		m_rSocket->FlushQueue();
	}
	m_sokcetLock.unlock();
}

void RSession::QueneMsg(WorldPacket* msg)
{
	
	uint16 opcode = msg->GetOpcode();
	if (opcode == Message_PING) {
		delete msg;
		return;
	};
	m_queneLock.lock();
	m_TotalBuffers += msg->size();
	m_recvQuene.Push(msg);
	m_queneLock.unlock();
}

void RSession::SendPacket(WorldPacket* msg)
{
	m_sokcetLock.lock();
	if (m_rSocket)
	{
		msg->Encode(GetPackKey());
		m_rSocket->SendPacket(msg);
	}
	m_sokcetLock.unlock();
}

void RSession::SetLoginData(PlayerInfo& data)
{
	m_loginData = data;
}


void RSession::SendPing()
{
	WorldPacket msg(Message_PING, 10);
	msg << getMSTime();
	SendPacket(&msg);
}

void RSession::SendGMCmd(string cmd, string p1, string p2, string p3, string p4)
{
	char buf[128];
	sprintf(buf, "%s %s %s %s %s", cmd.c_str(), p1.c_str(), p2.c_str(), p3.c_str(), p4.c_str());

	WorldPacket msg(GAME_USER__GM_CMD, 128);
	msg.appendNetString(string(buf));
	SendPacket(&msg);
}

void RSession::StartUserAuth()
{
	if (m_isEnter == false) return;


	if (m_firstLogin) {
		//一链接就发认证？
		SendUserAuthReq();
		//sWorld.GetControlMgr()->AddOnlineRobot();
		m_firstLogin = false;
	}
}

void RSession::SendUserAuthReq()
{
	WorldPacket msg(LoginMsg_Authenticate, 1);
	msg << uint8(1);
	string accountName = sWorld.GetUserOpenId(m_instanceId);
	msg.appendNetString(ConvertLoginDateString(accountName));
	msg.appendNetString(m_serverId);
	msg.appendNetString(m_ticke);
	msg.appendNetString(m_key);
	SendPacket(&msg);
}

void RSession::SendRoleSelectReq()
{
	if (m_loginData.uid != 0){
		WorldPacket msg(LoginMsg_SelectRole, 10);
		msg << m_loginData.uid;
		SendPacket(&msg);
	}else{
		sLog.outError("Login Data RoleId is Error (Send LoginMsg_SelectRole accountID) :", " %d,(%u)\n", m_loginData.uid, m_instanceId);
	}
}

void RSession::SendCreateRoleReq()
{
	uint32 a[] = { 1,
		110,
		100,
		130,
		120,
		160,
		170,
		150,
		140
	};

	WorldPacket msg(LoginMsg_CreateRole, 1024);
	PlayerInfo info;
	char nameId[256];
	sprintf(nameId, "%d", m_instanceId);
	msg.appendNetString(string(nameId));

	uint16 ranModleIndex = rand() % (sizeof(a) / 4);
	uint16 modleId = ranModleIndex < sizeof(a) ? a[ranModleIndex] : a[0];
	ModleCfg* cfg = sInsMgr.GetModleCfg(modleId);
	if (cfg == NULL) return;

	msg << uint32(0) << uint8(1) << uint16(cfg->headId) << uint16(modleId) << uint16(1) << uint8(0) << uint8(0);
	msg << uint16(6) << uint16(6) << uint16(6) << uint16(6) << uint16(6);
	msg << uint8(0) << uint8(0) << uint8(10) << uint8(0) << uint16(0) << uint8(0);
	SendPacket(&msg);
}

void RSession::InitializePlayer(uint64 serverInstanceId, PlayerInfo& info)
{
	if (m_player) {
		sLog.outError("Session's player is not Null!", "");
		DestoryPlayer();
	}
	m_player = CreatePlayer(m_instanceId, info, this);
	if (!m_player) {
		sLog.outError("Create Player have Error!", "");
		return;
	}
	SetSessionState(Session_InGame);
	m_player->Init();
	m_player->SetServerInstanceId(serverInstanceId);
}

RPlayer* RSession::CreatePlayer(uint32 instanceId, PlayerInfo& info, RSession* session)
{
	RPlayer* play = new RPlayer(instanceId, info, session);
	if (play) {
		sWorld.AddPlayerCount();
		return play;
	}
	return nullptr;
}
void RSession::DestoryPlayer()
{
	if (m_player) {
		delete m_player;
		m_player = nullptr;
		sWorld.DelPlayerCount();
	}
}



void RSession::SendQueuingRequest()
{
	//sPerforReport.DoStartInfo(m_instanceId, "login");

	WorldPacket data(LOGIN_USER__ReadyLoginQueue, 50);

	string accountname = sWorld.GetUserOpenId(m_instanceId);
	if (accountname != "") {
		data.appendNetString(ConvertLoginDateString(accountname));
		data << (uint8)m_boConfirm;
		//日志 显示继续排队的操作
		if (m_boConfirm == 1)
			sLog.outInfo("SendQueuingRequest ", "%s:%u", accountname.c_str(), m_boConfirm);
		SendPacket(&data);
	}
}

string RSession::ConvertLoginDateString(string& str)
{

#ifdef Robot_IOS8
	return str;
#else
	const char* jsonLoginString = "{\
\"platform\":0,\
\"open_id\" : \"%s\",\
\"system\" : 100,\
\"program\" : 1,\
\"res\" : \"1.0.0.0\",\
\"config\" : \"0.0.117\",\
\"reconnect\" : false\
}";

	char buffer[4096];
	snprintf(buffer, 4096, jsonLoginString, str.c_str());
	// 
	// 	string str;
	// 	JsonWriter writer;
	//  	writer.Write("platform", 0);
	//  	writer.Writechar2("open_id", str.c_str());
	//  	writer.Write("system", 100);
	//  	writer.Write("program", 1);
	// 	string buff = "1.0.0.0";
	//  	writer.Writechar2("res", "1.0.0.0");
	//  	writer.Writechar2("config", "0.0.117");
	//  	writer.Write("reconnect", 0);
	// 	str = writer.GetJsonString();
	// 	return str;
	return buffer;
#endif
}

RSession::RSession(uint32 instanceId) :m_instanceId(instanceId)
{
	enterCallback = bind(&RSession::OnEnterSocketEvent, this, std::placeholders::_1, std::placeholders::_2);
	gateCallback = bind(&RSession::OnGateSocketEvent, this, std::placeholders::_1, std::placeholders::_2);
}
