#include "Server/MsgTran/MsgTranServerImpl.h"

#include "DCSManager.h"

CMsgTranServerImpl::CMsgTranServerImpl()
{
	//...
}


CMsgTranServerImpl::~CMsgTranServerImpl()
{
	//...
}

int
CMsgTranServerImpl::
GetMessage(const DistCommSysData_::HostChain &seqIpPort, st_MsgBlock &mb, st_ExceptionError &ex)
{
	printf("GetMessage\n");

	return 0;
}

int
CMsgTranServerImpl::
PutMessage(const DistCommSysData_::HostChain &seqIpPort, const st_MsgBlock &mb, st_ExceptionError &ex)
{
	printf("PutMessage\n");

	return 0;
}