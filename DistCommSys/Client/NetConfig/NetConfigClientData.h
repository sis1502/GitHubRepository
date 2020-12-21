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
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &cfgFileName,
		/*	��Ӧ����	*/
		string &cfgFileContent,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Save(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &cfgFileName,
		const string &cfgFileContent,
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CNetConfigClientCarry *m_Carry;
};

