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
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		//无
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Set(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &file,
		const string &wm,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Get(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &file,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		string &wm,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Add(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filePath,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Remove(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filePath,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Rename(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &oldfilename,
		const string &newfilename,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool Verify(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &sFileName,
		const __int32 &nFileSize,
		const string &sWm,
		const bool &bSimpleSync,
		/*	响应数据	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool VerifyForFilter(
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const string &files,
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool RequestResume(	
		/*	固定数据	*/
		const string &conn,
		/*	请求数据	*/
		const string &filename,
		/*	响应数据	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CNetWaterMarkClientCarry *m_Carry;
};

