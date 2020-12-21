#include "Server/NetDirectory/NetDirectoryServerCarry.h"

#include "Server/NetDirectory/NetDirectoryServerData.h"

CNetDirectoryServerCarry::
CNetDirectoryServerCarry(CNetDirectoryServerData *p)
{
	m_Data = p;
}


CNetDirectoryServerCarry::
~CNetDirectoryServerCarry()
{
	//...
}

::grpc::Status 
CNetDirectoryServerCarry::
Check(::grpc::ServerContext* context, const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response)
{
	if (m_Data->Check(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetDirectoryServerCarry::
GetTree(::grpc::ServerContext* context, const ::InforGuard_::GetTreeReq* request, ::InforGuard_::GetTreeRes* response)
{
	if (m_Data->GetTree(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetDirectoryServerCarry::
GetList(::grpc::ServerContext* context, const ::InforGuard_::GetListReq* request, ::InforGuard_::GetListRes* response)
{
	if (m_Data->GetList(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetDirectoryServerCarry::
GetTreeEx(::grpc::ServerContext* context, const ::InforGuard_::GetTreeExReq* request, ::InforGuard_::GetTreeExRes* response)
{
	if (m_Data->GetTreeEx(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CNetDirectoryServerCarry::
GetListEx(::grpc::ServerContext* context, const ::InforGuard_::GetListExReq* request, ::InforGuard_::GetListExRes* response)
{
	if (m_Data->GetListEx(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}
