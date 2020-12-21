#pragma once

#include "grpc_Generated/NetWaterMark.grpc.pb.h"

class CNetWaterMarkServerData;

class CNetWaterMarkServerCarry final : public InforGuard_::NetWaterMark::Service
{
public:
	CNetWaterMarkServerCarry(CNetWaterMarkServerData *p);
	~CNetWaterMarkServerCarry();

public:
	virtual ::grpc::Status Check(::grpc::ServerContext* context, const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response);
	virtual ::grpc::Status Set(::grpc::ServerContext* context, const ::InforGuard_::SetReq* request, ::InforGuard_::SetRes* response);
	virtual ::grpc::Status Get(::grpc::ServerContext* context, const ::InforGuard_::GetReq* request, ::InforGuard_::GetRes* response);
	virtual ::grpc::Status Add(::grpc::ServerContext* context, const ::InforGuard_::AddReq* request, ::InforGuard_::AddRes* response);
	virtual ::grpc::Status Remove(::grpc::ServerContext* context, const ::InforGuard_::RemoveReq* request, ::InforGuard_::RemoveRes* response);
	virtual ::grpc::Status Rename(::grpc::ServerContext* context, const ::InforGuard_::RenameReq* request, ::InforGuard_::RenameRes* response);
	virtual ::grpc::Status Verify(::grpc::ServerContext* context, const ::InforGuard_::VerifyReq* request, ::InforGuard_::VerifyRes* response);
	virtual ::grpc::Status VerifyForFilter(::grpc::ServerContext* context, const ::InforGuard_::VerifyForFilterReq* request, ::InforGuard_::VerifyForFilterRes* response);
	virtual ::grpc::Status RequestResume(::grpc::ServerContext* context, const ::InforGuard_::RequestResumeReq* request, ::InforGuard_::RequestResumeRes* response);

private:
	CNetWaterMarkServerData *m_Data;
};