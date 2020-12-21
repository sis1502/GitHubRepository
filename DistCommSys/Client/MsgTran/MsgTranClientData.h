#pragma once

#include "PubUtil/DataExchange.h"

class CMsgTranClientCarry;

class CMsgTranClientData final
{
public:
	CMsgTranClientData(CMsgTranClientCarry *p);
	~CMsgTranClientData();

public:
	bool GetMessage(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const DistCommSysData_::st_MsgBlock &req_mb,
		/*	��Ӧ����	*/
		DistCommSysData_::st_MsgBlock &res_mb,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool PutMessage(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const DistCommSysData_::st_MsgBlock &req_mb,
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CMsgTranClientCarry *m_Carry;
};

