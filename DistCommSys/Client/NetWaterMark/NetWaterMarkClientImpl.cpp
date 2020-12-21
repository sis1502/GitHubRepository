#include "Client/NetWaterMark/NetWaterMarkClientImpl.h"

#include "Client/NetWaterMark/NetWaterMarkClientData.h"

#ifndef _UNITTEST
#	include "Common/ExceptionError.h"
#endif

CNetWaterMarkClientImpl::
CNetWaterMarkClientImpl(CNetWaterMarkClientData *p)
{
	m_Data = p;
}


CNetWaterMarkClientImpl::
~CNetWaterMarkClientImpl()
{
	//...
}

int 
CNetWaterMarkClientImpl::
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
CNetWaterMarkClientImpl::
Set(const string &ip, const string &port,
	st_NetCallData &call,
	const string &file,
	const string &wm)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Set(conn, call, file, wm, res_call, ret, ex))
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
CNetWaterMarkClientImpl::
Get(const string &ip, const string &port,
	st_NetCallData &call,
	const string &file,
	string &wm)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Get(conn, call, file, res_call, wm, ret, ex))
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
CNetWaterMarkClientImpl::
Add(const string &ip, const string &port,
	st_NetCallData &call,
	const string &filePath)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Add(conn, call, filePath, res_call, ret, ex))
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
CNetWaterMarkClientImpl::
Remove(	const string &ip, const string &port,
		st_NetCallData &call,
		const string &filePath)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Remove(conn, call, filePath, res_call, ret, ex))
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
CNetWaterMarkClientImpl::
Rename(	const string &ip, const string &port,
		st_NetCallData &call,
		const string &oldfilename,
		const string &newfilename)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Rename(conn, call, oldfilename, newfilename, res_call, ret, ex))
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
CNetWaterMarkClientImpl::
Verify(	const string &ip, const string &port,
		st_NetCallData &call,
		const string &sFileName,
		const long &nFileSize,
		const string &sWm,
		const bool &bSimpleSync)
{
	st_ExceptionError ex;
	st_NetCallData res_call;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->Verify(conn, call, sFileName, nFileSize, sWm, bSimpleSync, res_call, ret, ex))
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
CNetWaterMarkClientImpl::
VerifyForFilter(const string &ip, const string &port, const string &files)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->VerifyForFilter(conn, files, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}


int
CNetWaterMarkClientImpl::
RequestResume(const string &ip, const string &port, const string &filename)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->RequestResume(conn, filename, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}
