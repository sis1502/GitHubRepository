#pragma once

#include "PubUtil/BaseDef.h"

#include "FileTran.grpc.pb.h"

class CFileTranServerData;

class CFileTranServerCarry final : public InforGuard_::FileTran::Service
{
public:
	CFileTranServerCarry(CFileTranServerData *p);
	~CFileTranServerCarry();

public:
	virtual ::grpc::Status Check(::grpc::ServerContext* context, const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response);
	virtual ::grpc::Status GetFileBlock(::grpc::ServerContext* context, const ::InforGuard_::GetFileBlockReq* request, ::InforGuard_::GetFileBlockRes* response);
	virtual ::grpc::Status PutFileBlock(::grpc::ServerContext* context, const ::InforGuard_::PutFileBlockReq* request, ::InforGuard_::PutFileBlockRes* response);
	virtual ::grpc::Status MakeDirectory(::grpc::ServerContext* context, const ::InforGuard_::MakeDirectoryReq* request, ::InforGuard_::MakeDirectoryRes* response);
	virtual ::grpc::Status MoveFileIn(::grpc::ServerContext* context, const ::InforGuard_::MoveFileInReq* request, ::InforGuard_::MoveFileInRes* response);
	virtual ::grpc::Status MoveFileOut(::grpc::ServerContext* context, const ::InforGuard_::MoveFileOutReq* request, ::InforGuard_::MoveFileOutRes* response);
	virtual ::grpc::Status RenameFile(::grpc::ServerContext* context, const ::InforGuard_::RenameFileReq* request, ::InforGuard_::RenameFileRes* response);
	virtual ::grpc::Status QueryBasePath(::grpc::ServerContext* context, const ::InforGuard_::QueryBasePathReq* request, ::InforGuard_::QueryBasePathRes* response);
	virtual ::grpc::Status isFileExist(::grpc::ServerContext* context, const ::InforGuard_::isFileExistReq* request, ::InforGuard_::isFileExistRes* response);
	virtual ::grpc::Status setFileTime(::grpc::ServerContext* context, const ::InforGuard_::setFileTimeReq* request, ::InforGuard_::setFileTimeRes* response);
	virtual ::grpc::Status getFileTime(::grpc::ServerContext* context, const ::InforGuard_::getFileTimeReq* request, ::InforGuard_::getFileTimeRes* response);
	virtual ::grpc::Status sendFileList(::grpc::ServerContext* context, const ::InforGuard_::sendFileListReq* request, ::InforGuard_::sendFileListRes* response);
	virtual ::grpc::Status sendAccess(::grpc::ServerContext* context, const ::InforGuard_::sendAccessReq* request, ::InforGuard_::sendAccessRes* response);
	virtual ::grpc::Status checkFileList(::grpc::ServerContext* context, const ::InforGuard_::checkFileListReq* request, ::InforGuard_::checkFileListRes* response);

private:
	CFileTranServerData *m_Data;
};