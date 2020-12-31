#pragma once

#include "PubUtil/BaseDef.h"

#include "MsgTran.grpc.pb.h"

class CMsgTranServerImpl;

class CMsgTranServerData final
{
public:
	CMsgTranServerData(CMsgTranServerImpl *p);
	~CMsgTranServerData();

public:
	bool GetMessage(const ::InforGuard_::GetMsgReq* request, ::InforGuard_::GetMsgRes* response);
	bool PutMessage(const ::InforGuard_::PutMsgReq* request, ::InforGuard_::PutMsgRes* response);

private:
	CMsgTranServerImpl *m_Impl;
};

