#include "ObjManageTemplate.h"
#include "Conv.h"

int main(int agrc, char *argv[])
{
	st_ConstructPara convPara;
	convPara.app = "ConvertTest";
	convPara.mdl = "Conversion";
	convPara.cls = "CConv";
	
	TObjManage<CConv> conv_GBKtoUTF8((void*)&convPara);
	
	printf("LANG=%s\n", getenv("LANG"));
	
	string gbk_;
	for (int i = 0; i < 512; i++)
	{
		gbk_ += "Ив";
	}
	string gbk;
	for (int i = 0; i < 1024; i++)
	{
		gbk += gbk_;
	}	
	
	//printf("gbk:%s,len:%d\n", gbk.c_str(), strlen(gbk.c_str()));
	printf("gbk.size():%d\n", gbk.size());
	string utf8;
	
	struct timeval start,end;
	gettimeofday(&start, nullptr);
	
	CConv *p = nullptr;
	if (!conv_GBKtoUTF8.Occupy(p))
	{
		printf("WTF!\n");
	}
	if (p)
	{
		p->GBKtoUTF8(gbk, utf8);
		//printf("utf8:%s\n", utf8.c_str());
	}
	else
	{
		printf("-1\n");
	}
	
	gettimeofday(&end, nullptr);
	printf("total cost %ld,%ld\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
	
	while (!getchar())
	{
		//...
	}

	return 0;
}
