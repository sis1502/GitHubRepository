#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CNetDirectoryServerImpl final
{
public:
	CNetDirectoryServerImpl();
	~CNetDirectoryServerImpl();

public:
	int Check(st_ExceptionError &ex);

	int GetTree(st_NetCallData &call,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileTreeList &treenode,
		st_ExceptionError &ex);

	int GetList(st_NetCallData &call,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileList &filelist,
		st_ExceptionError &ex);

	int GetTreeEx(const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileTreeList &treenode,
		st_ExceptionError &ex);

	int GetListEx(const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileList &filelist,
		st_ExceptionError &ex);

private:
	int GetFileList(st_NetCallData &callData,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileList &filelist,
		st_ExceptionError &ex,
		bool bSort = false);
};

