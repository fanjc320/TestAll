#include "stdafx.h"

InstanceMgr sInsMgr;

void InstanceMgr::Load()
{
	
	LoadItemCfg();

	LoadQuestMainList();
	LoadQuestStepsList();
	LoadNpcsList();
	LoadMapPointList();
	LoadSceneMapList();
	LoadModleNameCfg();
}

ItemCfg* InstanceMgr::GetItemCfg(uint32 id)
{
	auto itr = mItemCfg.find(id);
	if (itr != mItemCfg.end()) return &itr->second;
	return NULL;
}

ItemTypeCfg* InstanceMgr::GetItemTypeCfg(uint32 id)
{
	auto itr = mItemTypeCfg.find(id);
	if (itr != mItemTypeCfg.end()) return &itr->second;
	return NULL;
}

void InstanceMgr::LoadItemTypeCfg()
{
	mItemTypeCfg.clear();
	JsonReader reader;

	reader.LoadFrom("table/ItemTypeCfg.json.txt");
	JsonValueReader valueReader = reader.GetValueReader();
	string actionIdList;
	// 获取每个节点
	for (int i = 0; i < reader.GetMemberCount(); i++)
	{
		ItemTypeCfg cfg = {};

		valueReader = reader.GetValueReader()[i];
		cfg.id = valueReader["id"].GetInt();
		cfg.pos1 = valueReader["position"].GetInt();
		cfg.pos2 = valueReader["position2"].GetInt();
		if (cfg.pos1 > 0 || cfg.pos2 > 0) {
			cfg.isEqu = true;
		}
		mItemTypeCfg[cfg.id] = cfg;
	}
}

void InstanceMgr::LoadItemCfg()
{
	LoadItemTypeCfg();
	mItemCfg.clear();
	JsonReader reader;
	JsonValueReader valueReader = reader.GetValueReader();
	reader.LoadFrom("table/ItemCfg.json.txt");
	uint32 count = reader.GetMemberCount();
	for (int i = 0; i < (int32)count; i++)
	{
		ItemCfg cfg = {};
		valueReader = reader.GetValueReader()[i];
		cfg.id = valueReader["id"].GetInt();
		cfg.type = valueReader["type"].GetInt();
		mItemCfg[cfg.id] = cfg;
	}
}


void InstanceMgr::LoadQuestStepsList()
{
	//m_MapQuestStepsList.clear();
	//m_json.LoadJsonFile("./table/TaskStepCfg.json.txt");
	//string strMonsterlist = "";
	//std::vector<std::string> lstStr1;
	//std::vector<std::string> lstStr2;

	//uint32 aNub = 0, aNub2 = 0, aType = 0;
	//QuestStepBase QuestStepB;
	//m_json.GetJsonCount(aNub);
	//for (uint32 i = 0; i < aNub; i++)
	//{
	//	m_json.GetJsonCount(i, aNub2);
	//	for (uint32 j = 0; j < aNub2; j++)
	//	{
	//		QuestStepB.monIds.clear();

	//		m_json.GetJsonValueByIndex(i, j, "id", QuestStepB.id);
	//		m_json.GetJsonValueByIndex(i, j, "stepId", QuestStepB.stepId);
	//		m_json.GetJsonValueByIndex(i, j, "type", aType);
	//		QuestStepB.type = QuestStepType(aType);
	//		m_json.GetJsonValueByIndex(i, j, "para1", QuestStepB.para1);
	//		m_json.GetJsonValueByIndex(i, j, "para2", QuestStepB.para2);
	//		m_json.GetJsonValueByIndex(i, j, "para3", QuestStepB.para3);
	//		m_json.GetJsonValueByIndex(i, j, "para4", QuestStepB.para4);
	//		m_json.GetJsonValueByIndex(i, j, "para5", QuestStepB.para5);
	//		m_json.GetJsonValueByIndex(i, j, "para6", QuestStepB.para6);

	//		if (aType == QuestStepType::QStepHit || aType == QuestStepType::QStepHitByMap || aType == QuestStepType::QMazeHitCount)
	//		{
	//			QuestStepB.uncount = QuestStepB.para2;
	//			m_json.GetJsonValueByIndex(i, j, "monsterlist", strMonsterlist);
	//			lstStr1 = StrSplit(strMonsterlist, ";");

	//			if (lstStr1.size() <= 0 && aType != QuestStepType::QStepHitByMap) // 此种玩法不需要此约束性检查
	//				sLog.outError("LoadQuestStepsList", "TaskStepCfg.json.txt monsterlist <= 0");

	//			if (QuestStepB.uncount == 0 && lstStr1.size() > 3)
	//				sLog.outError("LoadQuestStepsList", "TaskStepCfg.json.txt uncount == 0 && monsterlist > 3");

	//			for (auto strItem : lstStr1)
	//			{
	//				QuestMonCountInfo aQuestMonCountInfo;
	//				lstStr2 = StrSplit(strItem, ",");
	//				if (lstStr2.size() != 2)
	//				{
	//					sLog.outError("LoadQuestStepsList", "TaskStepCfg.json.txt monsterlist error");
	//					continue;
	//				}

	//				aQuestMonCountInfo.name = lstStr2[0];
	//				aQuestMonCountInfo.count = strtouint32(lstStr2[1].c_str());
	//				QuestStepB.monIds.push_back(aQuestMonCountInfo);
	//			}
	//		}

	//		m_json.GetJsonValueByIndex(i, j, "sendItemId", QuestStepB.sendItemId);
	//		m_json.GetJsonValueByIndex(i, j, "sendItemNum", QuestStepB.sendItemNum);
	//		m_json.GetJsonValueByIndex(i, j, "recycleItemId", QuestStepB.recycleItemId);
	//		m_json.GetJsonValueByIndex(i, j, "recycleItemNum", QuestStepB.recycleItemNum);
	//		m_json.GetJsonValueByIndex(i, j, "limitTime", QuestStepB.limitTime);
	//		m_json.GetJsonValueByIndex(i, j, "StepPrize", QuestStepB.StepPrize);

	//		m_json.GetJsonValueByIndex(i, j, "objectNpc", QuestStepB.objectNpc);

	//		
	//		//if (m_MapQuestStepsList.find(QuestStepB.id) == m_MapQuestStepsList.end())
	//		//{
	//		MapQuestSteps& instaRef = m_MapQuestStepsList[QuestStepB.id];
	//		if (instaRef.find(QuestStepB.stepId) == instaRef.end())
	//			instaRef[QuestStepB.stepId] = QuestStepB;
	//		else
	//			sLog.outError("ERRCON", "TaskStepCfg %d,%d", QuestStepB.id, QuestStepB.stepId);
	//		//}

	//	}
	//}
}

void InstanceMgr::LoadQuestMainList()
{
	string str;
	uint32 aNub = 0, aNub2 = 0, aType = 0;
	QuestMain QuestM;
	m_QuestMainList.clear();


	JsonReader reader;
	JsonValueReader valueReader = reader.GetValueReader();
	reader.LoadFrom("table/TaskCfg.json.txt");
	uint32 count = reader.GetMemberCount();
	for (int i = 0; (uint32)i < count; i++)
	{

		valueReader = reader.GetValueReader()[i];
		QuestM = { 0 };
		QuestM.NextIds.clear();

		QuestM.id = valueReader["id"].GetUint();
		QuestM.preId = valueReader["preId"].GetUint();
		QuestM.allowLv = valueReader["allowLv"].GetUint();
		QuestM.name = valueReader["name"].GetString();
		str = valueReader["allowJob"].GetString();
		uint32 value = 0;
		sscanf(str.c_str(), "%u", &value);
		QuestM.allowJob = value;

		QuestM.type = (QuestType)valueReader["type"].GetUint();
		QuestM.activityID = valueReader["activityID"].GetUint();
		QuestM.isDynamicNpc = valueReader["isDynamicNpc"].GetUint();
		QuestM.countType = valueReader["countType"].GetUint();
		QuestM.count = valueReader["count"].GetUint();
		QuestM.limitTime = valueReader["limitTime"].GetUint();
		QuestM.prizeId = valueReader["prizeId"].GetUint();
		QuestM.CanGiveUp = valueReader["isGiveup"].GetUint();
		QuestM.npcId = valueReader["npcId"].GetUint();
		QuestM.autoGet = valueReader["autoGet"].GetBool();
		QuestM.nextTaskID = valueReader["nextId"].GetUint();//下一个任务ID

		JsonValueReader dats = valueReader.ForceGetValueReader("nextTask");
		if (dats.IsValid()) {
			uint32 count = dats.GetCount();
			for (uint32 j = 0; j < count; j++)
			{
				QuestM.NextIds.push_back(dats[j].GetUint());
			}
		};
		m_QuestMainList[QuestM.id] = QuestM;
	/*	vector<uint32> &idlist = m_QuestIdByType[aType];
		idlist.push_back(QuestM.id);*/
	}
	////获取循环任务编号
	//GetQuestMain_LoopTypeData();
	//GetQuestMain_ShiLianLoopTypeData();
	//GetQuestMain_DaZongGuanLoopTypeData();
}



void InstanceMgr::LoadMapPointList()
{

	for (uint32 i = 0; i < 1000; i++)
	{
		MapPtList& instaRef = m_MapPointList[i];
		instaRef.clear();
	}

	JsonReader reader;
	JsonValueReader valueReader = reader.GetValueReader();
	reader.LoadFrom("table/ScenePointCfg.json.txt");
	uint32 count = reader.GetMemberCount();
	for (int i = 0; (uint32)i < count; i++)
	{
		valueReader = reader.GetValueReader()[i];
		MapPointInfo ptinf;
		ptinf.id = valueReader["id"].GetUint();
		ptinf.mapId = valueReader["mapId"].GetUint();
		ptinf.x = valueReader["pt1x"].GetUint();
		ptinf.y = valueReader["pt1y"].GetUint();
		ptinf.dest = valueReader["dest"].GetUint();
		MapPtList& instaNpc = m_MapPointList[ptinf.mapId];
		instaNpc.push_back(ptinf);
	}
}

void InstanceMgr::LoadSceneMapList()
{
	m_sceneMapList.clear();
	JsonReader reader;
	JsonValueReader valueReader = reader.GetValueReader();
	reader.LoadFrom("table/SceneCfg.json.txt");
	uint32 count = reader.GetMemberCount();
	for (uint32 i = 0; i < count; i++)
	{
		valueReader = reader.GetValueReader()[i];
		SceneData info = {};
		info.id = valueReader["id"].GetUint();
		info.sceneMapName = valueReader["sceneMapName"].GetString();
		m_sceneMapList[info.id] = info;
	}
}

void InstanceMgr::LoadModleNameCfg()
{
	mMapModleCfg.clear();
	JsonReader reader;
	JsonValueReader valueReader = reader.GetValueReader();
	reader.LoadFrom("table/ModelNameCfg.json.txt");
	uint32 count = reader.GetMemberCount();
	for (uint32 i = 0; i < count; i++)
	{
		valueReader = reader.GetValueReader()[i];
		ModleCfg info = {};
		info.id = valueReader["id"].GetUint();
		info.headId = valueReader["head"].GetUint();
		mMapModleCfg[info.id] = info;
	}
}

NpcInfo * InstanceMgr::GetNpcById(uint32 id)
{
	for (uint32 i = 0; i < 1000; i++)
	{
		NpcList *aNpcs = &m_NpcList[i];
		if (aNpcs->size() > 0)
		{
			NpcList::iterator itr;
			itr = aNpcs->find(id);
			if (itr != aNpcs->end())
			{
				return  &itr->second;
			}
		}
	}
	return NULL;
}


void InstanceMgr::LoadNpcsList()
{
	/*for (uint32 i = 0; i < 1000; i++)
	{
		NpcList& instaRef = m_NpcList[i];
		instaRef.clear();
	}
	m_json.LoadJsonFile("table/NpcCfg.json.txt");
	string str;
	uint32 aNub;
	Field field;
	m_json.GetJsonCount(aNub);
	uint32 job = -1;

	for (uint32 i = 0; i < aNub; i++)
	{
		NpcInfo npcI;
		if (!m_json.GetJsonValueByIndex(i, "id", npcI.id))				sLog.outError("LoadMonsList", "error on load id!");
		if (!m_json.GetJsonValueByIndex(i, "icon", npcI.icon))				sLog.outError("LoadMonsList", "error on load icon!");
		if (!m_json.GetJsonValueByIndex(i, "name", npcI.name))			sLog.outError("LoadMonsList", "error on load name!");
		if (!m_json.GetJsonValueByIndex(i, "model", npcI.model))			sLog.outError("LoadMonsList", "error on load model!");
		if (!m_json.GetJsonValueByIndex(i, "mapId", npcI.mapId))				sLog.outError("LoadMonsList", "error on load lv!");
		if (!m_json.GetJsonValueByIndex(i, "x", npcI.x))				sLog.outError("LoadMonsList", "error on load hp!");
		if (!m_json.GetJsonValueByIndex(i, "y", npcI.y))				sLog.outError("LoadMonsList", "error on load mp!");
		if (!m_json.GetJsonValueByIndex(i, "type", npcI.type))				sLog.outError("LoadMonsList", "error on load mp!");
		if (!m_json.GetJsonValueByIndex(i, "script", npcI.script))				sLog.outError("LoadMonsList", "error on load mp!");
		if (!m_json.GetJsonValueByIndex(i, "isPrivate", npcI.isPrivate))				sLog.outError("LoadNpcStaticList", "error on load mp!");
		std::string talks;
		if (!m_json.GetJsonValueByIndex(i, "npcTalk", talks))				sLog.outError("LoadNpcStaticList", "error on load mp!");
		npcI.npcTalks = StrSplit(talks, "|");
		if (!m_json.GetJsonValueByIndex(i, "isDynamicNpc", npcI.isDynamicNpc))				sLog.outError("LoadNpcStaticList", "error on load mp!");
		if (!m_json.GetJsonValueByIndex(i, "dynamicPara", npcI.dynamicPara))				sLog.outError("LoadNpcStaticList", "error on load mp!");
		if (!m_json.GetJsonValueByIndex(i, "direct", npcI.direct))				sLog.outError("LoadNpcStaticList", "error on load mp!");
		if (!m_json.GetJsonValueByIndex(i, "job", npcI.job))				sLog.outError("LoadNpcStaticList", "error on load job!");
		NpcList& instaNpc = m_NpcList[npcI.mapId];
		instaNpc[npcI.id] = npcI;
	}*/
}

QuestStepBase * InstanceMgr::GetQuestStep(uint32 Id, uint32 astepId)
{
	auto itr = m_MapQuestStepsList.find(Id);
	if (itr == m_MapQuestStepsList.end()) return false;

	MapQuestSteps& steps = itr->second;
	auto stpItr = steps.find(astepId);
	if (stpItr != steps.end())
	{
		return &( stpItr->second);
	}
	return NULL;
}

QuestMain * InstanceMgr::GetQuestMain(uint32 Id)
 {
	 MapQuestMainList::iterator itr;
	 itr = m_QuestMainList.find(Id);
	 if (itr != m_QuestMainList.end())
	 {
		 return &(itr->second);
	 }
	 return NULL;
 }

MapPointInfo* InstanceMgr::GetMapPoint(uint32 MapId)
{
	if (MapId >= 1000)
		return NULL;
	MapPtList& instaNpc = m_MapPointList[MapId];
	if (instaNpc.size() > 0)
	{
		if (instaNpc.size()==1)
		   return	&instaNpc[0];

		uint32 pos=RandBetween1(0, instaNpc.size());
		if (instaNpc.size() > pos)
			return	&instaNpc[pos];
		return	&instaNpc[0];
	}
	return NULL;
}

string InstanceMgr::GetMapNameById(uint32 id)
{
	auto iter = m_sceneMapList.find(id);
	if (iter != m_sceneMapList.end()) {
		return iter->second.sceneMapName;
	}
	return "";
}

ModleCfg* InstanceMgr::GetModleCfg(uint32 id)
{
	auto itr = mMapModleCfg.find(id);
	if (itr != mMapModleCfg.end()) {
		return &itr->second;
	}
	return NULL;
}
