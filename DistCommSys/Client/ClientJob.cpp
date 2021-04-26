#include "ClientJob.h"

#include "GRPCClient.h"

using namespace Sis_;

CClientJob::
CClientJob(CGRPCClient *p)
{
	m_Client = p;
}

CClientJob::
~CClientJob()
{
	//...
}

bool 
CClientJob::
Run(CThreadJobQueue *p_O, CThreadJobQueue *p_R)
{
	try
	{
		st_NetCallData call;
		string buff;
		long len = 0;
		int ret = m_Client->GetFileTran().GetFileBlock("InforGuard", "10005", call, "Linux123123", 100, buff, len);
		if (ret == 0)
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

	SLEEP(5);

	return true;
}