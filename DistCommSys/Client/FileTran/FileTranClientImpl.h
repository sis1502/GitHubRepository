#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CFileTranClientData;

class CFileTranClientImpl
{
public:
	CFileTranClientImpl(CFileTranClientData *p);
	~CFileTranClientImpl();

public:
	int Check(const string &ip, const string &port);

	int GetFileBlock(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filename,
		const long long &off,
		string &buff,
		long &len);

	int PutFileBlock(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filename,
		const long long &off,
		const string &buff,
		long &len);

	int MakeDirectory(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filename,
		const bool &temp);

	int MoveFileIn(const string &ip, const string &port,
		st_NetCallData &call,
		const string &srcfile,
		const string &dstfile,
		const string &delfile,
		const bool &bTopPath);

	int MoveFileOut(const string &ip, const string &port,
		st_NetCallData &call,
		const string &srcfile,
		const string &dstfile);

	int RenameFile(const string &ip, const string &port,
		st_NetCallData &call,
		const string &oldfile,
		const string &newfile,
		const long &attr);

	int QueryBasePath(const string &ip, const string &port, string &basepath);

	int isFileExist(const string &ip, const string &port,
		const string &filePath,
		long &fileSize);

	int setFileTime(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filename, 
		const long &mtime);

	int getFileTime(const string &ip, const string &port,
		st_NetCallData &call,
		const string &filename,
		long &mtime);

	int sendFileList(const string &ip, const string &port, const RemoteDirectoryList &list);

	int sendAccess(const string &ip, const string &port);

	int checkFileList(const string &ip, const string &port,
		const NetFileList &inList,
		ParamList &notExistList,
		ParamList &diffList);

private:
	CFileTranClientData *m_Data;
};

