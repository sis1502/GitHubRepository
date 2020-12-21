#include "Client/NetWaterMark/NetWaterMarkClientCarry.h"

#include "Client/GRPCChannel.h"
#include "PubUtil/DataExchange.h"

CNetWaterMarkClientCarry::
CNetWaterMarkClientCarry(CGRPCChannel *p)
{
	m_Channel = p;
}

CNetWaterMarkClientCarry::
~CNetWaterMarkClientCarry()
{
	//...
}

bool
CNetWaterMarkClientCarry::
Check(const string &conn, const ::InforGuard_::CheckReq& request, ::InforGuard_::CheckRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Check(&context, request, response);
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
CNetWaterMarkClientCarry::
Set(const string &conn, const ::InforGuard_::SetReq& request, ::InforGuard_::SetRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Set(&context, request, response);
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
CNetWaterMarkClientCarry::
Get(const string &conn, const ::InforGuard_::GetReq& request, ::InforGuard_::GetRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Get(&context, request, response);
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
CNetWaterMarkClientCarry::
Add(const string &conn, const ::InforGuard_::AddReq& request, ::InforGuard_::AddRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Add(&context, request, response);
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
CNetWaterMarkClientCarry::
Remove(const string &conn, const ::InforGuard_::RemoveReq& request, ::InforGuard_::RemoveRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Remove(&context, request, response);
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
CNetWaterMarkClientCarry::
Rename(const string &conn, const ::InforGuard_::RenameReq& request, ::InforGuard_::RenameRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Rename(&context, request, response);
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
CNetWaterMarkClientCarry::
Verify(const string &conn, const ::InforGuard_::VerifyReq& request, ::InforGuard_::VerifyRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Verify(&context, request, response);
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
CNetWaterMarkClientCarry::
VerifyForFilter(const string &conn, const ::InforGuard_::VerifyForFilterReq& request, ::InforGuard_::VerifyForFilterRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->VerifyForFilter(&context, request, response);
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
CNetWaterMarkClientCarry::
RequestResume(const string &conn, const ::InforGuard_::RequestResumeReq& request, ::InforGuard_::RequestResumeRes* response)
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
		m_Stub = InforGuard_::NetWaterMark::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->RequestResume(&context, request, response);
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