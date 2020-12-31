#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CNetConfigServerImpl final
{
public:
	CNetConfigServerImpl();
	~CNetConfigServerImpl();

public:
	int Load(const HostChain &seqIpPort,
		const string &cfgFileName,
		string &cfgFileContent,
		st_ExceptionError &ex);

	int Save(const HostChain &seqIpPort,
		const string &cfgFileName,
		const string &cfgFileContent,
		st_ExceptionError &ex);

public:
	//...
};

