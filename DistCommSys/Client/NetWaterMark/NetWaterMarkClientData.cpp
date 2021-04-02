#include "Client/NetWaterMark/NetWaterMarkClientData.h"

#include "Client/NetWaterMark/NetWaterMarkClientCarry.h"

using namespace DistCommSysData_;

CNetWaterMarkClientData::
CNetWaterMarkClientData(CNetWaterMarkClientCarry *p)
{
	m_Carry = p;
}

CNetWaterMarkClientData::
~CNetWaterMarkClientData()
{
	//...
}

bool
CNetWaterMarkClientData::
Check(const string &conn, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::CheckReq request;
	::InforGuard_::CheckRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	request.set_check(true);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Check(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
Set(const string &conn,
	const st_NetCallData &req_call,
	const string &file,
	const string &wm,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::SetReq request;
	::InforGuard_::SetRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** file
	request.set_file(file);

	//** wm
	request.set_wm(wm);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Set(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
Get(const string &conn,
	const st_NetCallData &req_call,
	const string &file,
	st_NetCallData &res_call,
	string &wm,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetReq request;
	::InforGuard_::GetRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** file
	request.set_file(file);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Get(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** wm
	wm = response.wm();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
Add(const string &conn,
	const st_NetCallData &req_call,
	const string &filePath,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::AddReq request;
	::InforGuard_::AddRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** file
	request.set_filepath(filePath);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Add(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
Remove(const string &conn,
	const st_NetCallData &req_call,
	const string &filePath,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::RemoveReq request;
	::InforGuard_::RemoveRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** file
	request.set_filepath(filePath);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Remove(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
Rename(const string &conn,
	const st_NetCallData &req_call,
	const string &oldfilename,
	const string &newfilename,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::RenameReq request;
	::InforGuard_::RenameRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** oldfilename
	request.set_oldfilename(oldfilename);

	//** newfilename
	request.set_newfilename(newfilename);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Rename(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
Verify(const string &conn,
	const st_NetCallData &req_call,
	const string &sFileName,
	const __int32 &nFileSize,
	const string &sWm,
	const bool &bSimpleSync,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::VerifyReq request;
	::InforGuard_::VerifyRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** sFileName
	request.set_sfilename(sFileName);

	//** nFileSize
	request.set_nfilesize(nFileSize);

	//** sWm
	request.set_swm(sWm);

	//** bSimpleSync
	request.set_bsimplesync(bSimpleSync);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Verify(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
VerifyForFilter(const string &conn, const string &files, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::VerifyForFilterReq request;
	::InforGuard_::VerifyForFilterRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** files
	request.set_files(files);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->VerifyForFilter(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetWaterMarkClientData::
RequestResume(const string &conn, const string &filename, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::RequestResumeReq request;
	::InforGuard_::RequestResumeRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** filename
	request.set_filename(filename);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->RequestResume(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}