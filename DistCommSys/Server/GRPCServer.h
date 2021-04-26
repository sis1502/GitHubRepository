#pragma once

#include "PubUtil/BaseDef.h"

class CFileTranServerCarry;
class CFileTranServerData;
class CFileTranServerImpl;

class CMsgTranServerCarry;
class CMsgTranServerData;
class CMsgTranServerImpl;

class CNetConfigServerCarry;
class CNetConfigServerData;
class CNetConfigServerImpl;

class CNetDirectoryServerCarry;
class CNetDirectoryServerData;
class CNetDirectoryServerImpl;

class CNetWaterMarkServerCarry;
class CNetWaterMarkServerData;
class CNetWaterMarkServerImpl;

class CGRPCServer final
{
public:
	CGRPCServer(const string &ip,
		const unsigned int &port,
		const string &certClient,
		const string &certServer,
		const string &keyServer);
	~CGRPCServer();

public:
	bool Run();

public:
	bool Init();

private:
	CFileTranServerCarry *m_FileTranCarry;
	CFileTranServerData *m_FileTranData;
	CFileTranServerImpl *m_FileTranImpl;

	CMsgTranServerCarry *m_MsgTranCarry;
	CMsgTranServerData *m_MsgTranData;
	CMsgTranServerImpl *m_MsgTranImpl;

	CNetConfigServerCarry *m_NetConfigCarry;
	CNetConfigServerData *m_NetConfigData;
	CNetConfigServerImpl *m_NetConfigImpl;

	CNetDirectoryServerCarry *m_NetDirectoryCarry;
	CNetDirectoryServerData *m_NetDirectoryData;
	CNetDirectoryServerImpl *m_NetDirectoryImpl;

	CNetWaterMarkServerCarry *m_NetWaterMarkCarry;
	CNetWaterMarkServerData *m_NetWaterMarkData;
	CNetWaterMarkServerImpl *m_NetWaterMarkImpl;

private:
	string m_Conn;
	string m_ClientCert;
	string m_ServerCert;
	string m_ServerKey;
};

