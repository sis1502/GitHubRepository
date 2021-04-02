#include "Client/GRPCClient.h"

#include "Client/GRPCChannel.h"

#include "Client/FileTran/FileTranClientCarry.h"
#include "Client/FileTran/FileTranClientData.h"

#include "Client/MsgTran/MsgTranClientCarry.h"
#include "Client/MsgTran/MsgTranClientData.h"

#include "Client/NetConfig/NetConfigClientCarry.h"
#include "Client/NetConfig/NetConfigClientData.h"

#include "Client/NetDirectory/NetDirectoryClientCarry.h"
#include "Client/NetDirectory/NetDirectoryClientData.h"

#include "Client/NetWaterMark/NetWaterMarkClientCarry.h"
#include "Client/NetWaterMark/NetWaterMarkClientData.h"

CGRPCClient::
CGRPCClient()
{
	m_Channel = nullptr;
}

CGRPCClient::
~CGRPCClient()
{
	//...
}

bool 
CGRPCClient::
Init()
{
	m_Channel = new (nothrow)CGRPCChannel(2, 2, 3);
	if (!m_Channel)
	{
		return false;
	}

	//** FileTran�ӿ�
	m_FileTranCarry = new (nothrow)CFileTranClientCarry(m_Channel);
	m_FileTranData = new (nothrow)CFileTranClientData(m_FileTranCarry);
	m_FileTranImpl = new (nothrow)CFileTranClientImpl(m_FileTranData);

	//** MsgTran�ӿ�
	m_MsgTranCarry = new (nothrow)CMsgTranClientCarry(m_Channel);
	m_MsgTranData = new (nothrow)CMsgTranClientData(m_MsgTranCarry);
	m_MsgTranImpl = new (nothrow)CMsgTranClientImpl(m_MsgTranData);

	//** NetConfig�ӿ�
	m_NetConfigCarry = new (nothrow)CNetConfigClientCarry(m_Channel);
	m_NetConfigData = new (nothrow)CNetConfigClientData(m_NetConfigCarry);
	m_NetConfigImpl = new (nothrow)CNetConfigClientImpl(m_NetConfigData);

	//** NetDirectory�ӿ�
	m_NetDirectoryCarry = new (nothrow)CNetDirectoryClientCarry(m_Channel);
	m_NetDirectoryData = new (nothrow)CNetDirectoryClientData(m_NetDirectoryCarry);
	m_NetDirectoryImpl = new (nothrow)CNetDirectoryClientImpl(m_NetDirectoryData);

	//** NetDirectory�ӿ�
	m_NetWaterMarkCarry = new (nothrow)CNetWaterMarkClientCarry(m_Channel);
	m_NetWaterMarkData = new (nothrow)CNetWaterMarkClientData(m_NetWaterMarkCarry);
	m_NetWaterMarkImpl = new (nothrow)CNetWaterMarkClientImpl(m_NetWaterMarkData);

	cout << "�ͻ��˳�ʼ���ɹ�" << endl;

	return true;
}

CFileTranClientImpl &
CGRPCClient::
GetFileTran()
{
	return *m_FileTranImpl;
}

CMsgTranClientImpl &
CGRPCClient::
GetMsgTran()
{
	return *m_MsgTranImpl;
}

CNetConfigClientImpl &
CGRPCClient::
GetNetConfig()
{
	return *m_NetConfigImpl;
}

CNetDirectoryClientImpl &
CGRPCClient::
GetNetDirectory()
{
	return *m_NetDirectoryImpl;
}

CNetWaterMarkClientImpl &
CGRPCClient::
GetNetWaterMark()
{
	return *m_NetWaterMarkImpl;
}