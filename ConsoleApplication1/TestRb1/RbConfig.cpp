#include "stdafx.h"
#include "RbConfig.h"
createFileSingleton(StressCfg);


static const char* map_config_file = "map/*.bytes";

StressCfg::StressCfg()
{
	m_worldCfg = {};
	m_robotCfg = {};
}

StressCfg::~StressCfg()
{
}

bool StressCfg::LoadCfg()
{
	LoadBaseCfg();
	/*if (!LoacMapCfg()) {
		sLog.outError("Config", "--$LoadMapCfg Error!");
		return false;
	}*/
	//Map* mapS = new Map();
	//if (mapS->LoadFromFile() == false)
	//{
	//	return false;
	//}
	//mapS->Init();
	//LoadOpenId();
	return true;
}

void StressCfg::LoadBaseCfg()
{
	m_worldCfg.maxRobotCount = Config.MainConfig.GetIntDefault("WorldConfig", "MaxRobotCount", 1);
	m_worldCfg.beginAcctNameId = Config.MainConfig.GetIntDefault("WorldConfig", "BeginAccNameID", 1);
	m_worldCfg.maxNumberOfLink = Config.MainConfig.GetIntDefault("WorldConfig", "MaxNumberOfLink", 10);
	m_worldCfg.linkSpace = Config.MainConfig.GetIntDefault("WorldConfig", "LinkSpace", 2000);

	m_robotCfg.ableToReconnection = (Config.MainConfig.GetIntDefault("RobotConfig", "AbleToReconnection", 1) == 1) ? true : false;
	m_robotCfg.reconnectionSpace = Config.MainConfig.GetIntDefault("RobotConfig", "ReconnectionSpace", 15);
	m_robotCfg.moveSpace = Config.MainConfig.GetIntDefault("RobotConfig", "MoveSpace", 500);
	m_robotCfg.moveWave = Config.MainConfig.GetIntDefault("RobotConfig", "MoveWave", 500);
	m_robotCfg.sendMoveSpace = Config.MainConfig.GetIntDefault("RobotConfig", "SendMoveSpace", 500);


	m_destinateMapId = Config.MainConfig.GetIntDefault("StressMap", "MapID", 1);

	/*聊天配置*/
	m_robotSpeakCfg.ableSpeak = (Config.MainConfig.GetIntDefault("RobotSpeak", "isspeak", 0) == 1) ? true : false;
	m_robotSpeakCfg.speakchannel = Config.MainConfig.GetIntDefault("RobotSpeak", "speakchannel", 0);
	m_robotSpeakCfg.speakSpeed = Config.MainConfig.GetIntDefault("RobotSpeak", "speakspeed", 5000);
	m_robotSpeakCfg.speakContent = Config.MainConfig.GetStringDefault("RobotSpeak", "speakcontent", "I am a robot!");

	/*副本配置*/
	m_robotCopyCfg.ableEnterCopy = (Config.MainConfig.GetIntDefault("RobotCopyMap", "IsEnter", 0) >= 1) ? true : false;
	m_robotCopyCfg.mazeStyle = Config.MainConfig.GetIntDefault("RobotCopyMap", "EnterMazeStyle", 2);

	/*家族战配置*/
	m_robotGuildPvPCfg.ableEnterGuildPVP = (Config.MainConfig.GetIntDefault("RobotGuildPVP", "IsEnter", 0) >= 1) ? true : false;
	m_robotGuildPvPCfg.enterMaxPeople = Config.MainConfig.GetIntDefault("RobotGuildPVP", "EnterRobotCount", 1);
	m_robotGuildPvPCfg.maxGuildCount = Config.MainConfig.GetIntDefault("RobotGuildPVP", "MaxGuildCount", 100);
	m_robotGuildPvPCfg.ableActRepeat = (Config.MainConfig.GetIntDefault("RobotGuildPVP", "AbleRepeat", 0) >= 1) ? true : false;

	/*压力上报配置*/
	m_robotReportCfg.ablePerforReport = (Config.MainConfig.GetIntDefault("RobotReport", "IsReport", 0) >= 1) ? true : false;
	m_robotReportCfg.showPerforReport = (Config.MainConfig.GetIntDefault("RobotReport", "showReport", 0) >= 1) ? true : false;
	m_robotReportCfg.checkPacket = Config.MainConfig.GetIntDefault("RobotReport", "checkPacket", 5000);

	/*sPerforReport.mUrl = Config.MainConfig.GetStringDefault("RobotReport", "url", "");
	sPerforReport.mProCode = Config.MainConfig.GetStringDefault("RobotReport", "proCode", "");
	sPerforReport.mHost = Config.MainConfig.GetStringDefault("RobotReport", "host", "");
	sPerforReport.mPort = Config.MainConfig.GetIntDefault("RobotReport", "port", 80);*/

	/*任务配置*/
	m_robotQuestCfg.ableQuest = (Config.MainConfig.GetIntDefault("RobotQuest", "isQuest", 0) >= 1) ? true : false;
	m_robotQuestCfg.questId = Config.MainConfig.GetIntDefault("RobotQuest", "BeginQuestId", 0);
	m_robotQuestCfg.questStepId = Config.MainConfig.GetIntDefault("RobotQuest", "BeginQuestStepId", 0);

	/*组队配置*/
	m_robotTeamCfg.ableTeam = (Config.MainConfig.GetIntDefault("RobotTeam", "isTeam", 0) >= 1) ? true : false;

	/*商店配置*/
	m_RobotShopCfg.isShop = (Config.MainConfig.GetIntDefault("RobotShop", "isShop", 0) >= 1) ? true : false;
	m_RobotShopCfg.ticket = Config.MainConfig.GetIntDefault("RobotShop", "ticket", 10000);

	/*服务器机器人配置*/
	m_ServerRobotCfg.isTeam = (Config.MainConfig.GetIntDefault("RobotRobot", "isopen", 0) >= 1) ? true : false;
	m_ServerRobotCfg.teamNum = Config.MainConfig.GetIntDefault("RobotRobot", "teamnum", 4);
}

BOOL ParseParaString(std::vector<std::string>& vectString, const char* buf, int len, char chSeparator)
{
	if (buf == NULL)
	{
		return FALSE;
	}
	vectString.clear();

	const char* pStart = buf;
	const char* pEnd = NULL;
	std::string str;

	while (true)
	{
		pEnd = (const char*)memchr(pStart, chSeparator, buf + len - pStart);
		if (pEnd >= pStart)
		{
			str.assign(pStart, pEnd);
			vectString.push_back(str);
		}
		else
		{
			str.assign(pStart, buf + len);
			vectString.push_back(str);
			break;
		}
		pStart = pEnd + 1;
	}
	return TRUE;
}
bool StressCfg::LoacMapCfg()
{
	return true;
	char fileName[256] = { 0 };
	sprintf_s(fileName, 256, "%s", map_config_file);
	vector<string> fileVec;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(fileName, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return false;
	}
	else
	{
		fileVec.push_back(FindFileData.cFileName);

		while (0 != FindNextFile(hFind, &FindFileData))
		{
			fileVec.push_back(FindFileData.cFileName);
		}
		FindClose(hFind);
	}
	for (vector<string>::iterator itr = fileVec.begin(); itr != fileVec.end(); itr++)
	{
		vector<string> spliteVec;
		string mapName = (*itr);
		ParseParaString(spliteVec, mapName.c_str(), mapName.length(), '_');
		string id = spliteVec[0];
		uint32 mapId = strtouint32(id.c_str());
		/*临时400以上地图转换id*/
		mapId = ConvertMapId(mapId);
		m_mapIdToNameCfg[mapId] = (*itr);
	}
	return true;
}

uint32 StressCfg::ConvertMapId(uint32 originalMapId)
{
	if (originalMapId > 400) {
		//地图id对应地形
		return originalMapId - 290;
	}
	if (originalMapId == 49) {
		//临时家族战地图
		return 73;
	}
	return originalMapId;
}
string StressCfg::GetMapNameByID(uint32 id)
{
	MapNameCfg::iterator itr = m_mapIdToNameCfg.find(id);
	if (itr != m_mapIdToNameCfg.end())
	{
		return itr->second;
	}
	return "";
}

bool StressCfg::GetMapInfo(uint32 mapId, MapInfo& mapInfo, vector<Coordinate>& walkCoord)
{
	//string mapfile = sStressCfg.GetMapNameByID(mapId);sInsMgr
	//string mapfile = sInsMgr.GetMapNameById(mapId);
	//if (mapfile == "") {
	//	sLog.outError("LoadMap Config", "Map File Name is Null! map id:%d", mapId);
	//	return false;
	//}
	//char buf[256];
	//sprintf(buf, "%s%s.bytes", "map/", mapfile.c_str());
	//string filename(buf);
	//ifstream fs;
	//filename = StringToANSI(filename.c_str());
	//fs.open(filename, ios_base::in | ios_base::binary);
	//// 读取地图头
	//fs.read((char*)&mapInfo, sizeof(MapInfo));
	//if (mapInfo.cellCount > 0)
	//{
	//	// 读取格子信息
	//	CellInfo *cells = new CellInfo[mapInfo.cellCount];
	//	fs.read((char*)cells, sizeof(CellInfo)* mapInfo.cellCount);

	//	walkCoord.clear();
	//	for (int i = 0; i < mapInfo.cellCount; i++)
	//	{
	//		if (cells[i].attr & CellInfo::CellMask_Walkable)
	//		{
	//			Coordinate coord;
	//			coord.x = cells[i].x;
	//			coord.y = cells[i].y;
	//			walkCoord.push_back(coord);
	//		}
	//	}
	//	delete[] cells;
	//}
	//else
	//{
	//	fs.close();
	//	return false;
	//}
	//fs.close();
	return true;
}


void StressCfg::LoadOpenId()
{
	string file = "openid.txt";
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 


	string s;
	while (getline(infile, s))
	{
		//cout << s << endl;
		m_openIdList.push_back(s);
	}
	infile.close();             //关闭文件输入流 
}
string StressCfg::GetOpenIdByIndex(uint32 index)
{
	uint32 curIndex = index - GetWorldCfg()->beginAcctNameId;
	if (m_openIdList.size() > curIndex) {
		return m_openIdList[curIndex];
	}
	return "";
}