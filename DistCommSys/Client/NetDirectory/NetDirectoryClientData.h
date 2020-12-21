#pragma once

#include "PubUtil/DataExchange.h"

class CNetDirectoryClientCarry;

class CNetDirectoryClientData final
{
public:
	CNetDirectoryClientData(CNetDirectoryClientCarry *p);
	~CNetDirectoryClientData();

public:
	bool Check(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		//无
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetTree(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		DistCommSysData_::NetFileTreeList &treenode,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetList(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		DistCommSysData_::NetFileList &filelist,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetTreeEx(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	响应数据	*/
		DistCommSysData_::NetFileTreeList &treenode,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetListEx(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	响应数据	*/
		DistCommSysData_::NetFileList &filelist,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CNetDirectoryClientCarry *m_Carry;
};

