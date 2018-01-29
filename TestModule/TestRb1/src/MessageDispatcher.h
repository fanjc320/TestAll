#pragma once

class RSession;

typedef void(*Func)(WorldPacket& msg, RSession* session);
struct HandlerInfo
{
	uint32 opCodeId;
	Func func = nullptr;
};

typedef unordered_map<uint32, HandlerInfo> FuncList;
class MessageDispatcher
{
public:
	MessageDispatcher();
	~MessageDispatcher();
	void Init();
	void DispatcherMsg(WorldPacket& msg, RSession* session);
private:
	void RegistHandler(uint32 opCodeId, Func handlerFunc);

	static void HandlePackKeyNotify(WorldPacket& msg, RSession* session);
	static void HandleQueuingRequestAck(WorldPacket& msg, RSession* session);
	static void HandleAuthAck(WorldPacket& msg, RSession* session);
	static void HandleRoleListAck(WorldPacket& msg, RSession* session);
	static void HandleSelectRoleAck(WorldPacket& msg, RSession* session);
	static void HandleCreateRoleNtf(WorldPacket& msg, RSession* session);

	static void HandleRoleInitMeNtf(WorldPacket& msg, RSession* session);
	static void HandleRoleInitMeEnd(WorldPacket& msg, RSession* session);

	static void HandleErrorMsg(WorldPacket& msg, RSession* session);
	static void HandleOutLine(WorldPacket& msg, RSession* session);
	static void HandleForceOutLine(WorldPacket& msg, RSession* session);
protected:
	

	//static void HandleCheckPacket(WorldPacket& msg, RSession* session);
private:
	FuncList m_FuncList;
};

extern MessageDispatcher sMsgDispatcher;