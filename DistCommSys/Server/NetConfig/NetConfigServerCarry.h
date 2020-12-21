#pragma once

#include "grpc_Generated/NetConfig.grpc.pb.h"

class CNetConfigServerData;

class CNetConfigServerCarry final : public InforGuard_::NetConfig::Service
{
public:
	CNetConfigServerCarry(CNetConfigServerData *p);
	~CNetConfigServerCarry();

public:
	virtual ::grpc::Status Load(::grpc::ServerContext* context, const ::InforGuard_::LoadReq* request, ::InforGuard_::LoadRes* response);
	virtual ::grpc::Status Save(::grpc::ServerContext* context, const ::InforGuard_::SaveReq* request, ::InforGuard_::SaveRes* response);

private:
	CNetConfigServerData *m_Data;
};