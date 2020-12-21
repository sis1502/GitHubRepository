#include "Server/NetWaterMark/NetWaterMarkServerData.h"

#include "Server/NetWaterMark/NetWaterMarkServerImpl.h"
#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

CNetWaterMarkServerData::
CNetWaterMarkServerData(CNetWaterMarkServerImpl *p)
{
	m_Impl = p;
}


CNetWaterMarkServerData::
~CNetWaterMarkServerData()
{
	//...
}

bool 
CNetWaterMarkServerData::
Check(const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response)
{
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Check(ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
Set(const ::InforGuard_::SetReq* request, ::InforGuard_::SetRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Set(call, request->file(), request->wm(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
Get(const ::InforGuard_::GetReq* request, ::InforGuard_::GetRes* response)
{
	st_NetCallData call;
	string wm;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Get(call, request->file(), wm, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** wm
	response->set_wm(wm);

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
Add(const ::InforGuard_::AddReq* request, ::InforGuard_::AddRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Add(call, request->filepath(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
Remove(const ::InforGuard_::RemoveReq* request, ::InforGuard_::RemoveRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Remove(call, request->filepath(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
Rename(const ::InforGuard_::RenameReq* request, ::InforGuard_::RenameRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Rename(call, request->oldfilename(), request->newfilename(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
Verify(const ::InforGuard_::VerifyReq* request, ::InforGuard_::VerifyRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Verify(call, request->sfilename(), request->nfilesize(), request->swm(), request->bsimplesync(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
VerifyForFilter(const ::InforGuard_::VerifyForFilterReq* request, ::InforGuard_::VerifyForFilterRes* response)
{
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->VerifyForFilter(request->files(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetWaterMarkServerData::
RequestResume(const ::InforGuard_::RequestResumeReq* request, ::InforGuard_::RequestResumeRes* response)
{
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->RequestResume(request->filename(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}
