//** Application

#include "PubUtil/BaseDef.h"
#include "PubUtil/ExternFunc.h"

#include "GRPCServer.h"

int main(int argc, char *argv[])
{
	cout << "CheckIP:" << Sis_::CheckIP("localhost") << endl;

	CGRPCServer server("localhost", 10005);
	server.Init();
	server.Run();

	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}
