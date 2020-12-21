#pragma once

#include "PubUtil/DataExchange.h"
#include "Common/ExtQueue.h"
#include "MsgTran/MsgTranDef.h"

using namespace DistCommSysData_;

class CMsgTranServerImpl final
{
public:
	CMsgTranServerImpl();
	~CMsgTranServerImpl();

public:
	int GetMessage(const DistCommSysData_::HostChain &seqIpPort, st_MsgBlock &mb, st_ExceptionError &ex);
	int PutMessage(const DistCommSysData_::HostChain &seqIpPort, const st_MsgBlock &mb, st_ExceptionError &ex);

public:
	static CExtQueue<MsgBlockStruct2> m_recvMsgQue;
	static string sAuthentication;

private:
	//...
};

