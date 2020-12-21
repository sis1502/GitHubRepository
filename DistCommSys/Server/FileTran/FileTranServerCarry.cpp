#include "Server/FileTran/FileTranServerCarry.h"

#include "Server/FileTran/FileTranServerData.h"

CFileTranServerCarry::
CFileTranServerCarry(CFileTranServerData *p)
{
	m_Data = p;
}


CFileTranServerCarry::
~CFileTranServerCarry()
{
	//...
}

::grpc::Status 
CFileTranServerCarry::
Check(::grpc::ServerContext* context, const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response)
{
	if (m_Data->Check(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
GetFileBlock(::grpc::ServerContext* context, const ::InforGuard_::GetFileBlockReq* request, ::InforGuard_::GetFileBlockRes* response)
{
	if (m_Data->GetFileBlock(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
PutFileBlock(::grpc::ServerContext* context, const ::InforGuard_::PutFileBlockReq* request, ::InforGuard_::PutFileBlockRes* response)
{
	if (m_Data->PutFileBlock(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
MakeDirectory(::grpc::ServerContext* context, const ::InforGuard_::MakeDirectoryReq* request, ::InforGuard_::MakeDirectoryRes* response)
{
	if (m_Data->MakeDirectory(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
MoveFileIn(::grpc::ServerContext* context, const ::InforGuard_::MoveFileInReq* request, ::InforGuard_::MoveFileInRes* response)
{
	if (m_Data->MoveFileIn(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
MoveFileOut(::grpc::ServerContext* context, const ::InforGuard_::MoveFileOutReq* request, ::InforGuard_::MoveFileOutRes* response)
{
	if (m_Data->MoveFileOut(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
RenameFile(::grpc::ServerContext* context, const ::InforGuard_::RenameFileReq* request, ::InforGuard_::RenameFileRes* response)
{
	if (m_Data->RenameFile(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
QueryBasePath(::grpc::ServerContext* context, const ::InforGuard_::QueryBasePathReq* request, ::InforGuard_::QueryBasePathRes* response)
{
	if (m_Data->QueryBasePath(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
isFileExist(::grpc::ServerContext* context, const ::InforGuard_::isFileExistReq* request, ::InforGuard_::isFileExistRes* response)
{
	if (m_Data->isFileExist(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
setFileTime(::grpc::ServerContext* context, const ::InforGuard_::setFileTimeReq* request, ::InforGuard_::setFileTimeRes* response)
{
	if (m_Data->setFileTime(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
getFileTime(::grpc::ServerContext* context, const ::InforGuard_::getFileTimeReq* request, ::InforGuard_::getFileTimeRes* response)
{
	if (m_Data->getFileTime(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
sendFileList(::grpc::ServerContext* context, const ::InforGuard_::sendFileListReq* request, ::InforGuard_::sendFileListRes* response)
{
	if (m_Data->sendFileList(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
sendAccess(::grpc::ServerContext* context, const ::InforGuard_::sendAccessReq* request, ::InforGuard_::sendAccessRes* response)
{
	if (m_Data->sendAccess(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}

::grpc::Status 
CFileTranServerCarry::
checkFileList(::grpc::ServerContext* context, const ::InforGuard_::checkFileListReq* request, ::InforGuard_::checkFileListRes* response)
{
	if (m_Data->checkFileList(request, response))
	{
		return ::grpc::Status::OK;
	}

	return ::grpc::Status::CANCELLED;
}