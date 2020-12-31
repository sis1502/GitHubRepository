#include "Server/NetWaterMark/NetWaterMarkServerImpl.h"

CNetWaterMarkServerImpl::CNetWaterMarkServerImpl()
{
	//...
}


CNetWaterMarkServerImpl::~CNetWaterMarkServerImpl()
{
	//...
}

int
CNetWaterMarkServerImpl::
Check(st_ExceptionError &ex)
{
	printf("Check\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Set(st_NetCallData &call,
	const string &file,
	const string &wm,
	st_ExceptionError &ex)
{
	printf("Set\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Get(st_NetCallData &call,
	const string &file,
	string &wm,
	st_ExceptionError &ex)
{
	printf("Get\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Add(st_NetCallData &call,
	const string &filePath,
	st_ExceptionError &ex)
{
	printf("Add\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Remove(st_NetCallData &call,
	const string &filePath,
	st_ExceptionError &ex)
{
	printf("Remove\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Rename(st_NetCallData &call,
	const string &oldfilename,
	const string &newfilename,
	st_ExceptionError &ex)
{
	printf("Rename\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Verify(st_NetCallData &call,
	const string &sFileName,
	const long &nFileSize,
	const string &sWm,
	const bool &bSimpleSync,
	st_ExceptionError &ex)
{
	printf("Verify\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
VerifyForFilter(const string &files, st_ExceptionError &ex)
{
	printf("VerifyForFilter\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
RequestResume(const string &filename, st_ExceptionError &ex)
{
	printf("RequestResume\n");

	return 0;
}