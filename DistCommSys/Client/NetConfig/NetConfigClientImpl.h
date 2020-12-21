#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CNetConfigClientData;

class CNetConfigClientImpl
{
public:
	CNetConfigClientImpl(CNetConfigClientData *p);
	~CNetConfigClientImpl();

public:
	int Load(const string &ip, const string &port,
		const HostChain &seqIpPort,
		const string &cfgFileName,
		string &cfgFileContent);

	int Save(const string &ip, const string &port,
		const HostChain &seqIpPort,
		const string &cfgFileName,
		const string &cfgFileContent);

private:
	CNetConfigClientData *m_Data;
};

