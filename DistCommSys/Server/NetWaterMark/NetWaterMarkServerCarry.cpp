#include "Server/NetWaterMark/NetWaterMarkServerCarry.h"

#include "Server/NetWaterMark/NetWaterMarkServerData.h"

CNetWaterMarkServerCarry::
CNetWaterMarkServerCarry(CNetWaterMarkServerData *p)
{
	m_Data = p;
}


CNetWaterMarkServerCarry::
~CNetWaterMarkServerCarry()
{
	//...
}

::grpc::Status 
CNetWaterMarkServerCarry::
Check(::grpc::ServerContext* context, const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response)
{
	if (m_Data->Check(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
Set(::grpc::ServerContext* context, const ::InforGuard_::SetReq* request, ::InforGuard_::SetRes* response)
{
	if (m_Data->Set(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
Get(::grpc::ServerContext* context, const ::InforGuard_::GetReq* request, ::InforGuard_::GetRes* response)
{
	if (m_Data->Get(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
Add(::grpc::ServerContext* context, const ::InforGuard_::AddReq* request, ::InforGuard_::AddRes* response)
{
	if (m_Data->Add(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
Remove(::grpc::ServerContext* context, const ::InforGuard_::RemoveReq* request, ::InforGuard_::RemoveRes* response)
{
	if (m_Data->Remove(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
Rename(::grpc::ServerContext* context, const ::InforGuard_::RenameReq* request, ::InforGuard_::RenameRes* response)
{
	if (m_Data->Rename(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
Verify(::grpc::ServerContext* context, const ::InforGuard_::VerifyReq* request, ::InforGuard_::VerifyRes* response)
{
	if (m_Data->Verify(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
VerifyForFilter(::grpc::ServerContext* context, const ::InforGuard_::VerifyForFilterReq* request, ::InforGuard_::VerifyForFilterRes* response)
{
	if (m_Data->VerifyForFilter(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetWaterMarkServerCarry::
RequestResume(::grpc::ServerContext* context, const ::InforGuard_::RequestResumeReq* request, ::InforGuard_::RequestResumeRes* response)
{
	if (m_Data->RequestResume(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}