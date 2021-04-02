#include "Client/NetDirectory/NetDirectoryClientData.h"

#include "Client/NetDirectory/NetDirectoryClientCarry.h"

using namespace DistCommSysData_;

CNetDirectoryClientData::
CNetDirectoryClientData(CNetDirectoryClientCarry *p)
{
	m_Carry = p;
}

CNetDirectoryClientData::
~CNetDirectoryClientData()
{
	//...
}

bool
CNetDirectoryClientData::
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

	bool check = m_Carry->Check(conn, request, &response);

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

	return check;
}

bool
CNetDirectoryClientData::
GetTree(const string &conn,
	const st_NetCallData &req_call,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const __int32 &mode,
	st_NetCallData &res_call,
	NetFileTreeList &treenode,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetTreeReq request;
	::InforGuard_::GetTreeRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** remotefoldername
	request.set_remotefoldername(remotefoldername);

	//** mode
	request.set_mode(mode);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->GetTree(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//**treenode
	::google::protobuf::RepeatedPtrField<InforGuard_::NetFileTreeNode> nodes = response.treenode();
	for (auto node : nodes)
	{
		st_NetFileTreeNode node_;
		node_.name = node.name();
		node_.size = node.size();
		node_.time = node.time();
		node_.isfolder = node.isfolder();
		treenode.push_back(node_);
	}

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetDirectoryClientData::
GetList(const string &conn,
	const st_NetCallData &req_call,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const __int32 &mode,
	st_NetCallData &res_call,
	NetFileList &filelist,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetListReq request;
	::InforGuard_::GetListRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_REQUEST__

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** remotefoldername
	request.set_remotefoldername(remotefoldername);

	//** mode
	request.set_mode(mode);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->GetList(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** netCallData
	__DATACOPY_NETCALLDATA_RESPONSE__

	//** filelist
	::google::protobuf::RepeatedPtrField<InforGuard_::NetFileListNode> nodes = response.filelist();
	for (auto node : nodes)
	{
		st_NetFileListNode node_;
		node_.name = node.name();
		node_.size = node.size();
		node_.time = node.time();
		node_.isfolder = node.isfolder();
		filelist.push_back(node_);
	}

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetDirectoryClientData::
GetTreeEx(const string &conn,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const __int32 &mode,
	NetFileTreeList &treenode,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetTreeExReq request;
	::InforGuard_::GetTreeExRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** remotefoldername
	request.set_remotefoldername(remotefoldername);

	//** mode
	request.set_mode(mode);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->GetTreeEx(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//**treenode
	::google::protobuf::RepeatedPtrField<InforGuard_::NetFileTreeNode> nodes = response.treenode();
	for (auto node : nodes)
	{
		st_NetFileTreeNode node_;
		node_.name = node.name();
		node_.size = node.size();
		node_.time = node.time();
		node_.isfolder = node.isfolder();
		treenode.push_back(node_);
	}

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}

bool
CNetDirectoryClientData::
GetListEx(const string &conn,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const __int32 &mode,
	NetFileList &filelist,
	__int32 &ret,
	st_ExceptionError &ex)
{
	::InforGuard_::GetListExReq request;
	::InforGuard_::GetListExRes response;

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		请求数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** seqIpPort
	__DATACOPY_HOSTCHAIN_REQUEST__

	//** remotefoldername
	request.set_remotefoldername(remotefoldername);

	//** mode
	request.set_mode(mode);

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	bool check = m_Carry->GetListEx(conn, request, &response);

	/* - - - - - - - - - - - - - - - - - - - - *///<<
	/*
	***		响应数据填充区
	*/
	/* * * * * * * * * * * * * * * * * * * * * */

	//** filelist
	::google::protobuf::RepeatedPtrField<InforGuard_::NetFileListNode> nodes = response.filelist();
	for (auto node : nodes)
	{
		st_NetFileListNode node_;
		node_.name = node.name();
		node_.size = node.size();
		node_.time = node.time();
		node_.isfolder = node.isfolder();
		filelist.push_back(node_);
	}

	//** ret
	ret = response.ret();

	//** 异常信息
	__DATAEXCEPTION_TRANS__

	//>>/* - - - - - - - - - - - - - - - - - - - - */

	return check;
}