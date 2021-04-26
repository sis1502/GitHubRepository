//** Application

#include "PubUtil/BaseDef.h"
#include "PubUtil/ExternFunc.h"

#include "GRPCServer.h"

int main(int argc, char *argv[])
{
	string path = Sis_::GetRunningDirectory();
	string certServer = Sis_::GetFileContent(path + "key\\" + string(servercert_path));
	string certClient = Sis_::GetFileContent(path + "key\\" + string(clientcert_path));
	string keyServer = Sis_::GetFileContent(path + "key\\" + string(serverkey_path));

	//cout << "certServer:" << certServer << endl;
	//cout << "certClient:" << certClient << endl;
	//cout << "keyServer:" << keyServer << endl;

	CGRPCServer server("192.168.1.101", 10005, certClient, certServer, keyServer);
	server.Init();
	server.Run();

	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}
