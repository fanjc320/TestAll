//#pragma once

#define Default_Config_File			"configs/StressConfig.conf"

//error
//class SERVER_DECL Master : public TestBase

class SERVER_DECL Master : public Singleton<Master>
{
public:
	Master();
	~Master();
	bool Run();
	static volatile bool m_stopEvent;
private:
	bool StartServer();
	bool StopServer();
	void Terminate();
	void InitializeLogger();
	bool LoadConfig();

	void InitializeNetLib();
	void _HookSignals();
	void _UnhookSignals();

	void MainThreadLoop();

	CmdDispatcher m_CmdDispatcher;
	thread* m_WorldThread = nullptr;

};

#define sMaster Master::getSingleton()