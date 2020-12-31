#pragma once

#include "PubUtil/BaseDef.h"

#include "FileTran.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class CGRPCChannel;

class CFileTranClientCarry final
{
public:
	CFileTranClientCarry(CGRPCChannel *p);
	~CFileTranClientCarry();

public:
	bool Check(const string &conn, const ::InforGuard_::CheckReq& request, ::InforGuard_::CheckRes* response);
	bool GetFileBlock(const string &conn, const ::InforGuard_::GetFileBlockReq& request, ::InforGuard_::GetFileBlockRes* response);
	bool PutFileBlock(const string &conn, const ::InforGuard_::PutFileBlockReq& request, ::InforGuard_::PutFileBlockRes* response);
	bool MakeDirectory(const string &conn, const ::InforGuard_::MakeDirectoryReq& request, ::InforGuard_::MakeDirectoryRes* response);
	bool MoveFileIn(const string &conn, const ::InforGuard_::MoveFileInReq& request, ::InforGuard_::MoveFileInRes* response);
	bool MoveFileOut(const string &conn, const ::InforGuard_::MoveFileOutReq& request, ::InforGuard_::MoveFileOutRes* response);
	bool RenameFile(const string &conn, const ::InforGuard_::RenameFileReq& request, ::InforGuard_::RenameFileRes* response);
	bool QueryBasePath(const string &conn, const ::InforGuard_::QueryBasePathReq& request, ::InforGuard_::QueryBasePathRes* response);
	bool isFileExist(const string &conn, const ::InforGuard_::isFileExistReq& request, ::InforGuard_::isFileExistRes* response);
	bool setFileTime(const string &conn, const ::InforGuard_::setFileTimeReq& request, ::InforGuard_::setFileTimeRes* response);
	bool getFileTime(const string &conn, const ::InforGuard_::getFileTimeReq& request, ::InforGuard_::getFileTimeRes* response);
	bool sendFileList(const string &conn, const ::InforGuard_::sendFileListReq& request, ::InforGuard_::sendFileListRes* response);
	bool sendAccess(const string &conn, const ::InforGuard_::sendAccessReq& request, ::InforGuard_::sendAccessRes* response);
	bool checkFileList(const string &conn, const ::InforGuard_::checkFileListReq& request, ::InforGuard_::checkFileListRes* response);

private:
	unique_ptr<InforGuard_::FileTran::Stub> m_Stub;

private:
	CGRPCChannel *m_Channel;

private:
	unsigned int m_RetryCount;
	time_t m_RetryInterval;
	time_t m_Timeout;
};

