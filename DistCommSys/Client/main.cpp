//** Application

#include "PubUtil/BaseDef.h"

#include "GRPCClient.h"

#include <grpcpp/grpcpp.h>
#include "FileTran.grpc.pb.h"

int main(int argc, char *argv[])
{
	LARGE_INTEGER fq;
	QueryPerformanceFrequency(&fq);

	LARGE_INTEGER pc1,pc2,pc3,pc4;
	QueryPerformanceCounter(&pc1);
	shared_ptr<::grpc::ChannelInterface> p1 = ::grpc::CreateChannel("localhost:10005", ::grpc::InsecureChannelCredentials());
	QueryPerformanceCounter(&pc2);
	printf("[1]%.2f\n", (double)((pc2.QuadPart - pc1.QuadPart)*1000/fq.QuadPart));
	printf("%d\n", sizeof(*(p1.get())));

	shared_ptr<::grpc::ChannelInterface> p2 = ::grpc::CreateChannel("localhost:10005", ::grpc::InsecureChannelCredentials());
	printf("p1:%p,p2:%p\n", p1, p2);

	unique_ptr<InforGuard_::FileTran::Stub> I1 = InforGuard_::FileTran::NewStub(p1);
	unique_ptr<InforGuard_::FileTran::Stub> I2 = InforGuard_::FileTran::NewStub(p2);
	printf("I1:%p,I2:%p\n", I1, I2);
	printf("%d\n", sizeof(*(I1.get())));

	QueryPerformanceCounter(&pc3);
	::grpc::ClientContext context1;
	::InforGuard_::CheckReq request1;
	::InforGuard_::CheckRes response1;
	I1->Check(&context1, request1, &response1);
	QueryPerformanceCounter(&pc4);
	printf("[2]%.2f\n", (double)((pc4.QuadPart - pc3.QuadPart) * 1000 / fq.QuadPart));

	::grpc::ClientContext context2;
	::InforGuard_::CheckReq request2;
	::InforGuard_::CheckRes response2;
	I2->Check(&context2, request2, &response2);

/*	CGRPCClient client;
	if (client.Init())
	{
		printf("Client Init Successed\n");
	}
	else
	{
		printf("Client Init Failed\n");
	}

	//for (int i = 0; i < 10; i++)
	while(true)
	{
		try
		{
			st_NetCallData call;
			string buff;
			long len = 0;
			bool ret = client.GetFileTran().GetFileBlock("localhost", "10005", call, "Linux123123", 100, buff, len);
			if (ret)
			{
				printf("GetFileBlock Successed\n");
				cout << buff << "///" << len << endl;
			}
			else
			{
				printf("GetFileBlock Failed\n");
			}
		}
		catch (st_ExceptionError &ex)
		{
			ex.Display();
		}
		SLEEP(1);
	}
*/

	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}