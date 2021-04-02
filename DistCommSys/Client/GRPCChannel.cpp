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
	cout << GetCurrentThreadId() << "µÈ´ý¡£¡£¡£¡£" << endl;

	//lock_guard<mutex> lock(m_Mutex);
	m_Mutex.lock();

	cout << "Timeout:" << m_Timeout << endl;

	high_resolution_clock::time_point beginTime = high_resolution_clock::now();

	if (m_Channel.find(conn) == m_Channel.end())
	{
		m_Channel[conn] = ::grpc::CreateChannel(conn, ::grpc::InsecureChannelCredentials());
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
		cout << "Wait Success:" << timeInterval.count() << endl;

		return true;
	}
	else
	{
		endTime = high_resolution_clock::now();
		timeInterval = duration_cast<milliseconds>(endTime - beginTime);
		cout << "Wait Fail:" << timeInterval.count() << endl;

		cout << GetCurrentThreadId() << "½áÊø¡£¡£¡£¡£" << endl;

		return false;
	}
}