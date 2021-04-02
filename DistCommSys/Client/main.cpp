//** Application

#include "PubUtil/BaseDef.h"

#include "GRPCClient.h"
#include "ThreadManager.h"

#define MAX_CONN 10

int main(int argc, char *argv[])
{
/*	shared_ptr<::grpc::ChannelInterface> p[MAX_CONN];
	unique_ptr<InforGuard_::FileTran::Stub> s[MAX_CONN];
	
	high_resolution_clock::time_point beginTime = high_resolution_clock::now();

	for (int i = 0; i < MAX_CONN; i++)
	{
		p[i] = ::grpc::CreateChannel("localhost:10005", ::grpc::InsecureChannelCredentials());
		if (p[i] != nullptr)
		{
			s[i] = InforGuard_::FileTran::NewStub(p[i]);
			if (s[i] != nullptr)
			{
				//printf("create interface[%d]\n", i);
				//::grpc::ClientContext context;
				//::InforGuard_::CheckReq request;
				//::InforGuard_::CheckRes response;
				//s[i]->Check(&context, request, &response);
			}
			else
			{
				printf("failed to create interface[%d]\n", i);
			}
		}
		else
		{
			printf("failed to create channel[%d]\n", i);
		}
	}
	
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	nanoseconds timeInterval = duration_cast<nanoseconds>(endTime - beginTime);
	printf("%lld\n", timeInterval.count());

	::grpc::ClientContext context;
	::InforGuard_::CheckReq request;
	::InforGuard_::CheckRes response;
	printf("%d\n", s[0]->Check(&context, request, &response).error_code());
*/	

	CGRPCClient client;
	if (client.Init())
	{
		printf("Client Init Successed\n");
	}
	else
	{
		printf("Client Init Failed\n");
	}

	CThreadManager manager(&client);
	manager.Init();
	manager.Start();


	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}
