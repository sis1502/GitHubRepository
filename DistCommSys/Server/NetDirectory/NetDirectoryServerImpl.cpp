#include "Server/NetDirectory/NetDirectoryServerImpl.h"

#include "DCSManager.h"

CNetDirectoryServerImpl::CNetDirectoryServerImpl()
{
	//...
}


CNetDirectoryServerImpl::~CNetDirectoryServerImpl()
{
	//...
}

int
CNetDirectoryServerImpl::
Check(st_ExceptionError &ex)
{
	printf("Check\n");

	return 0;
}

int
CNetDirectoryServerImpl::
GetTree(st_NetCallData &call,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileTreeList &treenode,
	st_ExceptionError &ex)
{
	printf("GetTree\n");

	return 0;
}

int
CNetDirectoryServerImpl::
GetList(st_NetCallData &call,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist,
	st_ExceptionError &ex)
{
	printf("GetList\n");

	return 0;
}

int
CNetDirectoryServerImpl::
GetTreeEx(const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileTreeList &treenode,
	st_ExceptionError &ex)
{
	printf("GetTreeEx\n");

	return 0;
}

int
CNetDirectoryServerImpl::
GetListEx(const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist,
	st_ExceptionError &ex)
{
	printf("GetListEx\n");

	return 0;
}

int 
CNetDirectoryServerImpl::
GetFileList(st_NetCallData &callData,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist,
	st_ExceptionError &ex,
	bool bSort)
{

	return 0;
}