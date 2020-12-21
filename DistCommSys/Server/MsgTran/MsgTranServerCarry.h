#pragma once

#include "PubUtil/BaseDef.h"

#include "grpc_Generated/MsgTran.grpc.pb.h"

class CMsgTranServerData;

class CMsgTranServerCarry final : public InforGuard_::MsgTran::Service
{
public:
	CMsgTranServerCarry(CMsgTranServerData *p);
	~CMsgTranServerCarry();

public:
	virtual ::grpc::Status GetMessage(::grpc::ServerContext* context, const ::InforGuard_::GetMsgReq* request, ::InforGuard_::GetMsgRes* response);
	virtual ::grpc::Status PutMessage(::grpc::ServerContext* context, const ::InforGuard_::PutMsgReq* request, ::InforGuard_::PutMsgRes* response);

private:
	CMsgTranServerData *m_Data;
};