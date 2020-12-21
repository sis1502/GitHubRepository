#include "Client/MsgTran/MsgTranClientData.h"

#include "Client/MsgTran/MsgTranClientCarry.h"

using namespace DistCommSysData_;

CMsgTranClientData::
CMsgTranClientData(CMsgTranClientCarry *p)
{
	m_Carry = p;
}

CMsgTranClientData::
~CMsgTranClientData()
{
	//...
}

bool
CMsgTranClientData::
GetMessage(const string &conn,
	const HostChain &seqIpPort,
	const st_MsgBlock &req_mb,
	st_MsgBlock &res_mb,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetMsgReq request;
	::InforGuard_::GetMsgRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** req_mb
	InforGuard_::MsgBlock *req_mb_ = request.mutable_mb();
	req_mb_->set_mid(req_mb.mid);
	req_mb_->set_level(req_mb.level);
	req_mb_->set_serial(req_mb.serial);
	req_mb_->set_src(req_mb.src);
	req_mb_->set_dst(req_mb.dst);
	vector<string>::const_iterator it_P = req_mb.pl.begin();
	while (it_P != req_mb.pl.end())
	{
		string * node = req_mb_->add_pl();
		node->assign(*it_P);
		++it_P;
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->GetMessage(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** res_mb
	res_mb.mid = response.mb().mid();
	res_mb.level = response.mb().level();
	res_mb.serial = response.mb().serial();
	res_mb.src = response.mb().src();
	res_mb.dst = response.mb().dst();
	::google::protobuf::RepeatedPtrField<string> pls = response.mb().pl();
	for (auto pl_ : pls)
	{
		res_mb.pl.push_back(pl_);
	}

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CMsgTranClientData::
PutMessage(const string &conn,
	const HostChain &seqIpPort,
	const st_MsgBlock &req_mb,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::PutMsgReq request;
	::InforGuard_::PutMsgRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** req_mb
	InforGuard_::MsgBlock *req_mb_ = request.mutable_mb();
	req_mb_->set_mid(req_mb.mid);
	req_mb_->set_level(req_mb.level);
	req_mb_->set_serial(req_mb.serial);
	req_mb_->set_src(req_mb.src);
	req_mb_->set_dst(req_mb.dst);
	vector<string>::const_iterator it_P = req_mb.pl.begin();
	while (it_P != req_mb.pl.end())
	{
		string * node = req_mb_->add_pl();
		node->assign(*it_P);
		++it_P;
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->PutMessage(conn, request, &response);

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

	return true;
}