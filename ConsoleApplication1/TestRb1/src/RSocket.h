#pragma once

static const uint32 SocketBuffSize = 126 * 1024;
static const uint32 MaxSokcetBuffSize = 8 * 1024;

class RSession;

class RSocket : public MessageSocket
{
public:
	friend class World;
	RSocket(SOCKET fd);
	~RSocket();
	virtual void OnMessage(WorldPacket* message);
	virtual void OnMessageError();
	virtual void OnConnect();
	virtual void OnDisconnect();
	virtual MessageBuilder* CreateMessageBuilder()
	{
		MessageBuilder* build = new DefaultMessageBuilder(this);		
		return build;
	}
	void BindSession(RSession* session);
	void UnBindSession() {
		m_sessionLock.lock();
		if (m_Session)
			m_Session = nullptr;
		m_sessionLock.unlock();
	}
private:
	mutex m_sessionLock;
	RSession* m_Session= nullptr;
};

