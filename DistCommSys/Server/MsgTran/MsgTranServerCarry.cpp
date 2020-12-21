#include "Server/MsgTran/MsgTranServerCarry.h"

#include "Server/MsgTran/MsgTranServerData.h"

CMsgTranServerCarry::
CMsgTranServerCarry(CMsgTranServerData *p)
{
	m_Data = p;
}


CMsgTranServerCarry::
~CMsgTranServerCarry()
{
	//...
}

::grpc::Status 
CMsgTranServerCarry::
GetMessage(::grpc::ServerContext* context, const ::InforGuard_::GetMsgReq* request, ::InforGuard_::GetMsgRes* response)
{
	if (m_Data->GetMessage(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CMsgTranServerCarry::
PutMessage(::grpc::ServerContext* context, const ::InforGuard_::PutMsgReq* request, ::InforGuard_::PutMsgRes* response)
{
	if (m_Data->PutMessage(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}
