#include "Client/GRPCChannel.h"

CGRPCChannel::
CGRPCChannel(const unsigned int &count, const time_t &interval, const time_t &timeout)
{
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
	lock_guard<mutex> lock(m_Mutex);

	gpr_timespec tm_out{ m_Timeout, 0, GPR_TIMESPAN };
	if (m_Channel.find(conn) == m_Channel.end())
	{
		m_Channel[conn] = ::grpc::CreateChannel(conn, ::grpc::InsecureChannelCredentials());
	}
	bool connected = false;
	unsigned int count = 0;
	while (!(connected = m_Channel[conn]->WaitForConnected<gpr_timespec>(tm_out)) && (m_RetryCount > count))
	{
#	ifdef _CONSOLE
		cout << "Retry to connect to [" << conn << "].Retrycount remaining [" << m_RetryCount - count << "]" << endl;
#	endif
		count++;
		SLEEP(m_RetryInterval);
	}
	if (connected)
	{
		channel = m_Channel[conn];
		return true;
	}
	else
	{
		return false;
	}
}