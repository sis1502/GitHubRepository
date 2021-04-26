#include "Client/GRPCChannel.h"

CGRPCChannel::
CGRPCChannel(const string &certServer,
	const string &certClient,
	const string &keyClient,
	const unsigned int &count,
	const time_t &interval,
	const time_t &timeout)
{
	m_ServerCert = certServer;
	m_ClientCert = certClient;
	m_ClientKey = keyClient;
	m_RetryCount = count;
	m_RetryInterval = interval;
	m_Timeout = timeout;
}


CGRPCChannel::
~CGRPCChannel()
{
	//...
}

bool 
CGRPCChannel::
GetChannel(const string &conn, shared_ptr<::grpc::ChannelInterface> &channel)
{
	//** 证书参数
	grpc::SslCredentialsOptions ssl_opts;
	//** 服务端根证书
	ssl_opts.pem_root_certs = m_ServerCert;
	//** 客户端私钥
	ssl_opts.pem_private_key = m_ClientKey;
	//** 客户端根证书
	ssl_opts.pem_cert_chain = m_ClientCert;

	//lock_guard<mutex> lock(m_Mutex);
	m_Mutex.lock();

	high_resolution_clock::time_point beginTime = high_resolution_clock::now();

	if (m_Channel.find(conn) == m_Channel.end())
	{
		//m_Channel[conn] = ::grpc::CreateChannel(conn, ::grpc::InsecureChannelCredentials());
		m_Channel[conn] = ::grpc::CreateChannel(conn, ::grpc::SslCredentials(ssl_opts));
	}

	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	milliseconds timeInterval = duration_cast<milliseconds>(endTime - beginTime);
	cout << "CreateChannel:" << timeInterval.count() <<endl;

	m_Mutex.unlock();

/*	bool connected = false;
	unsigned int count = 0;
	while (!(connected = m_Channel[conn]->WaitForConnected<gpr_timespec>(tm_out)) && (m_RetryCount > count))
	{
#	ifdef _CONSOLE
		cout << "Retry to connect to [" << conn << "].Retrycount remaining [" << m_RetryCount - count << "]" << endl;
#	endif
		count++;
		SLEEP(m_RetryInterval);
	}
	if (connected)*/

	beginTime = high_resolution_clock::now();

	gpr_timespec tm_out{ m_Timeout, 0, GPR_TIMESPAN };

	if (m_Channel[conn]->WaitForConnected<gpr_timespec>(tm_out))
	{
		channel = m_Channel[conn];

		endTime = high_resolution_clock::now();
		timeInterval = duration_cast<milliseconds>(endTime - beginTime);
		//cout << "Wait Success:" << timeInterval.count() << endl;

		return true;
	}
	else
	{
		endTime = high_resolution_clock::now();
		timeInterval = duration_cast<milliseconds>(endTime - beginTime);
		//cout << "Wait Fail:" << timeInterval.count() << endl;

		//cout << GetCurrentThreadId() << "结束。。。。" << endl;

		return false;
	}
}