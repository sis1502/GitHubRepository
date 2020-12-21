#pragma once

#include "Client/GRPCClient.h"
#include "Server/GRPCServer.h"

class CDCSManager final
{
public:
	CDCSManager();
	~CDCSManager();

public:
	bool InitClint();
	bool InitServer(const string &ip, const unsigned int &port);
	void RunServers();

public:
	CGRPCClient & GetClient();

private:
	CGRPCClient *m_Client;
	map<string, CGRPCServer*> m_Servers;
};