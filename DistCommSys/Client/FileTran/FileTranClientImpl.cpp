#include "Client/FileTran/FileTranClientImpl.h"

#include "Client/FileTran/FileTranClientData.h"

#ifndef _UNITTEST
#	include "Common/ExceptionError.h"
#endif

CFileTranClientImpl::
CFileTranClientImpl(CFileTranClientData *p)
{
	m_Data = p;
}


CFileTranClientImpl::
~CFileTranClientImpl()
{
	//...
}

int
CFileTranClientImpl::
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
CFileTranClientImpl::
GetFileBlock(const string &ip, const string &port,
	st_NetCallData &call,
	const string &filename,
	const long long &off,
	string &buff,
	long &len)
{
	st_NetCallData res_call;
	int res_len;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->GetFileBlock(conn, call, filename, off, len, res_call, buff, res_len, ret, ex))
	{
		len = res_len;
		call = res_call;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CFileTranClientImpl::
PutFileBlock(const string &ip, const string &port,
	st_NetCallData &call,
	const string &filename,
	const long long &off,
	const string &buff,
	long &len)
{
	st_NetCallData res_call;
	int res_len;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->PutFileBlock(conn, call, filename, off, buff, len, res_call, res_len, ret, ex))
	{
		len = res_len;
		call = res_call;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CFileTranClientImpl::
MakeDirectory(const string &ip, const string &port,
	st_NetCallData &call,
	const string &filename,
	const bool &temp)
{
	st_NetCallData res_call;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->MakeDirectory(conn, call, filename, temp, res_call, ret, ex))
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
CFileTranClientImpl::
MoveFileIn(	const string &ip, const string &port,
			st_NetCallData &call,
			const string &srcfile,
			const string &dstfile,
			const string &delfile,
			const bool &bTopPath)
{
	st_NetCallData res_call;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->MoveFileIn(conn, call, srcfile, dstfile, delfile, bTopPath, res_call, ret, ex))
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
CFileTranClientImpl::
MoveFileOut(const string &ip, const string &port,
	st_NetCallData &call,
	const string &srcfile,
	const string &dstfile)
{
	st_NetCallData res_call;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->MoveFileOut(conn, call, srcfile, dstfile, res_call, ret, ex))
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
CFileTranClientImpl::
RenameFile(const string &ip, const string &port,
	st_NetCallData &call,
	const string &oldfile,
	const string &newfile,
	const long &attr)
{
	st_NetCallData res_call;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->RenameFile(conn, call, oldfile, newfile, attr, res_call, ret, ex))
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
CFileTranClientImpl::
QueryBasePath(const string &ip, const string &port, string &basepath)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->QueryBasePath(conn, basepath, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CFileTranClientImpl::
isFileExist(const string &ip, const string &port,
	const string &filePath,
	long &fileSize)
{
	st_ExceptionError ex;
	int res_fileSize;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->isFileExist(conn, filePath, res_fileSize, ret, ex))
	{
		fileSize = res_fileSize;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CFileTranClientImpl::
setFileTime(const string &ip, const string &port,
	st_NetCallData &call,
	const string &filename,
	const long &mtime)
{
	st_NetCallData res_call;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->setFileTime(conn, call, filename, mtime, res_call, ret, ex))
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
CFileTranClientImpl::
getFileTime(const string &ip, const string &port,
	st_NetCallData &call,
	const string &filename,
	long &mtime)
{
	st_NetCallData res_call;
	int res_mtime;
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->getFileTime(conn, call, filename, res_call, res_mtime, ret, ex))
	{
		call = res_call;
		mtime = res_mtime;
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int 
CFileTranClientImpl::
sendFileList(const string &ip, const string &port, const RemoteDirectoryList &list)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->sendFileList(conn, list, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int 
CFileTranClientImpl::
sendAccess(const string &ip, const string &port)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->sendAccess(conn, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}

int
CFileTranClientImpl::
checkFileList(const string &ip, const string &port,
	const NetFileList &inList,
	ParamList &notExistList,
	ParamList &diffList)
{
	st_ExceptionError ex;
	string conn = ip + ":" + port;
	int ret;
	if (m_Data->checkFileList(conn, inList, notExistList, diffList, ret, ex))
	{
		return ret;
	}
	else
	{
		__IMPLEXCEPTION_CONVERT__
	}
}
