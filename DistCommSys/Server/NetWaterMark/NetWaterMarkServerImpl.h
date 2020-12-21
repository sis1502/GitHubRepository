#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CNetWaterMarkServerImpl final
{
public:
	CNetWaterMarkServerImpl();
	~CNetWaterMarkServerImpl();

public:
	int Check(st_ExceptionError &ex);

	int Set(st_NetCallData &call,
		const string &file,
		const string &wm,
		st_ExceptionError &ex);

	int Get(st_NetCallData &call,
		const string &file,
		string &wm,
		st_ExceptionError &ex);

	int Add(st_NetCallData &call,
		const string &filePath,
		st_ExceptionError &ex);

	int Remove(st_NetCallData &call,
		const string &filePath,
		st_ExceptionError &ex);

	int Rename(st_NetCallData &call,
		const string &oldfilename,
		const string &newfilename,
		st_ExceptionError &ex);

	int Verify(st_NetCallData &call,
		const string &sFileName,
		const long &nFileSize,
		const string &sWm,
		const bool &bSimpleSync,
		st_ExceptionError &ex);

	int VerifyForFilter(const string &files, st_ExceptionError &ex);

	int RequestResume(const string &filename, st_ExceptionError &ex);

private:
	//...
};

