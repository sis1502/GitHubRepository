#pragma once

#include "PubUtil/DataExchange.h"

class CFileTranClientCarry;

class CFileTranClientData final
{
public:
	CFileTranClientData(CFileTranClientCarry *p);
	~CFileTranClientData();

public:
	bool Check(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		//无
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetFileBlock(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const __int64 off,
		const __int32 req_len,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		string &buff,
		__int32 &res_len,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool PutFileBlock(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const __int64 off,
		const string &buff,
		const __int32 req_len,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &res_len,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool MakeDirectory(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const bool &temp,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool MoveFileIn(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &srcfile,
		const string &dstfile,
		const string &delfile,
		const bool &bTopPath,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool MoveFileOut(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &srcfile,
		const string &dstfile,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool RenameFile(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &oldfile,
		const string &newfile,
		const __int32 &attr,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool QueryBasePath(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		//无
		/*	响应数据	*/
		string &basepath,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool isFileExist(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const string &filePath,
		/*	响应数据	*/
		__int32 &fileSize,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool setFileTime(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const __int32 &mtime,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool getFileTime(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &mtime,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool sendFileList(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::RemoteDirectoryList &list,
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool sendAccess(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		//无
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool checkFileList(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::NetFileList &inList,
		/*	响应数据	*/
		DistCommSysData_::ParamList &notExistList,
		DistCommSysData_::ParamList &diffList,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CFileTranClientCarry *m_Carry;
};

