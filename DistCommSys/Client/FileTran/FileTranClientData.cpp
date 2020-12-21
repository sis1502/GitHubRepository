#include "Client/FileTran/FileTranClientData.h"

#include "Client/FileTran/FileTranClientCarry.h"

using namespace DistCommSysData_;

CFileTranClientData::
CFileTranClientData(CFileTranClientCarry *p)
{
	m_Carry = p;
}

CFileTranClientData::
~CFileTranClientData()
{
	//...
}

bool 
CFileTranClientData::
Check(const string &conn, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::CheckReq request;
	::InforGuard_::CheckRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	request.set_check(true);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->Check(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
GetFileBlock(const string &conn,
	const st_NetCallData &req_call,
	const string &filename,
	const __int64 off,
	const __int32 req_len,
	st_NetCallData &res_call,
	string &buff,
	__int32 &res_len,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetFileBlockReq request;
	::InforGuard_::GetFileBlockRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */
	
	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__
#ifdef _CONSOLE
	req_call.Display();
#endif

	//** filename
	request.set_filename(filename);
#ifdef _CONSOLE
	cout << "filename:" << filename << endl;
#endif

	//** off
	request.set_off(off);
#ifdef _CONSOLE
	cout << "off:" << off << endl;
#endif

	//** len
	request.set_len(req_len);
#ifdef _CONSOLE
	cout << "req_len:" << req_len << endl;
#endif

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->GetFileBlock(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** buff
	buff = response.buff();

	//** len
	res_len = response.len();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
PutFileBlock(const string &conn,
	const st_NetCallData &req_call,
	const string &filename,
	const __int64 off,
	const string &buff,
	const __int32 req_len,
	st_NetCallData &res_call,
	__int32 &res_len,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::PutFileBlockReq request;
	::InforGuard_::PutFileBlockRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** filename
	request.set_filename(filename);

	//** off
	request.set_off(off);

	//** buff
	request.set_buff(buff);

	//** len
	request.set_len(req_len);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->PutFileBlock(conn, request, &response);
	
	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** len
	res_len = response.len();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
MakeDirectory(const string &conn,
	const st_NetCallData &req_call,
	const string &filename,
	const bool &temp,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::MakeDirectoryReq request;
	::InforGuard_::MakeDirectoryRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** filename
	request.set_filename(filename);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->MakeDirectory(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
MoveFileIn(const string &conn,
	const st_NetCallData &req_call,
	const string &srcfile,
	const string &dstfile,
	const string &delfile,
	const bool &bTopPath,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::MoveFileInReq request;
	::InforGuard_::MoveFileInRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** srcfile
	request.set_srcfile(srcfile);

	//** dstfile
	request.set_dstfile(dstfile);

	//** delfile
	request.set_delfile(delfile);

	//** bTopPath
	request.set_btoppath(bTopPath);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->MoveFileIn(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
MoveFileOut(const string &conn,
	const st_NetCallData &req_call,
	const string &srcfile,
	const string &dstfile,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::MoveFileOutReq request;
	::InforGuard_::MoveFileOutRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** srcfile
	request.set_srcfile(srcfile);

	//** dstfile
	request.set_dstfile(dstfile);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->MoveFileOut(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
RenameFile(const string &conn,
	const st_NetCallData &req_call,
	const string &oldfile,
	const string &newfile,
	const __int32 &attr,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::RenameFileReq request;
	::InforGuard_::RenameFileRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** oldfile
	request.set_oldfile(oldfile);

	//** newfile
	request.set_newfile(newfile);

	//** attr
	request.set_attr(attr);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->RenameFile(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;}

bool 
CFileTranClientData::
QueryBasePath(const string &conn, string &basepath, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::QueryBasePathReq request;
	::InforGuard_::QueryBasePathRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	request.set_req(true);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->QueryBasePath(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** basepath
	basepath = response.basepath();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranClientData::
isFileExist(const string &conn, const string &filePath, __int32 &fileSize, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::isFileExistReq request;
	::InforGuard_::isFileExistRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** filePath
	request.set_filepath(filePath);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->isFileExist(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** fileSize
	fileSize = response.filesize();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
setFileTime(const string &conn,
	const st_NetCallData &req_call,
	const string &filename,
	const __int32 &mtime,
	st_NetCallData &res_call,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::setFileTimeReq request;
	::InforGuard_::setFileTimeRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** filename
	request.set_filename(filename);

	//** mtime
	request.set_mtime(mtime);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->setFileTime(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool
CFileTranClientData::
getFileTime(const string &conn,
	const st_NetCallData &req_call,
	const string &filename,
	st_NetCallData &res_call,
	__int32 &mtime,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::getFileTimeReq request;
	::InforGuard_::getFileTimeRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** filename
	request.set_filename(filename);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->getFileTime(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** mtime
	mtime = response.mtime();

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranClientData::
sendFileList(const string &conn, const DistCommSysData_::RemoteDirectoryList &list, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::sendFileListReq request;
	::InforGuard_::sendFileListRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** list
	DistCommSysData_::RemoteDirectoryList::const_iterator it_R = list.begin();
	while (it_R != list.end())
	{
		InforGuard_::RemoteDirectory *pDirs = request.add_list();
		pDirs->set_id(it_R->id);

		vector<st_FileNodeInfo>::const_iterator it_F = (it_R->list).begin();
		while (it_F != (it_R->list).end())
		{
			InforGuard_::s_FileNodeInfo *pNode = pDirs->add_nodes();
			pNode->set_name(it_F->name);
			pNode->set_isfile(it_F->isfile);
			pNode->set_mtime(it_F->mtime);
			pNode->set_type(it_F->type);
			++it_F;
		}
		++it_R;
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->sendFileList(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranClientData::
sendAccess(const string &conn, __int32 &ret, st_ExceptionError &ex)
{
	::InforGuard_::sendAccessReq request;
	::InforGuard_::sendAccessRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	request.set_req(true);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->sendAccess(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranClientData::
checkFileList(const string &conn,
	const DistCommSysData_::NetFileList &inList,
	DistCommSysData_::ParamList &notExistList,
	DistCommSysData_::ParamList &diffList,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::checkFileListReq request;
	::InforGuard_::checkFileListRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	DistCommSysData_::NetFileList::const_iterator it = inList.begin();
	while (it != inList.end())
	{
		InforGuard_::NetFileListNode *pNode = request.add_inlist();
		pNode->set_name(it->name);
		pNode->set_size(it->size);
		pNode->set_time(it->time);
		pNode->set_isfolder(it->isfolder);
		++it;
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	m_Carry->checkFileList(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** notExistList
	::google::protobuf::RepeatedPtrField<string> res_notExistList = response.notexistlist();
	for (auto notExistNode : res_notExistList)
	{
		notExistList.push_back(notExistNode);
	}

	//** diffList
	::google::protobuf::RepeatedPtrField<string> res_diffList = response.difflist();
	for (auto diffNode : res_diffList)
	{
		diffList.push_back(diffNode);
	}

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}
