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
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const DistCommSysData_::st_MsgBlock &req_mb,
		/*	响应数据	*/
		DistCommSysData_::st_MsgBlock &res_mb,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool PutMessage(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const DistCommSysData_::st_MsgBlock &req_mb,
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CMsgTranClientCarry *m_Carry;
};

