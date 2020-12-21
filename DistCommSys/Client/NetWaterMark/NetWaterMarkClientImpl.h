#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CNetWaterMarkClientData;

class CNetWaterMarkClientImpl
{
public:
	CNetWaterMarkClientImpl(CNetWaterMarkClientData *p);
	~CNetWaterMarkClientImpl();

public:
	int Check(const string &ip, const string &port);

	int Set(const string &ip, const string &port,
		st_NetCallData &call,
		const string &file,
		const string &wm);

	int Get(const string &ip, const string &port,
		st_NetCallData &call,
		const string &file,
		string &wm);

	int Add(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filePath);

	int Remove(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filePath);

	int Rename(const string &ip, const string &port,
		st_NetCallData &call,
		const string &oldfilename,
		const string &newfilename);

	int Verify(const string &ip, const string &port,
		st_NetCallData &call,
		const string &sFileName,
		const long &nFileSize,
		const string &sWm,
		const bool &bSimpleSync);

	int VerifyForFilter(const string &ip, const string &port, const string &files);

	int RequestResume(const string &ip, const string &port, const string &filename);

private:
	CNetWaterMarkClientData *m_Data;
};

