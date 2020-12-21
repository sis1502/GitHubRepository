#pragma once

#include "PubUtil/BaseDef.h"

#include "grpc_Generated/NetWaterMark.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class CGRPCChannel;

class CNetWaterMarkClientCarry final
{
public:
	CNetWaterMarkClientCarry(CGRPCChannel *p);
	~CNetWaterMarkClientCarry();

public:
	bool Check(const string &conn, const ::InforGuard_::CheckReq& request, ::InforGuard_::CheckRes* response);
	bool Set(const string &conn, const ::InforGuard_::SetReq& request, ::InforGuard_::SetRes* response);
	bool Get(const string &conn, const ::InforGuard_::GetReq& request, ::InforGuard_::GetRes* response);
	bool Add(const string &conn, const ::InforGuard_::AddReq& request, ::InforGuard_::AddRes* response);
	bool Remove(const string &conn, const ::InforGuard_::RemoveReq& request, ::InforGuard_::RemoveRes* response);
	bool Rename(const string &conn, const ::InforGuard_::RenameReq& request, ::InforGuard_::RenameRes* response);
	bool Verify(const string &conn, const ::InforGuard_::VerifyReq& request, ::InforGuard_::VerifyRes* response);
	bool VerifyForFilter(const string &conn, const ::InforGuard_::VerifyForFilterReq& request, ::InforGuard_::VerifyForFilterRes* response);
	bool RequestResume(const string &conn, const ::InforGuard_::RequestResumeReq& request, ::InforGuard_::RequestResumeRes* response);

private:
	unique_ptr<InforGuard_::NetWaterMark::Stub> m_Stub;

private:
	CGRPCChannel *m_Channel;

private:
	unsigned int m_RetryCount;
	time_t m_RetryInterval;
	time_t m_Timeout;
};

