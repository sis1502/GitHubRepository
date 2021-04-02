#include "Convertor.h"

int main(int agrc, char *argv[])
{
	st_ConstructPara convPara;
	convPara.app = "ConvertTest";
	convPara.mdl = "Conversion";
	convPara.cls = "CConv";
	
	CConvertor conv((void*)&convPara);
	
	string gbk_;
	for (int i = 0; i < 10; i++)
	{
		gbk_ += "��";
	}
	string gbk;
	for (int i = 0; i < 1; i++)
	{
		gbk += gbk_;
	}	
	
	//printf("gbk:%s,len:%d\n", gbk.c_str(), strlen(gbk.c_str()));
	printf("gbk.size():%d\n", gbk.size());
	string utf8;

	conv.GBKtoUTF8(gbk, utf8);

	printf("utf8:%s\n", utf8.c_str());

	string gbk__;
	conv.UTF8toGBK(utf8, gbk__);
	printf("gbk__:%s\n", gbk__.c_str());
	
	while (!getchar())
	{
		//...
	}

	return 0;
}
