#pragma once

#include "NetConfig.grpc.pb.h"

class CNetConfigServerImpl;

class CNetConfigServerData final
{
public:
	CNetConfigServerData(CNetConfigServerImpl *p);
	~CNetConfigServerData();

public:
	bool Load(const ::InforGuard_::LoadReq* request, ::InforGuard_::LoadRes* response);
	bool Save(const ::InforGuard_::SaveReq* request, ::InforGuard_::SaveRes* response);

private:
	CNetConfigServerImpl *m_Impl;
};

