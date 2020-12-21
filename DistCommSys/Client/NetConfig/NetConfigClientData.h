#pragma once

#include "PubUtil/DataExchange.h"

class CNetConfigClientCarry;

class CNetConfigClientData final
{
public:
	CNetConfigClientData(CNetConfigClientCarry *p);
	~CNetConfigClientData();

public:
	bool Load(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &cfgFileName,
		/*	响应数据	*/
		string &cfgFileContent,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Save(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &cfgFileName,
		const string &cfgFileContent,
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CNetConfigClientCarry *m_Carry;
};

