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
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		//��
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetTree(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		DistCommSysData_::NetFileTreeList &treenode,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetList(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		DistCommSysData_::NetFileList &filelist,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetTreeEx(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	��Ӧ����	*/
		DistCommSysData_::NetFileTreeList &treenode,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetListEx(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::HostChain &seqIpPort,
		const string &remotefoldername,
		const __int32 &mode,
		/*	��Ӧ����	*/
		DistCommSysData_::NetFileList &filelist,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CNetDirectoryClientCarry *m_Carry;
};

