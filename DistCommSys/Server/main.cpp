//** Application

#include "BaseDef.h"

#include "GRPCServer.h"

int main(int argc, char *argv[])
{
	CGRPCServer server("192.168.81.180", 10005);
	server.Init();
	server.Run();

	while (!getchar())
	{
		//...
	}

	return SUCCESS;
}
