#pragma once

#include "PubUtil/DataExchange.h"

class CFileTranClientCarry;

class CFileTranClientData final
{
public:
	CFileTranClientData(CFileTranClientCarry *p);
	~CFileTranClientData();

public:
	bool Check(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		//��
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool GetFileBlock(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const __int64 off,
		const __int32 req_len,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		string &buff,
		__int32 &res_len,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool PutFileBlock(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const __int64 off,
		const string &buff,
		const __int32 req_len,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &res_len,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool MakeDirectory(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const bool &temp,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool MoveFileIn(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &srcfile,
		const string &dstfile,
		const string &delfile,
		const bool &bTopPath,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool MoveFileOut(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &srcfile,
		const string &dstfile,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool RenameFile(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &oldfile,
		const string &newfile,
		const __int32 &attr,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool QueryBasePath(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		//��
		/*	��Ӧ����	*/
		string &basepath,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool isFileExist(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const string &filePath,
		/*	��Ӧ����	*/
		__int32 &fileSize,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool setFileTime(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		const __int32 &mtime,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool getFileTime(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::st_NetCallData &req_call,
		const string &filename,
		/*	��Ӧ����	*/
		DistCommSysData_::st_NetCallData &res_call,
		__int32 &mtime,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool sendFileList(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::RemoteDirectoryList &list,
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool sendAccess(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		//��
		/*	��Ӧ����	*/
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

	bool checkFileList(
		/*	�̶�����	*/
		const string &conn,
		/*	��������	*/
		const DistCommSysData_::NetFileList &inList,
		/*	��Ӧ����	*/
		DistCommSysData_::ParamList &notExistList,
		DistCommSysData_::ParamList &diffList,
		__int32 &ret,
		DistCommSysData_::st_ExceptionError &ex);

private:
	CFileTranClientCarry *m_Carry;
};

