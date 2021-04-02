#include "Client/NetConfig/NetConfigClientData.h"

#include "Client/NetConfig/NetConfigClientCarry.h"

using namespace DistCommSysData_;

CNetConfigClientData::
CNetConfigClientData(CNetConfigClientCarry *p)
{
	m_Carry = p;
}

CNetConfigClientData::
~CNetConfigClientData()
{
	//...
}

bool
CNetConfigClientData::
Load(const string &conn,
	const HostChain &seqIpPort,
	const string &cfgFileName,
	string &cfgFileContent,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::LoadReq request;
	::InforGuard_::LoadRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** cfgFileName
	request.set_cfgfilename(cfgFileName);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Load(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** cfgFileContent
	cfgFileContent = response.cfgfilecontent();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetConfigClientData::
Save(const string &conn,
	const HostChain &seqIpPort,
	const string &cfgFileName,
	const string &cfgFileContent,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::SaveReq request;
	::InforGuard_::SaveRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** cfgFileName
	request.set_cfgfilename(cfgFileName);

	//** cfgFileContent
	request.set_cfgfilecontent(cfgFileContent);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->Save(conn, request, &response);

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