#pragma once

#include "PubUtil/BaseDef.h"

#include "grpc_Generated/NetDirectory.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class CGRPCChannel;

class CNetDirectoryClientCarry final
{
public:
	CNetDirectoryClientCarry(CGRPCChannel *p);
	~CNetDirectoryClientCarry();

public:
	bool Check(const string &conn, const ::InforGuard_::CheckReq& request, ::InforGuard_::CheckRes* response);
	bool GetTree(const string &conn, const ::InforGuard_::GetTreeReq& request, ::InforGuard_::GetTreeRes* response);
	bool GetList(const string &conn, const ::InforGuard_::GetListReq& request, ::InforGuard_::GetListRes* response);
	bool GetTreeEx(const string &conn, const ::InforGuard_::GetTreeExReq& request, ::InforGuard_::GetTreeExRes* response);
	bool GetListEx(const string &conn, const ::InforGuard_::GetListExReq& request, ::InforGuard_::GetListExRes* response);

private:
	unique_ptr<InforGuard_::NetDirectory::Stub> m_Stub;

private:
	CGRPCChannel *m_Channel;

private:
	unsigned int m_RetryCount;
	time_t m_RetryInterval;
	time_t m_Timeout;
};

