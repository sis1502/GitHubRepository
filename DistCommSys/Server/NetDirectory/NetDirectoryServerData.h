#pragma once

#include "grpc_Generated/NetDirectory.grpc.pb.h"

class CNetDirectoryServerImpl;

class CNetDirectoryServerData final
{
public:
	CNetDirectoryServerData(CNetDirectoryServerImpl *p);
	~CNetDirectoryServerData();

public:
	bool Check(const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response);
	bool GetTree(const ::InforGuard_::GetTreeReq* request, ::InforGuard_::GetTreeRes* response);
	bool GetList(const ::InforGuard_::GetListReq* request, ::InforGuard_::GetListRes* response);
	bool GetTreeEx(const ::InforGuard_::GetTreeExReq* request, ::InforGuard_::GetTreeExRes* response);
	bool GetListEx(const ::InforGuard_::GetListExReq* request, ::InforGuard_::GetListExRes* response);

private:
	CNetDirectoryServerImpl *m_Impl;
};

