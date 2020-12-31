#pragma once

#include "NetWaterMark.grpc.pb.h"

class CNetWaterMarkServerImpl;

class CNetWaterMarkServerData final
{
public:
	CNetWaterMarkServerData(CNetWaterMarkServerImpl *p);
	~CNetWaterMarkServerData();

public:
	bool Check(const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response);
	bool Set(const ::InforGuard_::SetReq* request, ::InforGuard_::SetRes* response);
	bool Get(const ::InforGuard_::GetReq* request, ::InforGuard_::GetRes* response);
	bool Add(const ::InforGuard_::AddReq* request, ::InforGuard_::AddRes* response);
	bool Remove(const ::InforGuard_::RemoveReq* request, ::InforGuard_::RemoveRes* response);
	bool Rename(const ::InforGuard_::RenameReq* request, ::InforGuard_::RenameRes* response);
	bool Verify(const ::InforGuard_::VerifyReq* request, ::InforGuard_::VerifyRes* response);
	bool VerifyForFilter(const ::InforGuard_::VerifyForFilterReq* request, ::InforGuard_::VerifyForFilterRes* response);
	bool RequestResume(const ::InforGuard_::RequestResumeReq* request, ::InforGuard_::RequestResumeRes* response);

private:
	CNetWaterMarkServerImpl *m_Impl;
};

