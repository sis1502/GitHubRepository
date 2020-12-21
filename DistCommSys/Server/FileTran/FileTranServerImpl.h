#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CFileTranServerImpl final
{
public:
	CFileTranServerImpl();
	~CFileTranServerImpl();

public:
	int Check(st_ExceptionError &ex);

	int GetFileBlock(st_NetCallData &call,
		const string &filename,
		const __int64 off,
		__int32 &len,
		string &buff,
		st_ExceptionError &ex);

	int PutFileBlock(st_NetCallData &call,
		const string &filename,
		const __int64 off,
		__int32 &len,
		const string &buff,
		st_ExceptionError &ex);

	int MakeDirectory(st_NetCallData &call,
		const string &filename,
		const bool &temp,
		st_ExceptionError &ex);

	int MoveFileIn(st_NetCallData &call,
		const string &srcfile,
		const string &dstfile,
		const string &delfile,
		const bool &bTopPath,
		st_ExceptionError &ex);

	int MoveFileOut(st_NetCallData &call,
		const string &srcfile,
		const string &dstfile,
		st_ExceptionError &ex);

	int RenameFile(st_NetCallData &call,
		const string &oldfile,
		const string &newfile,
		const __int32 &attr,
		st_ExceptionError &ex);

	int QueryBasePath(string &basepath, st_ExceptionError &ex);

	int isFileExist(const string &filePath, __int32 &fileSize, st_ExceptionError &ex);

	int setFileTime(st_NetCallData &call,
		const string &filename,
		const __int32 &mtime,
		st_ExceptionError &ex);

	int getFileTime(st_NetCallData &call,
		const string &filename,
		__int32 &mtime,
		st_ExceptionError &ex);

	int sendFileList(const DistCommSysData_::RemoteDirectoryList &list, st_ExceptionError &ex);

	int sendAccess(st_ExceptionError &ex);

	int checkFileList(	const DistCommSysData_::NetFileList &inList,
		DistCommSysData_::ParamList &notExistList,
		DistCommSysData_::ParamList &diffList,
		st_ExceptionError &ex);

private:
	char *transblock;
};