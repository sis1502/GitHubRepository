#include "Server/NetConfig/NetConfigServerData.h"

#include "Server/NetConfig/NetConfigServerImpl.h"
#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

CNetConfigServerData::
CNetConfigServerData(CNetConfigServerImpl *p)
{
	m_Impl = p;
}


CNetConfigServerData::
~CNetConfigServerData()
{
	//...
}

bool 
CNetConfigServerData::
Load(const ::InforGuard_::LoadReq* request, ::InforGuard_::LoadRes* response)
{
	HostChain seqIpPort;
	string cfgFileContent;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Load(seqIpPort, request->cfgfilename(), cfgFileContent, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** cfgFileContent
	response->set_cfgfilecontent(cfgFileContent);

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetConfigServerData::
Save(const ::InforGuard_::SaveReq* request, ::InforGuard_::SaveRes* response)
{
	HostChain seqIpPort;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Save(seqIpPort, request->cfgfilename(), request->cfgfilecontent(), ex));

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