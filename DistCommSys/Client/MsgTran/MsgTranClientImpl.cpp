#include "Client/MsgTran/MsgTranClientImpl.h"

#include "Client/MsgTran/MsgTranClientData.h"

#ifndef _UNITTEST
#	include "Common/ExceptionError.h"
#endif

CMsgTranClientImpl::
CMsgTranClientImpl(CMsgTranClientData *p)
{
	m_Data = p;
}


CMsgTranClientImpl::
~CMsgTranClientImpl()
{
	//...
}

int
CMsgTranClientImpl::
GetMessage(const string &ip, const string &port,
	const HostChain seqIpPort,
	st_MsgBlock &mb)
{
	st_ExceptionError ex;
	st_MsgBlock res_mb;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->GetMessage(conn, seqIpPort, mb, res_mb, ret, ex))
	{
		mb = res_mb;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CMsgTranClientImpl::
PutMessage(const string &ip, const string &port,
	const HostChain seqIpPort,
	const st_MsgBlock &mb)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->PutMessage(conn, seqIpPort, mb, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}
