#include "Server/NetDirectory/NetDirectoryServerData.h"

#include "Server/NetDirectory/NetDirectoryServerImpl.h"
#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

CNetDirectoryServerData::
CNetDirectoryServerData(CNetDirectoryServerImpl *p)
{
	m_Impl = p;
}


CNetDirectoryServerData::
~CNetDirectoryServerData()
{
	//...
}

bool 
CNetDirectoryServerData::
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
CNetDirectoryServerData::
GetTree(const ::InforGuard_::GetTreeReq* request, ::InforGuard_::GetTreeRes* response)
{
	st_NetCallData call;
	HostChain seqIpPort;
	NetFileTreeList treenode;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->GetTree(call,seqIpPort, request->remotefoldername(), request->mode(), treenode, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** treenode
	NetFileTreeList::iterator it_N = treenode.begin();
	while (it_N != treenode.end())
	{
		::InforGuard_::NetFileTreeNode *node = response->add_treenode();
		node->set_name(it_N->name);
		node->set_size(it_N->size);
		node->set_time(it_N->time);
		node->set_isfolder(it_N->isfolder);
		++it_N;
	}

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetDirectoryServerData::
GetList(const ::InforGuard_::GetListReq* request, ::InforGuard_::GetListRes* response)
{
	st_NetCallData call;
	HostChain seqIpPort;
	NetFileList filelist;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_REQUEST__

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->GetList(call, seqIpPort, request->remotefoldername(), request->mode(), filelist, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** call
	__DATACOPY_SERVER_NETCALLDATA_RESPONSE__

	//** filelist
	::InforGuard_::NetFileListNode *node = response->add_filelist();
	NetFileList::iterator it_N = filelist.begin();
	while (it_N != filelist.end())
	{
		node->set_name(it_N->name);
		node->set_size(it_N->size);
		node->set_time(it_N->time);
		node->set_isfolder(it_N->isfolder);
		++it_N;
	}

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetDirectoryServerData::
GetTreeEx(const ::InforGuard_::GetTreeExReq* request, ::InforGuard_::GetTreeExRes* response)
{
	HostChain seqIpPort;
	NetFileTreeList treenode;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->GetTreeEx(seqIpPort, request->remotefoldername(), request->mode(), treenode, ex));

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** treenode
	NetFileTreeList::iterator it_N = treenode.begin();
	while (it_N != treenode.end())
	{
		::InforGuard_::NetFileTreeNode *node = response->add_treenode();
		node->set_name(it_N->name);
		node->set_size(it_N->size);
		node->set_time(it_N->time);
		node->set_isfolder(it_N->isfolder);
		++it_N;
	}

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}

bool 
CNetDirectoryServerData::
GetListEx(const ::InforGuard_::GetListExReq* request, ::InforGuard_::GetListExRes* response)
{
	HostChain seqIpPort;
	NetFileList filelist;
	st_ExceptionError ex;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		�������������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_SERVER_HOSTCHAIN_REQUEST__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	response->set_ret(m_Impl->GetListEx(seqIpPort, request->remotefoldername(), request->mode(), filelist, ex));
	
	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		��Ӧ���������
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** filelist
	::InforGuard_::NetFileListNode *node = response->add_filelist();
	NetFileList::iterator it_N = filelist.begin();
	while (it_N != filelist.end())
	{
		node->set_name(it_N->name);
		node->set_size(it_N->size);
		node->set_time(it_N->time);
		node->set_isfolder(it_N->isfolder);
		++it_N;
	}

	//** �쳣��Ϣ���
	__DATAEXCEPTION_SERVER_STUFF__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return true;
}