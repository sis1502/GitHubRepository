#include "ThreadManager.h"

#include "PubUtil\ThreadPool\ThreadWorking.h"
#include "ClientJob.h"

using namespace Sis_;

CThreadManager::
CThreadManager(CGRPCClient *p)
{
	m_Client = p;
}

CThreadManager::
~CThreadManager()
{
	//...
}

void 
CThreadManager::
Run()
{
	for (int i = 0; i < 10; i++)
	{
		m_tWorking[i]->Notify();
	}

	this->Wait();
}

bool 
CThreadManager::
Init()
{
	try
	{
		m_jWorking = new CClientJob(m_Client);

		for (int i = 0; i < 10; i++)
		{
			m_tWorking[i] = new CThreadWorking(nullptr, m_jWorking, nullptr, nullptr, "ThreadWorking", i, 0);
			m_tWorking[i]->Start();
		}
	}
	catch (...)
	{
		cout << "123123" << endl;
	}

	return true;
}