#include "Server/NetConfig/NetConfigServerCarry.h"

#include "Server/NetConfig/NetConfigServerData.h"

CNetConfigServerCarry::
CNetConfigServerCarry(CNetConfigServerData *p)
{
	m_Data = p;
}


CNetConfigServerCarry::
~CNetConfigServerCarry()
{
	//...
}

::grpc::Status 
CNetConfigServerCarry::
Load(::grpc::ServerContext* context, const ::InforGuard_::LoadReq* request, ::InforGuard_::LoadRes* response)
{
	if (m_Data->Load(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetConfigServerCarry::
Save(::grpc::ServerContext* context, const ::InforGuard_::SaveReq* request, ::InforGuard_::SaveRes* response)
{
	if (m_Data->Save(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}