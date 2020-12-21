#include "Client/NetConfig/NetConfigClientCarry.h"

#include "Client/GRPCChannel.h"
#include "PubUtil/DataExchange.h"

CNetConfigClientCarry::
CNetConfigClientCarry(CGRPCChannel *p)
{
	m_Channel = p;
}

CNetConfigClientCarry::
~CNetConfigClientCarry()
{
	//...
}

bool 
CNetConfigClientCarry::
Load(const string &conn, const ::InforGuard_::LoadReq& request, ::InforGuard_::LoadRes* response)
{
	if (!m_Stub)
	{
		shared_ptr<::grpc::ChannelInterface> channel;
		if (!m_Channel->GetChannel(conn, channel))
		{
#		ifdef _CONSOLE
			cout << conn << " Connect FAILED" << endl;
#		endif
			//�����Ӧ�����е��쳣�����ӷ���ʧ��
			__BADCHANNELEXCEPTION_STUFF__

			return false;
		}
		m_Stub = InforGuard_::NetConfig::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Load(&context, request, response);
	if (status.ok())
	{
		return true;
	}
	else
	{
		//�����Ӧ�����е��쳣������Զ�̽ӿ�ʧ��
		__BADSTUBEXCEPTION_STUFF__

		return false;
	}
}

bool 
CNetConfigClientCarry::
Save(const string &conn, const ::InforGuard_::SaveReq& request, ::InforGuard_::SaveRes* response)
{
	if (!m_Stub)
	{
		shared_ptr<::grpc::ChannelInterface> channel;
		if (!m_Channel->GetChannel(conn, channel))
		{
#		ifdef _CONSOLE
			cout << conn << " Connect FAILED" << endl;
#		endif
			//�����Ӧ�����е��쳣�����ӷ���ʧ��
			__BADCHANNELEXCEPTION_STUFF__

			return false;
		}
		m_Stub = InforGuard_::NetConfig::NewStub(channel);
	}

	::grpc::ClientContext context;
	::grpc::Status status = m_Stub->Save(&context, request, response);
	if (status.ok())
	{
		return true;
	}
	else
	{
		//�����Ӧ�����е��쳣������Զ�̽ӿ�ʧ��
		__BADSTUBEXCEPTION_STUFF__

		return false;
	}
}