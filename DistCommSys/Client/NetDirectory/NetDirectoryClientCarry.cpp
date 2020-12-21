#include "Client/NetDirectory/NetDirectoryClientCarry.h"

#include "Client/GRPCChannel.h"
#include "PubUtil/DataExchange.h"

CNetDirectoryClientCarry::
CNetDirectoryClientCarry(CGRPCChannel *p)
{
	m_Channel = p;
}

CNetDirectoryClientCarry::
~CNetDirectoryClientCarry()
{
	//...
}

bool
CNetDirectoryClientCarry::
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
		m_Stub = InforGuard_::NetDirectory::NewStub(channel);
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
CNetDirectoryClientCarry::
GetTree(const string &conn, const ::InforGuard_::GetTreeReq& request, ::InforGuard_::GetTreeRes* response)
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
		m_Stub = InforGuard_::NetDirectory::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->GetTree(&context, request, response);
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
CNetDirectoryClientCarry::
GetList(const string &conn, const ::InforGuard_::GetListReq& request, ::InforGuard_::GetListRes* response)
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
		m_Stub = InforGuard_::NetDirectory::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->GetList(&context, request, response);
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
CNetDirectoryClientCarry::
GetTreeEx(const string &conn, const ::InforGuard_::GetTreeExReq& request, ::InforGuard_::GetTreeExRes* response)
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
		m_Stub = InforGuard_::NetDirectory::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->GetTreeEx(&context, request, response);
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
CNetDirectoryClientCarry::
GetListEx(const string &conn, const ::InforGuard_::GetListExReq& request, ::InforGuard_::GetListExRes* response)
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
		m_Stub = InforGuard_::NetDirectory::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->GetListEx(&context, request, response);
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