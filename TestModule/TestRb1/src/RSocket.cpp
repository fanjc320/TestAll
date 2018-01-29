#include "stdafx.h"

RSocket::RSocket(SOCKET fd):MessageSocket(fd, SocketBuffSize, SocketBuffSize)
{
}


RSocket::~RSocket()
{
}
 

void RSocket::OnMessage(WorldPacket* message)
{
	m_sessionLock.lock();
	if (m_Session) {
		m_Session->QueneMsg(message);
	}
	else {
		delete message;
	}
	m_sessionLock.unlock();
}
void RSocket::OnMessageError()
{

}

void RSocket::OnConnect()
{

}

void RSocket::OnDisconnect()
{
	m_sessionLock.lock();
	if (m_Session) {
		m_Session->OnDisconnected();
		m_Session = nullptr;
	}
	m_sessionLock.unlock();
}

void RSocket::BindSession(RSession* session)
{
	m_sessionLock.lock();
	if (!m_Session)
		m_Session = session;
	m_sessionLock.unlock();
}