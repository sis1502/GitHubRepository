#pragma once

#include "PubUtil/BaseDef.h"

#include "grpc_Generated/FileTran.grpc.pb.h"

class CFileTranServerImpl;

class CFileTranServerData final
{
public:
	CFileTranServerData(CFileTranServerImpl *p);
	~CFileTranServerData();

public:
	bool Check(const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response);
	bool GetFileBlock(const ::InforGuard_::GetFileBlockReq* request, ::InforGuard_::GetFileBlockRes* response);
	bool PutFileBlock(const ::InforGuard_::PutFileBlockReq* request, ::InforGuard_::PutFileBlockRes* response);
	bool MakeDirectory(const ::InforGuard_::MakeDirectoryReq* request, ::InforGuard_::MakeDirectoryRes* response);
	bool MoveFileIn(const ::InforGuard_::MoveFileInReq* request, ::InforGuard_::MoveFileInRes* response);
	bool MoveFileOut(const ::InforGuard_::MoveFileOutReq* request, ::InforGuard_::MoveFileOutRes* response);
	bool RenameFile(const ::InforGuard_::RenameFileReq* request, ::InforGuard_::RenameFileRes* response);
	bool QueryBasePath(const ::InforGuard_::QueryBasePathReq* request, ::InforGuard_::QueryBasePathRes* response);
	bool isFileExist(const ::InforGuard_::isFileExistReq* request, ::InforGuard_::isFileExistRes* response);
	bool setFileTime(const ::InforGuard_::setFileTimeReq* request, ::InforGuard_::setFileTimeRes* response);
	bool getFileTime(const ::InforGuard_::getFileTimeReq* request, ::InforGuard_::getFileTimeRes* response);
	bool sendFileList(const ::InforGuard_::sendFileListReq* request, ::InforGuard_::sendFileListRes* response);
	bool sendAccess(const ::InforGuard_::sendAccessReq* request, ::InforGuard_::sendAccessRes* response);
	bool checkFileList(const ::InforGuard_::checkFileListReq* request, ::InforGuard_::checkFileListRes* response);


private:
	CFileTranServerImpl *m_Impl;
};