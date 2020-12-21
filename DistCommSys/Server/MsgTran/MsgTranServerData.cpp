#include "Server/MsgTran/MsgTranServerData.h"

#include "Server/MsgTran/MsgTranServerImpl.h"
#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

CMsgTranServerData::
CMsgTranServerData(CMsgTranServerImpl *p)
{
	m_Impl = p;
}


CMsgTranServerData::
~CMsgTranServerData()
{
	//...
}

bool 
CMsgTranServerData::
GetMessage(const ::InforGuard_::GetMsgReq* request, ::InforGuard_::GetMsgRes* response)
{
	HostChain seqIpPort;
	st_MsgBlock mb;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */
	
	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->GetMessage(seqIpPort, mb, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** mb
	::InforGuard_::MsgBlock *mb_ = response->mutable_mb();
	mb_->set_mid(mb.mid);
	mb_->set_level(mb.level);
	mb_->set_serial(mb.serial);
	mb_->set_src(mb.src);
	mb_->set_dst(mb.dst);
	vector<string>::iterator it_S = mb.pl.begin();
	while (it_S != mb.pl.end())
	{
		string *node = mb_->add_pl();
		node->assign(*it_S);
		++it_S;
	}

	//** 异常信息填充
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CMsgTranServerData::
PutMessage(const ::InforGuard_::PutMsgReq* request, ::InforGuard_::PutMsgRes* response)
{
	HostChain seqIpPort;
	st_MsgBlock mb;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//** mb
	mb.mid = request->mb().mid();
	mb.level = request->mb().level();
	mb.serial = request->mb().serial();
	mb.src = request->mb().src();
	mb.dst = request->mb().dst();
	::google::protobuf::RepeatedPtrField<string> nodes_S = request->mb().pl();
	for (auto node_S : nodes_S)
	{
		mb.pl.push_back(node_S);
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->PutMessage(seqIpPort, mb, ex));

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
