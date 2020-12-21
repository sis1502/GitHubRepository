#include "Client/NetConfig/NetConfigClientImpl.h"

#include "Client/NetConfig/NetConfigClientData.h"

#ifndef _UNITTEST
#	include "Common/ExceptionError.h"
#endif

CNetConfigClientImpl::
CNetConfigClientImpl(CNetConfigClientData *p)
{
	m_Data = p;
}

CNetConfigClientImpl::
~CNetConfigClientImpl()
{
	//...
}

int
CNetConfigClientImpl::
Load(const string &ip, const string &port,
	const HostChain &seqIpPort,
	const string &cfgFileName,
	string &cfgFileContent)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Load(conn, seqIpPort, cfgFileName, cfgFileContent, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CNetConfigClientImpl::
Save(const string &ip, const string &port,
	const HostChain &seqIpPort,
	const string &cfgFileName,
	const string &cfgFileContent)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Save(conn, seqIpPort, cfgFileName, cfgFileContent, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}
