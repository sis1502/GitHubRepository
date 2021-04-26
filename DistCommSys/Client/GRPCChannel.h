#pragma once

#include "PubUtil/BaseDef.h"

#include <grpcpp/grpcpp.h>

class CGRPCChannel
{
public:
	CGRPCChannel(const string &certServer,
		const string &certClient,
		const string &keyClient,
		const unsigned int &count = 5,
		const time_t &interval = 10,
		const time_t &timeout = 30);
	~CGRPCChannel();

public:
	bool GetChannel(const string &conn, shared_ptr<::grpc::ChannelInterface> &channel);

private:
	map<string, shared_ptr<::grpc::ChannelInterface>> m_Channel;
	mutex m_Mutex;

private:
	unsigned int m_RetryCount;
	time_t m_RetryInterval;
	time_t m_Timeout;
	string m_ServerCert;
	string m_ClientCert;
	string m_ClientKey;
};

