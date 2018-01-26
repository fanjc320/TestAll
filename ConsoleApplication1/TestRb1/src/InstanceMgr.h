#pragma once




struct ExchangeItemInfo
{
	uint16 idx;
	uint8  type;
	uint32 id;

	uint16 firstType;
	uint16 secondType;
	uint16 thirdType;
	uint8 sellable;	//是否可寄售，0为不可寄售
	uint32 price;
	uint32 lowerPrice;
	uint32 uperPrice;
	uint32 bottomPrice;
	uint32 topPrice;
	uint32 showTime;	//为0则不需要公示，秒
	uint32	currencyType;	//货币类型
};



struct ItemTypeCfg
{
	uint32 id;
	uint32 pos1;
	uint32 pos2;
	bool isEqu = false;
};

struct ItemCfg
{
	uint32 id;
	uint32 type;
};

struct ModleCfg
{
	uint32 id;
	uint32 headId;
};


enum QuestType {
	QTeach = 10,			// 教学任务
	QMain = 20,				// 主线任务
	QDaily = 30,			// 每日任务
	QBranch = 40,			// 支线任务
	QZhenZhong = 50,		// 真中任务模式
	QLoop = 60,				// 环任务
	QShiLian = 70,			// 冒险者试练
	QJiaZu = 80,			// 家族任务
	QUndead = 90,			// 亡灵的骚动
	QJobJinJie = 100,		// 职业进阶
	Qmine = 120,			// 采矿活动任务
	QKing = 130,			// 国王委托
	QDoubleTeam = 140,		// 流星山丘（双人男女搭配任务）
	QZhiYeGongHui = 150,	// 职业公会
	QJobBranch = 160,		// 职业分支任务
	QQiYu = 180,			// 奇遇任务
	QPartnerJobLv = 200,	// 职业分支任务
	QKnightTask = 210,		// 骑士日常
	QWeekTask = 220			// 周常任务
};

enum TeamType {
	TeamMain = 1,      //主线任务
	TeamZhenZhong = 2, //未找到任务或者遇到错误
	TeamDaily = 3,     //每日任务
};

enum TeamBy : unsigned char {
	Normal = 1,			//普通组队
	Knight = 2,			//骑士团组队
};

enum QuestStepType {
	QStepTalk = 1,   //对话
	QStepBattle = 2, //战斗
	QStepCollect = 3, //采集
	QStepBuy = 4,     //购买道具
	QStepPaid = 5,      //上缴
	QStepPatrol = 6,    //巡逻
	QStepHit = 7,       //打怪计数  
	QStepSprite = 9,    //脚本任务
	QStepADDSKill = 10, //学习技能完成任务
	QStepMining = 11,	//采矿
	QAnswer = 12,	    //答题模式任务
	QAnimation = 13,    //脚本动画模式
	QGuide = 14,        //活动引导模式
	QStepJobBranch = 15,		// 选择职业分支任务模式
	QItemHave = 16,	    // 背包里有道具（装备，和物品都可以）
	QItemTakeOn = 17,	// 穿戴（装备表）
	QItemUse = 18,	// 使用道具（装备，和物品都可以）
	QMoveBattle = 19, //寻路遇怪战斗
	QOpenDig = 20, //打开面板(客户端检测)
	QMoney = 21, //金币检测
	QStepHitByMap = 22,       //打怪计数(特定地图打怪计数) 
	QBattleCount = 23,		  //战斗场次计数类型
	QMazeHitCount = 24,		  //迷宫打怪计数
};


struct QuestMain {
	uint32 id;
	uint32 preId;
	uint32 allowLv;
	uint32 allowJob;
	QuestType type;
	uint32 activityID;
	uint32 count;
	uint32 countType;
	uint32 limitTime;
	uint32 prizeId;
	uint32 npcId;
	uint32 isDynamicNpc;
	uint32 CanGiveUp;
	std::vector<uint32> NextIds;
	bool autoGet;
	std::string name;
	uint32 nextTaskID; //下一个任务ID
};

struct QuestMonCountInfo
{
	std::string name;
	uint32 count;
};

struct QuestStepBase
{
	uint32 id;			//任务ID
	uint32 stepId;	    //环节
	QuestStepType type;		//环节类型
	uint32 para1;
	uint32 para2;
	uint32 para3;
	uint32 para4;
	uint32 para5;
	string para6;

	std::vector<QuestMonCountInfo> monIds;
	uint32 uncount;					// 非0时 monIds怪物之和为0时各QuestMonCountInfo 计数达到

	uint32 sendItemId;
	uint32 sendItemNum;
	uint32 recycleItemId;
	uint32 recycleItemNum;
	uint32 limitTime;	//环节限时
	uint32 StepPrize;
	uint32 objectNpc = 0;
	bool isComboBattle = false;
};


struct QuestFinish
{
	uint32 Finishtime;  //完成时间
	uint32 FinishNub;   //完成次数
	QuestMain QuestM;
};

struct Quest
{
	QuestStepBase QuestStep;
	uint32 Taskprogress1;
	uint32 Taskprogress2;
	uint32 Taskprogress3;
	bool isfinish;
};

struct QuestWillGet
{
	QuestStepBase QuestStep;
	uint32 Tim;
	uint32 Type;
	uint32 data;
};


struct QuestRewardBase
{
	uint32 groupId;
	uint32 id;
	uint32 weight;
	uint32 prizeType;
	uint32 prizeId;
	uint32 prizeNum;
	uint32 prizeJob = 0;
	uint32 lv_min = 0;
	uint32 lv_max = 0;
	uint8  bind = 0;  //物品是否绑定
};

struct QuestRewardList
{
	vector<QuestRewardBase>  QuestRewards;
};

struct NpcInfo {
	uint32 id = 0;
	std::string name;
	uint32 stand;
	uint32 model;
	uint32 icon;
	uint32 mapId;
	uint32 x;
	uint32 y;
	uint32 direct;
	uint32 type;
	//uint32 fun1;
	//uint32 fun2;
	uint32 isPrivate;
	std::vector<std::string> npcTalks;
	std::string  script;
	uint32 isDynamicNpc;
	uint32 dynamicPara;
	int32 job;
	std::string GetRandTalk()
	{
		if (npcTalks.size() == 0)
			return "";
		int32 i = rand() % npcTalks.size();
		return npcTalks[i];
	}
	uint8 GetRandId()
	{
		size_t tSize = npcTalks.size();
		if (0 == tSize)
		{
			return 0;
		}
		return (uint8)(rand() % tSize);
	}
	std::string GetTalkById(uint8 id)
	{
		size_t tSize = npcTalks.size();
		if (0 == tSize || id >= (uint8)tSize)
			return "";
		return npcTalks[id];
	}

	bool IsMonster(void)
	{
		return type == (uint32)ObjectType::Monnpc || type == (uint32)ObjectType::MapBoss || type == (uint32)ObjectType::ElementMonst;
	}
};

struct MapPointInfo {
	uint32 id = 0;
	uint16 mapId=0;
	uint16 x = 0;
	uint16 y = 0;
	uint32 dest = 0;
};


struct SceneData
{
	uint32 id = 0;
	string name;
	string sceneMapName;
	MapType type = NormalMap;
	uint32 maxnumber = 0;
	uint32 timetype = 0;
	string time;
	uint32 startH = 0;
	uint32 startS = 0;
	uint32 endH = 0;
	uint32 endS = 0;

	uint32 SealLv = 0;
	uint32 SealTaskId = 0;
	uint32 SeaItemId = 0;
	uint32 SeaTitleId = 0;
	uint32 UnsealPrize = 0;
	std::string SealHint;
	uint32 AutoRecover = 1;
	bool PK_Disabled = false;
	uint32 guaji = 0;
};

typedef unordered_map<uint32, QuestStepBase> MapQuestSteps;
typedef unordered_map<uint32, MapQuestSteps> MapQuestStepsList;
typedef unordered_map<uint32, QuestMain> MapQuestMainList;
typedef unordered_map<uint32, NpcInfo> NpcList;
typedef unordered_map<uint32, SceneData> SceneMapList;
typedef vector<MapPointInfo> MapPtList;

class InstanceMgr 
{
public:
	void Load();
	 
	ItemCfg* GetItemCfg(uint32 id);
	ItemTypeCfg* GetItemTypeCfg(uint32 id);
	NpcInfo * GetNpcById(uint32 id);
	QuestStepBase * GetQuestStep(uint32 Id, uint32 astepId);
	QuestMain* GetQuestMain(uint32 Id);
	MapPointInfo* GetMapPoint(uint32 MapId);
	string GetMapNameById(uint32 id);
	ModleCfg* GetModleCfg(uint32 id);
protected:
	void LoadItemTypeCfg();
	void LoadItemCfg();
	void LoadQuestMainList();
	void LoadQuestStepsList();
	void LoadNpcsList();

	void LoadMapPointList();
	void LoadSceneMapList();

	void LoadModleNameCfg();

protected:
	//JsonBase m_json;
	std::map<uint32, ExchangeItemInfo> itemCfg;
	std::map<uint32, ExchangeItemInfo> equipmentCfg;
	std::map<uint32, ExchangeItemInfo> petCfg;

	std::map<uint32, ItemTypeCfg> mItemTypeCfg;
	std::map<uint32, ItemCfg> mItemCfg;
	std::map<uint32, ModleCfg> mMapModleCfg;

	MapQuestMainList m_QuestMainList;
	MapQuestStepsList m_MapQuestStepsList;
	NpcList   m_NpcList[1000];
	MapPtList   m_MapPointList[1000];
	SceneMapList m_sceneMapList;
};

extern InstanceMgr sInsMgr;