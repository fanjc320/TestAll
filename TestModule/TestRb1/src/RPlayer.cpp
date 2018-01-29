#include "stdafx.h"

RPlayer::RPlayer(uint32 instanceId, PlayerInfo& playInfo, RSession* session)
	:m_instanceId(instanceId),
	m_playInfo(playInfo),
	m_session(session)/*,
	m_location(this),
	m_teamMgr(this)*/
{
	//m_timeWave = rand() % sStressCfg.GetRobotCfg()->moveWave;
}

RPlayer::RPlayer()
{

}

RPlayer::~RPlayer()
{
}

void RPlayer::Update(uint32 ticket)
{

}

void RPlayer::Init()
{

}

void RPlayer::SetServerInstanceId(uint64 serverInstanceId)
{

}
