#pragma once

#include "PubUtil/BaseDef.h"

#include "MsgTran.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class CGRPCChannel;

class CMsgTranClientCarry final
{
public:
	CMsgTranClientCarry(CGRPCChannel *p);
	~CMsgTranClientCarry();

public:
	bool GetMessage(const string &conn, const ::InforGuard_::GetMsgReq& request, ::InforGuard_::GetMsgRes* response);
	bool PutMessage(const string &conn, const ::InforGuard_::PutMsgReq& request, ::InforGuard_::PutMsgRes* response);

private:
	unique_ptr<InforGuard_::MsgTran::Stub> m_Stub;

private:
	CGRPCChannel *m_Channel;

private:
	unsigned int m_RetryCount;
	time_t m_RetryInterval;
	time_t m_Timeout;
};

