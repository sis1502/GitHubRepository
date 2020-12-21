//** Application

#include "BaseDef.h"

#include "GRPCClient.h"

int main(int argc, char *argv[])
{
	CGRPCClient client;
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
			bool ret = client.GetFileTran().GetFileBlock("192.168.81.12", "10005", call, "Linux123123", 100, buff, len);
			if (ret)
			{
				printf("Check Successed\n");
				cout << buff << "///" << len << endl;
			}
			else
			{
				printf("Check Failed\n");
			}
		}
		catch (st_ExceptionError &ex)
		{
			ex.Display();
		}
		SLEEP(1);
	}

	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}
