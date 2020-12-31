#pragma once

#include "NetDirectory.grpc.pb.h"

class CNetDirectoryServerData;

class CNetDirectoryServerCarry final : public InforGuard_::NetDirectory::Service
{
public:
	CNetDirectoryServerCarry(CNetDirectoryServerData *p);
	~CNetDirectoryServerCarry();

public:
	virtual ::grpc::Status Check(::grpc::ServerContext* context, const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response);
	virtual ::grpc::Status GetTree(::grpc::ServerContext* context, const ::InforGuard_::GetTreeReq* request, ::InforGuard_::GetTreeRes* response);
	virtual ::grpc::Status GetList(::grpc::ServerContext* context, const ::InforGuard_::GetListReq* request, ::InforGuard_::GetListRes* response);
	virtual ::grpc::Status GetTreeEx(::grpc::ServerContext* context, const ::InforGuard_::GetTreeExReq* request, ::InforGuard_::GetTreeExRes* response);
	virtual ::grpc::Status GetListEx(::grpc::ServerContext* context, const ::InforGuard_::GetListExReq* request, ::InforGuard_::GetListExRes* response);

private:
	CNetDirectoryServerData *m_Data;
};