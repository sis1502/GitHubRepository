#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CNetDirectoryClientData;

class CNetDirectoryClientImpl
{
public:
	CNetDirectoryClientImpl(CNetDirectoryClientData *p);
	~CNetDirectoryClientImpl();

public:
	int Check(const string &ip, const string &port);

	int GetTree(const string &ip, const string &port,
		st_NetCallData &call,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileTreeList &treenode);

	int GetList(const string &ip, const string &port,
		st_NetCallData &call,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileList &filelist);

	int GetTreeEx(const string &ip, const string &port,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileTreeList &treenode);

	int GetListEx(const string &ip, const string &port,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileList &filelist);

private:
	CNetDirectoryClientData *m_Data;
};

