#include "Client/FileTran/FileTranClientCarry.h"

#include "Client/GRPCChannel.h"
#include "PubUtil/DataExchange.h"

CFileTranClientCarry::
CFileTranClientCarry(CGRPCChannel *p)
{
	m_Stub = nullptr;
	m_Channel = p;
}


CFileTranClientCarry::
~CFileTranClientCarry()
{
	//...
}

bool 
CFileTranClientCarry::
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
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
CFileTranClientCarry::
GetFileBlock(const string &conn, const ::InforGuard_::GetFileBlockReq& request, ::InforGuard_::GetFileBlockRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->GetFileBlock(&context, request, response);
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
CFileTranClientCarry::
PutFileBlock(const string &conn, const ::InforGuard_::PutFileBlockReq& request, ::InforGuard_::PutFileBlockRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->PutFileBlock(&context, request, response);
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
CFileTranClientCarry::
MakeDirectory(const string &conn, const ::InforGuard_::MakeDirectoryReq& request, ::InforGuard_::MakeDirectoryRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->MakeDirectory(&context, request, response);
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
CFileTranClientCarry::
MoveFileIn(const string &conn, const ::InforGuard_::MoveFileInReq& request, ::InforGuard_::MoveFileInRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->MoveFileIn(&context, request, response);
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
CFileTranClientCarry::
MoveFileOut(const string &conn, const ::InforGuard_::MoveFileOutReq& request, ::InforGuard_::MoveFileOutRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->MoveFileOut(&context, request, response);
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
CFileTranClientCarry::
RenameFile(const string &conn, const ::InforGuard_::RenameFileReq& request, ::InforGuard_::RenameFileRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->RenameFile(&context, request, response);
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
CFileTranClientCarry::
QueryBasePath(const string &conn, const ::InforGuard_::QueryBasePathReq& request, ::InforGuard_::QueryBasePathRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->QueryBasePath(&context, request, response);
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
CFileTranClientCarry::
isFileExist(const string &conn, const ::InforGuard_::isFileExistReq& request, ::InforGuard_::isFileExistRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->isFileExist(&context, request, response);
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
CFileTranClientCarry::
setFileTime(const string &conn, const ::InforGuard_::setFileTimeReq& request, ::InforGuard_::setFileTimeRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->setFileTime(&context, request, response);
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
CFileTranClientCarry::
getFileTime(const string &conn, const ::InforGuard_::getFileTimeReq& request, ::InforGuard_::getFileTimeRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->getFileTime(&context, request, response);
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
CFileTranClientCarry::
sendFileList(const string &conn, const ::InforGuard_::sendFileListReq& request, ::InforGuard_::sendFileListRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->sendFileList(&context, request, response);
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
CFileTranClientCarry::
sendAccess(const string &conn, const ::InforGuard_::sendAccessReq& request, ::InforGuard_::sendAccessRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->sendAccess(&context, request, response);
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
CFileTranClientCarry::
checkFileList(const string &conn, const ::InforGuard_::checkFileListReq& request, ::InforGuard_::checkFileListRes* response)
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
		m_Stub = InforGuard_::FileTran::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->checkFileList(&context, request, response);
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