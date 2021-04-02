#pragma once

#include "PubUtil\ThreadPool\ThreadRunJob.h"

namespace Sis_
{
	class CThreadJobQueue;
}

class CGRPCClient;

class CClientJob final : public Sis_::CThreadRunJob
{
public:
	CClientJob(CGRPCClient *p);
	~CClientJob();

public:
	bool Run(Sis_::CThreadJobQueue *p_O, Sis_::CThreadJobQueue *p_R);

private:
	CGRPCClient *m_Client;
};
