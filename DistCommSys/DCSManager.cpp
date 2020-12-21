#include "DCSManager.h"

CDCSManager::
CDCSManager()
{
	m_Client = nullptr;
}

CDCSManager::
~CDCSManager()
{
	map<string, CGRPCServer*>::iterator it = m_Servers.begin();
	while (it != m_Servers.end())
	{
		if (it->second)
		{
			delete it->second;
		}
		m_Servers.erase(it++);
	}

	if (m_Client)
	{
		delete m_Client;
		m_Client = nullptr;
	}
}

bool 
CDCSManager::
InitClint()
{
	m_Client = new CGRPCClient();
	if (m_Client)
	{
		return m_Client->Init();
	}
	else
	{
		return false;
	}
}

bool 
CDCSManager::
InitServer(const string &ip, const unsigned int &port)
{
	string target = ip + to_string(port);
	map<string, CGRPCServer*>::iterator it = m_Servers.find(target);

	if (it == m_Servers.end())
	{
		CGRPCServer *p = new CGRPCServer(ip, port);
		if (p)
		{
			m_Servers[target] = p;
		}
		else
		{
			cout << "����GRPC����˼�������ʧ��" << endl;
			return false;
		}
		if (m_Servers[target]->Init())
		{
			//m_Servers[target]->Run();
			return true;
		}
		else
		{
			cout << "��ʼ��GRPC����˼���ʧ��" << endl;
			return false;
		}
	}
	else
	{
		cout << "GRPC����˼����ѱ�ռ��" << endl;
		return false;
	}
}

void 
CDCSManager::
RunServers()
{
	map<string, CGRPCServer*>::iterator it = m_Servers.begin();
	while (it != m_Servers.end())
	{
		it->second->Run();
		++it;
	}
}

CGRPCClient & 
CDCSManager::
GetClient()
{
	return *m_Client;
}