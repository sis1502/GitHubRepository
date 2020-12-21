#include "Server/FileTran/FileTranServerData.h"

#include "Server/FileTran/FileTranServerImpl.h"
#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

CFileTranServerData::
CFileTranServerData(CFileTranServerImpl *p)
{
	m_Impl = p;
}

CFileTranServerData::
~CFileTranServerData()
{
	//...
}

bool 
CFileTranServerData::
Check(const ::InforGuard_::CheckReq* request, ::InforGuard_::CheckRes* response)
{
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->Check(ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
GetFileBlock(const ::InforGuard_::GetFileBlockReq* request, ::InforGuard_::GetFileBlockRes* response)
{
	st_NetCallData call;
	__int32 len;
	string buff;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//** len
	len = request->len();

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->GetFileBlock(call, request->filename(), request->off(), len, buff, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** buff
	response->set_buff(buff);

	//** len
	response->set_len(len);

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
PutFileBlock(const ::InforGuard_::PutFileBlockReq* request, ::InforGuard_::PutFileBlockRes* response)
{
	st_NetCallData call;
	__int32 len;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//** len
	len = request->len();

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->PutFileBlock(call, request->filename(), request->off(), len, request->buff(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** len
	response->set_len(len);

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
MakeDirectory(const ::InforGuard_::MakeDirectoryReq* request, ::InforGuard_::MakeDirectoryRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->MakeDirectory(call, request->filename(), request->temp(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
MoveFileIn(const ::InforGuard_::MoveFileInReq* request, ::InforGuard_::MoveFileInRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->MoveFileIn(call, request->srcfile(), request->dstfile(), request->delfile(), request->btoppath(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
MoveFileOut(const ::InforGuard_::MoveFileOutReq* request, ::InforGuard_::MoveFileOutRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->MoveFileOut(call, request->srcfile(), request->dstfile(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
RenameFile(const ::InforGuard_::RenameFileReq* request, ::InforGuard_::RenameFileRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->RenameFile(call, request->oldfile(), request->newfile(), request->attr(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
QueryBasePath(const ::InforGuard_::QueryBasePathReq* request, ::InforGuard_::QueryBasePathRes* response)
{
	string basepath;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->QueryBasePath(basepath, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** basepath
	response->set_basepath(basepath);

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
isFileExist(const ::InforGuard_::isFileExistReq* request, ::InforGuard_::isFileExistRes* response)
{
	__int32 fileSize;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->isFileExist(request->filepath(), fileSize, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** fileSize
	response->set_filesize(fileSize);

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
setFileTime(const ::InforGuard_::setFileTimeReq* request, ::InforGuard_::setFileTimeRes* response)
{
	st_NetCallData call;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->setFileTime(call, request->filename(), request->mtime(), ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
getFileTime(const ::InforGuard_::getFileTimeReq* request, ::InforGuard_::getFileTimeRes* response)
{
	st_NetCallData call;
	__int32 mtime;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->getFileTime(call, request->filename(), mtime, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** mtime
	response->set_mtime(mtime);

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
sendFileList(const ::InforGuard_::sendFileListReq* request, ::InforGuard_::sendFileListRes* response)
{
	RemoteDirectoryList list;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** list
	::google::protobuf::RepeatedPtrField<::InforGuard_::RemoteDirectory> nodes_RD = request->list();
	for (auto node_RD : nodes_RD)
	{
		st_RemoteDirectory tmp_RD;
		tmp_RD.id = node_RD.id();
		::google::protobuf::RepeatedPtrField<::InforGuard_::s_FileNodeInfo> nodes_FN = node_RD.nodes();
		for (auto node_FN : nodes_FN)
		{
			st_FileNodeInfo tmp_FN;
			tmp_FN.name = node_FN.name();
			tmp_FN.isfile = node_FN.isfile();
			tmp_FN.mtime = node_FN.mtime();
			tmp_FN.type = node_FN.type();
			tmp_RD.list.push_back(tmp_FN);
		}
		list.push_back(tmp_RD);
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->sendFileList(list, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
sendAccess(const ::InforGuard_::sendAccessReq* request, ::InforGuard_::sendAccessRes* response)
{
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//...

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->sendAccess(ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CFileTranServerData::
checkFileList(const ::InforGuard_::checkFileListReq* request, ::InforGuard_::checkFileListRes* response)
{
	NetFileList inList;
	ParamList notExistList;
	ParamList diffList;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** inList
	::google::protobuf::RepeatedPtrField<::InforGuard_::NetFileListNode> nodes_FL = request->inlist();
	for (auto node_FL : nodes_FL)
	{
		st_NetFileListNode tmp_FL;
		tmp_FL.name = node_FL.name();
		tmp_FL.size = node_FL.size();
		tmp_FL.time = node_FL.time();
		tmp_FL.isfolder = node_FL.isfolder();
		inList.push_back(tmp_FL);
	}

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->checkFileList(inList, notExistList, diffList, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** notExistList
	vector<string>::iterator it_N = notExistList.begin();
	while (it_N != notExistList.end())
	{
		string *node = response->add_notexistlist();
		node->assign(*it_N);
		++it_N;
	}

	//** diffList
	vector<string>::iterator it_D = diffList.begin();
	while (it_D != diffList.end())
	{
		string *node = response->add_difflist();
		node->assign(*it_D);
		++it_D;
	}

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}