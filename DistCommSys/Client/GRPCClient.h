#pragma once

#include "Client/FileTran/FileTranClientImpl.h"
#include "Client/MsgTran/MsgTranClientImpl.h"
#include "Client/NetConfig/NetConfigClientImpl.h"
#include "Client/NetDirectory/NetDirectoryClientImpl.h"
#include "Client/NetWaterMark/NetWaterMarkClientImpl.h"

class CGRPCChannel;

class CFileTranClientCarry;
class CFileTranClientData;

class CMsgTranClientCarry;
class CMsgTranClientData;

class CNetConfigClientCarry;
class CNetConfigClientData;

class CNetDirectoryClientCarry;
class CNetDirectoryClientData;

class CNetWaterMarkClientCarry;
class CNetWaterMarkClientData;

class CGRPCClient final
{
public:
	CGRPCClient();
	~CGRPCClient();

public:
	bool Init(const string &certServer,
		const string &certClient,
		const string &keyClient);

public:
	CFileTranClientImpl & GetFileTran();
	CMsgTranClientImpl & GetMsgTran();
	CNetConfigClientImpl & GetNetConfig();
	CNetDirectoryClientImpl & GetNetDirectory();
	CNetWaterMarkClientImpl & GetNetWaterMark();

private:
	CGRPCChannel *m_Channel;

	CFileTranClientCarry *m_FileTranCarry;
	CFileTranClientData *m_FileTranData;
	CFileTranClientImpl *m_FileTranImpl;

	CMsgTranClientCarry *m_MsgTranCarry;
	CMsgTranClientData *m_MsgTranData;
	CMsgTranClientImpl *m_MsgTranImpl;

	CNetConfigClientCarry *m_NetConfigCarry;
	CNetConfigClientData *m_NetConfigData;
	CNetConfigClientImpl *m_NetConfigImpl;

	CNetDirectoryClientCarry *m_NetDirectoryCarry;
	CNetDirectoryClientData *m_NetDirectoryData;
	CNetDirectoryClientImpl *m_NetDirectoryImpl;

	CNetWaterMarkClientCarry *m_NetWaterMarkCarry;
	CNetWaterMarkClientData *m_NetWaterMarkData;
	CNetWaterMarkClientImpl *m_NetWaterMarkImpl;
};
