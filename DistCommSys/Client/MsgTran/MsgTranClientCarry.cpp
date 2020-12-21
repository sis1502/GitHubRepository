#include "Client/MsgTran/MsgTranClientCarry.h"

#include "Client/GRPCChannel.h"
#include "PubUtil/DataExchange.h"

CMsgTranClientCarry::
CMsgTranClientCarry(CGRPCChannel *p)
{
	m_Channel = p;
}


CMsgTranClientCarry::
~CMsgTranClientCarry()
{
	//...
}

bool 
CMsgTranClientCarry::
GetMessage(const string &conn, const ::InforGuard_::GetMsgReq& request, ::InforGuard_::GetMsgRes* response)
{
	if (!m_Stub)
	{
		shared_ptr<::grpc::ChannelInterface> channel;
		if (!m_Channel->GetChannel(conn, channel))
		{
#		ifdef _CONSOLE
			cout << conn << " Connect FAILED" << endl;
#		endif
			//填充响应数据中的异常：连接服务失败
			__BADCHANNELEXCEPTION_STUFF__

			return false;
		}
		m_Stub = InforGuard_::MsgTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->GetMsg(&context, request, response);
	if (status.ok())
	{
		return true;
	}
	else
	{
		//填充响应数据中的异常：调用远程接口失败
		__BADSTUBEXCEPTION_STUFF__

		return false;
	}
}

bool 
CMsgTranClientCarry::
PutMessage(const string &conn, const ::InforGuard_::PutMsgReq& request, ::InforGuard_::PutMsgRes* response)
{
	if (!m_Stub)
	{
		shared_ptr<::grpc::ChannelInterface> channel;
		if (!m_Channel->GetChannel(conn, channel))
		{
#		ifdef _CONSOLE
			cout << conn << " Connect FAILED" << endl;
#		endif
			//填充响应数据中的异常：连接服务失败
			__BADCHANNELEXCEPTION_STUFF__

			return false;
		}
		m_Stub = InforGuard_::MsgTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->PutMsg(&context, request, response);
	if (status.ok())
	{
		return true;
	}
	else
	{
		//填充响应数据中的异常：调用远程接口失败
		__BADSTUBEXCEPTION_STUFF__

		return false;
	}
}