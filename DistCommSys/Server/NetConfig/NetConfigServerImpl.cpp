#include "Server/NetConfig/NetConfigServerImpl.h"

CNetConfigServerImpl::CNetConfigServerImpl()
{
	//...
}


CNetConfigServerImpl::~CNetConfigServerImpl()
{
	//...
}

int
CNetConfigServerImpl::
Load(const HostChain &seqIpPort,
	const string &cfgFileName,
	string &cfgFileContent,
	st_ExceptionError &ex)
{
	printf("Load\n");

	return 0;
}

int
CNetConfigServerImpl::
Save(const HostChain &seqIpPort,
	const string &cfgFileName,
	const string &cfgFileContent,
	st_ExceptionError &ex)
{
	printf("Save\n");

	return 0;
}
