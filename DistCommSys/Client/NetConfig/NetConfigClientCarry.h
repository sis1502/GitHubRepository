#pragma once

#include "PubUtil/BaseDef.h"

#include "grpc_Generated/NetConfig.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class CGRPCChannel;

class CNetConfigClientCarry final
{
public:
	CNetConfigClientCarry(CGRPCChannel *p);
	~CNetConfigClientCarry();

public:
	bool Load(const string &conn, const ::InforGuard_::LoadReq& request, ::InforGuard_::LoadRes* response);
	bool Save(const string &conn, const ::InforGuard_::SaveReq& request, ::InforGuard_::SaveRes* response);

private:
	unique_ptr<InforGuard_::NetConfig::Stub> m_Stub;

private:
	CGRPCChannel *m_Channel;

private:
	unsigned int m_RetryCount;
	time_t m_RetryInterval;
	time_t m_Timeout;
};

