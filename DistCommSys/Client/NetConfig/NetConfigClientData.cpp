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
	***		�������������
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
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** cfgFileContent
	cfgFileContent = response.cfgfilecontent();

	//** ret
	ret = response.ret();

	//** �쳣��Ϣ
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
	***		�������������
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
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** �쳣��Ϣ
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}