//** Application

#include "PubUtil/ExternFunc.h"

#include "GRPCClient.h"
#include "ThreadManager.h"

#define MAX_CONN 10

int main(int argc, char *argv[])
{
	string path = Sis_::GetRunningDirectory();
	string certServer = Sis_::GetFileContent(path + "key\\" + string(servercert_path));
	string certClient = Sis_::GetFileContent(path + "key\\" + string(clientcert_path));
	string keyClient = Sis_::GetFileContent(path + "key\\" + string(clientkey_path));
	CGRPCClient client;
	if (client.Init(certServer, certClient, keyClient))
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
