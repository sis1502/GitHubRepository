#pragma once

#include "PubUtil/DataExchange.h"

using namespace DistCommSysData_;

class CMsgTranServerImpl final
{
public:
	CMsgTranServerImpl();
	~CMsgTranServerImpl();

public:
	int GetMessage(const DistCommSysData_::HostChain &seqIpPort, st_MsgBlock &mb, st_ExceptionError &ex);
	int PutMessage(const DistCommSysData_::HostChain &seqIpPort, const st_MsgBlock &mb, st_ExceptionError &ex);

private:
	//...
};

