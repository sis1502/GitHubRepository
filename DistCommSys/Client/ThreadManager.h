#pragma once

#include "PubUtil\ThreadPool\Thread.h"

namespace Sis_
{
	class CThreadWorking;
	class CThreadRunJob;
}

class CGRPCClient;

class CThreadManager final : public Sis_::CThread
{
public:
	CThreadManager(CGRPCClient *p);
	~CThreadManager();

public:
	void Run();

public:
	bool Init();

private:
	map <int, Sis_::CThreadWorking*> m_tWorking;
	Sis_::CThreadRunJob *m_jWorking;

private:
	CGRPCClient *m_Client;
};
