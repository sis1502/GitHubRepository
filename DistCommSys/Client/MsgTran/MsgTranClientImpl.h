#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CMsgTranClientData;

class CMsgTranClientImpl
{
public:
	CMsgTranClientImpl(CMsgTranClientData *p);
	~CMsgTranClientImpl();

public:
	int GetMessage(const string &ip, const string &port,
		const HostChain seqIpPort,
		st_MsgBlock &mb);

	int PutMessage(const string &ip, const string &port,
		const HostChain seqIpPort,
		const st_MsgBlock &mb);

private:
	CMsgTranClientData *m_Data;
};

