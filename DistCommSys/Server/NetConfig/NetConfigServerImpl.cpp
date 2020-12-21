#include "Server/NetConfig/NetConfigServerImpl.h"

#include "Base/App.h"
//#include "Base/NetTran.h"
#include "Common/DateTime.h"
#include "Common/ExceptionError.h"
////#include "Exception.h"
#include "GDLog/GDLog.h"
#include "GDLog/GDTrace.h"

string CNetConfigServerImpl::sAuthentication;

CNetConfigServerImpl::CNetConfigServerImpl()
{
	char tmp[128] = { 0 };
	string sLocalAuthFile = ::GetInforGuardPath();
	//	char sAuthentication[32] = {0};
	sLocalAuthFile.append(S_PATHLASH);
	sLocalAuthFile.append("cfg");
	sLocalAuthFile.append(S_PATHLASH);
	sLocalAuthFile.append("sAuthentication");
	FILE *fp = fopen(sLocalAuthFile.c_str(), "r");
	if (fp == NULL)
	{
		CGDLog::WriteErrLog("sAuthentication is not exist!");
	}
	else
	{
		fscanf(fp, "%s", tmp);
		fclose(fp);
		sAuthentication = tmp;
	}
}


CNetConfigServerImpl::~CNetConfigServerImpl()
{
	//...
}

int
CNetConfigServerImpl::
Load(const HostChain &seqIpPort,
	const string &cfgFileName,
	string &cfgFileContent,
	st_ExceptionError &ex)
{
	printf("Load\n");

	CGDTrace trace(LOG_L6, "NetConfig_impl:Load()");
	long nRet = 0;
	try
	{
		string configFileContent;
		nRet = CAppConfig::Instance().GetConfigFileContent(cfgFileName, configFileContent);
		cfgFileContent = configFileContent;
		//return nRet;
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "CAppConfig:GetConfigFileContent()";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("CAppConfig:GetConfigFileContent()");
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = -1;
	}

	return nRet;
}

int
CNetConfigServerImpl::
Save(const HostChain &seqIpPort,
	const string &cfgFileName,
	const string &cfgFileContent,
	st_ExceptionError &ex)
{
	printf("Save\n");

	CAppConfig::Instance().isSaveCfgXml = true;
	CGDTrace trace(LOG_L6, "NetConfig_impl:Save(%s,%s)", cfgFileName.c_str(), cfgFileContent.c_str());
	char temp[64] = { 0 };
	sprintf(temp, "[%s]", seqIpPort[1].sIp.c_str());
	string sInfo = temp;
	sInfo = sInfo.substr(sInfo.find_first_of("[") + 1, sInfo.find_last_of("]") - 1);
	if (strcmp(sInfo.c_str(), sAuthentication.c_str()) != 0)
	{
		CGDLog::WriteErrLog("A second MC is not allowed local is [%s],MC is [%s]", sAuthentication.c_str(), sInfo.c_str());
		/*		CExceptionError ex;
		ex.m_nErrCode = 113;
		ex.AddErrText( "A  NetConfig_impl:Save():" );
		InforGuard::ExceptionError e;
		CNetTran::ConvertException( ex, e );
		e._raise();*/
		return trace.SetRetValue(3); //这种类型的返回是3
	}
	long nRet = 0;

	try
	{
		if (strcmp("customrules.xml", cfgFileName.c_str()))
		{
			nRet = CAppConfig::Instance().Save(cfgFileName, cfgFileContent);
		}
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "CAppConfig:Save()";
		ex.vErrText.push_back(tmpErrMsg);

		nRet = -1;

		//ex.AddErrText("CAppConfig:Save()");
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
	}

	// CDateTime::Sleep(500); //以后要修改
	// CAppConfig::Instance().isSaveCfgXml = false;
	// 判断是否加载完？
	// 由于文件量大时，初始化慢，这里直接返回，不等待加载完成 modified by zhao_kwen on 20200929
	// if (strcmp("ma.xml", cfgFileName) == 0 || strcmp("sa.xml", cfgFileName) == 0)
	// {
	//     while (CAppConfig::Instance().isSaveCfgXml)
	//     {
	//         CDateTime::Sleep(20);
	//     }
	// }

	return trace.SetRetValue(nRet);
}
