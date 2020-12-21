#pragma once

#include "PubUtil/DataExchange.h"

class CNetWaterMarkClientCarry;

class CNetWaterMarkClientData final
{
public:
	CNetWaterMarkClientData(CNetWaterMarkClientCarry *p);
	~CNetWaterMarkClientData();

public:
	bool Check(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		//��
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Set(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &file,
		const string &wm,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Get(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &file,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		string &wm,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Add(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filePath,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Remove(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filePath,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Rename(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &oldfilename,
		const string &newfilename,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Verify(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &sFileName,
		const __int32 &nFileSize,
		const string &sWm,
		const bool &bSimpleSync,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool VerifyForFilter(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const string &files,
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool RequestResume(	
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const string &filename,
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CNetWaterMarkClientCarry *m_Carry;
};

