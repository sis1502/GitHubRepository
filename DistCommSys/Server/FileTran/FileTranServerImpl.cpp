#include "FileTranServerImpl.h"

CFileTranServerImpl::
CFileTranServerImpl()
{
	//...
}

CFileTranServerImpl::
~CFileTranServerImpl()
{
	//...
}

int
CFileTranServerImpl::
Check(st_ExceptionError &ex)
{
	printf("Check\n");

	return 0;
}

int
CFileTranServerImpl::
GetFileBlock(st_NetCallData &call,
	const string &filename,
	const __int64 off,
	__int32 &len,
	string &buff,
	st_ExceptionError &ex)
{
	printf("GetFileBlock\n");

	return 0;
}

int
CFileTranServerImpl::
PutFileBlock(	st_NetCallData &call,
				const string &filename,
				const __int64 off,
				__int32 &len,
				const string &buff,
				st_ExceptionError &ex)
{
	printf("PutFileBlock\n");

	printf("filename:%s\n", filename.c_str());
	printf("off:%d\n", off);
	printf("len:%d\n", len);
	printf("buff.len:%d\n", buff.size());

	return 0;
}

int
CFileTranServerImpl::
MakeDirectory(	st_NetCallData &call,
				const string &filename,
				const bool &temp,
				st_ExceptionError &ex)
{
	printf("MakeDirectory\n");

	return 0;
}

int
CFileTranServerImpl::
MoveFileIn(	st_NetCallData &call,
			const string &srcfile,
			const string &dstfile,
			const string &delfile,
			const bool &bTopPath,
			st_ExceptionError &ex)
{
	printf("MoveFileIn\n");

	printf("srcfile:%s\n", srcfile.c_str());
	printf("dstfile:%s\n", dstfile.c_str());
	printf("delfile:%s\n", delfile.c_str());

	return 0;
}

int
CFileTranServerImpl::
MoveFileOut(st_NetCallData &call,
			const string &srcfile,
			const string &dstfile,
			st_ExceptionError &ex)
{
	printf("MoveFileOut\n");

	return 0;
}

int
CFileTranServerImpl::
RenameFile(	st_NetCallData &call,
			const string &oldfile,
			const string &newfile,
			const __int32 &attr,
			st_ExceptionError &ex)
{
	printf("RenameFile\n");

	return 0;
}

int
CFileTranServerImpl::
QueryBasePath(string &basepath, st_ExceptionError &ex)
{
	printf("QueryBasePath\n");

	return 0;
}

int
CFileTranServerImpl::
isFileExist(const string &filePath, __int32 &fileSize, st_ExceptionError &ex)
{
	printf("isFileExist\n");

	return 0;
}

int
CFileTranServerImpl::
setFileTime(st_NetCallData &call,
			const string &filename,
			const __int32 &mtime,
			st_ExceptionError &ex)
{
	printf("setFileTime\n");

	return 0;
}

int
CFileTranServerImpl::
getFileTime(st_NetCallData &call,
			const string &filename,
			__int32 &mtime,
			st_ExceptionError &ex)
{
	printf("getFileTime\n");

	return 0;
}

int
CFileTranServerImpl::
sendFileList(const DistCommSysData_::RemoteDirectoryList &list, st_ExceptionError &ex)
{
	printf("sendFileList\n");

	return 0;
}

int
CFileTranServerImpl::
sendAccess(st_ExceptionError &ex)
{
	printf("sendAccess\n");

	return 0;
}

int
CFileTranServerImpl::
checkFileList(	const DistCommSysData_::NetFileList &inList,
	DistCommSysData_::ParamList &notExistList,
	DistCommSysData_::ParamList &diffList,
	st_ExceptionError &ex)
{
	printf("checkFileList\n");

	return 0;
}