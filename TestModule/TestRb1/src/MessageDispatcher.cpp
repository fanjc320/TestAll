#include "stdafx.h"

MessageDispatcher sMsgDispatcher;
MessageDispatcher::MessageDispatcher()
{
}


MessageDispatcher::~MessageDispatcher()
{
}

void MessageDispatcher::Init()
{
	RegistHandler(LoginMsg_Authenticate, HandleAuthAck);
	RegistHandler(LoginMsg_QueryRoleList, HandleRoleListAck);
	RegistHandler(LoginMsg_SelectRole, HandleSelectRoleAck);
	RegistHandler(LoginMsg_CreateRole, HandleCreateRoleNtf);

	RegistHandler(USER_PACK_KEY_NOTIFY, HandlePackKeyNotify);
	RegistHandler(LOGIN_USER__ReadyLoginQueue, HandleQueuingRequestAck);
	//自己初始化完成
	RegistHandler(GAME_USER__INIT_ME, HandleRoleInitMeNtf);
	RegistHandler(GAME_USER__INIT_ME_End, HandleRoleInitMeEnd);
	//踢下线反馈
	RegistHandler(Cmd_WORLD_TO_GATE_OUTLINE, HandleOutLine);
	RegistHandler(GameMsg_ForceClose, HandleForceOutLine);
	/************************************************************************/
	/*  游戏逻辑相关                                                            */
	/************************************************************************/
	// 检测包
	//RegistHandler(GAME_USER_CHECK_PACKET, HandleCheckPacket);
}

void MessageDispatcher::RegistHandler(uint32 opCodeId, Func handlerFunc)
{
	HandlerInfo info;
	info.opCodeId = opCodeId;
	info.func = handlerFunc;
	m_FuncList[opCodeId] = info;
}

void MessageDispatcher::HandlePackKeyNotify(WorldPacket& msg, RSession* session)
{
	session->SetIsEnter(true);
	std::string packKey;
	msg.readNetString(packKey);
	session->SetPackKey(packKey);
}

void MessageDispatcher::DispatcherMsg(WorldPacket& msg, RSession* session)
{
	FuncList::iterator iter = m_FuncList.find(msg.GetOpcode());
	if (iter != m_FuncList.end()) {
		HandlerInfo& info = iter->second;
		if (!info.func)
			return;
		bool isVaild = session->CheckMessage();
		if (isVaild) {
//#ifdef DEF_ENCODE
			if (msg.GetOpcode() != USER_PACK_KEY_NOTIFY && msg.GetOpcode() != USER_ENTER_KEY_NOTIFY)
			{
				msg.Uncode(session->GetPackKey());
			}
//#endif

			info.func(msg, session);
		}
	}
}

void MessageDispatcher::HandleQueuingRequestAck(WorldPacket& msg, RSession* session)
{
	string loginKey;
	string serverId;
	string overTime;
	string key;
	string ip;
	string port;
	string msgType;
	uint32 repeatTime;
	uint8 state;
	uint8 boConfirm;
	msg.readNetString(loginKey);
	msg.readNetString(serverId);
	msg.readNetString(overTime);
	msg.readNetString(key);
	msg.readNetString(ip);
	msg.readNetString(port);
	msg.readNetString(msgType);
	msg >> repeatTime;
	msg >> state;
	msg >> boConfirm;
	if (state == 2) {
		session->SetAllowAccess(true);
		session->SetGateIpAndPort(ip, port);
		session->SetEnterKey(serverId, overTime, key);
		session->CloseSocket();

#ifdef LogDebug
		sLog.outDebug("MessageDispatcher::HandleQueuingRequestAck", "Recive Enter Permit, IP:%s, Port:%s, SessionId %d\n", ip.c_str(), port.c_str(), session->GetSessionId());
#endif
	}
	else {
		if (boConfirm == 1) //继续排队,不马上断开连接
		{
			session->SetBoConfirm(boConfirm);
			session->SetSessionState(Session_ValidateEnter);
		}
		else
		{
			session->SetAllowAccess(false);
			session->CloseSocket();
		}
#ifdef LogDebug
		sLog.outDebug("MessageDispatcher::HandleQueuingRequestAck", "Recive Enter Refuse SessionId %d\n", session->GetSessionId());
#endif
	}
}

void MessageDispatcher::HandleAuthAck(WorldPacket& msg, RSession* session)
{
	uint32 isAuth;
	msg >> isAuth;
	if (isAuth == 0) {
#ifdef LogDebug
		sLog.outInfo("--$ PlayMgr::HandleAuthAck Recive Auth ID :", " %d\n", session->GetSessionId());
#endif
	}
	else {
#ifdef LogDebug
		sLog.outError("--$ MessageDispatcher::HandleAuthAck LoginMsg_Authenticate", "Fail errID : %d, SessionId:%d", isAuth, session->GetSessionId());
#endif
		session->CloseSocket();
	}
}

void MessageDispatcher::HandleRoleListAck(WorldPacket& msg, RSession* session)
{
	uint32 errId;
	msg >> errId;
	if (errId == 0) {
		PlayerInfo clientList[5];
		uint8 accNum;
		msg >> accNum;
		for (uint32 i = 0; i < accNum && i < 5; i++)
		{
			PlayerInfo clientInfo;
			msg.readNetString(clientInfo.name);
			msg >> clientInfo.uid;
			msg >> clientInfo.gender >> clientInfo.headID >> clientInfo.roleID >> clientInfo.level >> clientInfo.job >> clientInfo.jobLv;
			msg >> clientInfo.addpoints[apStrength] >> clientInfo.addpoints[apStrong] >> clientInfo.addpoints[apSpeed] >> clientInfo.addpoints[apEndurance] >> clientInfo.addpoints[apMagic];
			msg >> clientInfo.elements[eleEarth] >> clientInfo.elements[eleWater] >> clientInfo.elements[eleFire] >> clientInfo.elements[eleWind] >> clientInfo.lastmapid >> clientInfo.colorscheme;
			clientList[i] = clientInfo;
		}
		if (accNum > 0)
		{
			session->SetLoginData(clientList[0]);
#ifdef LogDebug
			sLog.outDebug("--$ PlayMgr::HandleRoleListAck RoleList UID :", " %d\n", clientList[0].uid);
#endif
			session->SendRoleSelectReq();
		}
		else if (accNum == 0)
		{
#ifdef LogDebug
			sLog.outError("--$", " MessageDispatcher::HandleRoleListAck RoleList is Null");
#endif
			//发送创角
			//名字监测
			//socket->SendCheckName();
			session->SendCreateRoleReq();
		}
	}
	else
	{
#ifdef LogDebug
		sLog.outError("--$ MessageDispatcher::HandleRoleListAck LoginMsg_QueryRoleList 1201 Fail errID :", " %d\n", errId);
#endif
	}
}

void MessageDispatcher::HandleSelectRoleAck(WorldPacket& msg, RSession* session)
{
	uint32 ack;
	msg >> ack;
	if (ack == 0) {
		//session->SendRoleEnterWorldReq();
	}
	else
	{
		sLog.outError("--$ MessageDispatcher::HandleSelectRole errID :", "%d\n", ack);
	}
}

void  MessageDispatcher::HandleCreateRoleNtf(WorldPacket& msg, RSession* session)
{
	uint32 isCreateSuccess;
	msg >> isCreateSuccess;
	if (isCreateSuccess != 0) {
		//socket->SendUserEnterReq();
#ifdef LogDebug
		sLog.outError("--$ MessageDispatcher::HandleCreateRoleNtf first create role ID : ", " %d, errId : %d\n", session->GetSessionId(), isCreateSuccess);
#endif
		//sessiont->CloseSocket();
	}
}

void MessageDispatcher::HandleRoleInitMeEnd(WorldPacket& msg, RSession* session)
{
	RPlayer* plr = session->GetPlayer();
	if (plr == nullptr) {
		return;
	}
	//plr->Execute_OtherScripts("player", "InitEnd", plr->GetMapId());
}

void MessageDispatcher::HandleRoleInitMeNtf(WorldPacket& msg, RSession* session)
{
	//sLog.outError("~~$", "Role Init!");
	//角色初始化
	uint64 instanceId = 0;
	PlayerInfo info = {};
	msg >> instanceId;
	msg >> info.accid >> info.uid;
	msg.readNetString(info.name);
	msg >> info.gender >> info.headID >> info.roleID >> info.job >> info.jobLv >> info.level >> info.exp >> info.honor >> info.honorLv;
	msg >> info.coin >> info.gold >> info.bindGold >> info.freeAttr;
	for (int32 i = AddPointAttribute::apStrength; i < AddPointAttribute::apMax; i++) { msg >> info.addpoints[i]; }
	for (int32 i = AttributeSlot::slotMin; i < AttributeSlot::slotMax; i++)
	{
		AttributeValueType attr = 0;
		msg >> attr;
		info.attrs[i] = (int32)attr;
	}
	for (size_t i = ElementType::eleMin; i < ElementType::eleMax; i++) { msg >> info.elements[i]; }

	msg >> info.Hp >> info.Mp >> info.race;
	msg >> info.lastmapid >> info.lastX >> info.lastY >> info.mapline;
	session->InitializePlayer(instanceId,info);

}


void MessageDispatcher::HandleErrorMsg(WorldPacket& msg, RSession* session)
{
	std::string errorMsg;
	msg.readNetString(errorMsg);
	//sLog.outError("Error:", errorMsg.c_str());
}

void MessageDispatcher::HandleOutLine(WorldPacket& msg, RSession* session)
{
	uint32 errCode = 0;
	std::string errMsg;
	msg >> errCode;
	msg.readNetString(errMsg);
	sLog.outInfo("OutLine :", errMsg.c_str());
}

void MessageDispatcher::HandleForceOutLine(WorldPacket& msg, RSession* session)
{
	uint32 errCode = 0;
	std::string errMsg;
	msg >> errCode;
	msg.readNetString(errMsg);
	sLog.outInfo("Force OutLine :", errMsg.c_str());
}