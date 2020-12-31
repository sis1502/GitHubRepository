//** Application

#include "PubUtil/BaseDef.h"

#include "GRPCServer.h"

int main(int argc, char *argv[])
{
	CGRPCServer server("localhost", 10005);
	server.Init();
	server.Run();

	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}
