#include "Client/NetDirectory/NetDirectoryClientImpl.h"

#include "Client/NetDirectory/NetDirectoryClientData.h"

#ifndef _UNITTEST
#	include "Common/ExceptionError.h"
#endif

CNetDirectoryClientImpl::
CNetDirectoryClientImpl(CNetDirectoryClientData *p)
{
	m_Data = p;
}


CNetDirectoryClientImpl::
~CNetDirectoryClientImpl()
{
	//...
}

int 
CNetDirectoryClientImpl::
Check(const string &ip, const string &port)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Check(conn, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CNetDirectoryClientImpl::
GetTree(const string &ip, const string &port,
		st_NetCallData &call,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileTreeList &treenode)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->GetTree(conn, call, seqIpPort, remotefoldername, mode, res_call, treenode, ret, ex))
	{
		call = res_call;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CNetDirectoryClientImpl::
GetList(const string &ip, const string &port,
		st_NetCallData &call,
		const HostChain &seqIpPort,
		const string &remotefoldername,
		const long &mode,
		NetFileList &filelist)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->GetList(conn, call, seqIpPort, remotefoldername, mode, res_call, filelist, ret, ex))
	{
		call = res_call;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CNetDirectoryClientImpl::
GetTreeEx(	const string &ip, const string &port,
			const HostChain &seqIpPort,
			const string &remotefoldername,
			const long &mode,
			NetFileTreeList &treenode)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->GetTreeEx(conn,seqIpPort, remotefoldername, mode, treenode, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CNetDirectoryClientImpl::
GetListEx(const string &ip, const string &port,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->GetListEx(conn, seqIpPort, remotefoldername, mode, filelist, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}
