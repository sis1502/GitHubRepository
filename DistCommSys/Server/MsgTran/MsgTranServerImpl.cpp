#include "Server/MsgTran/MsgTranServerImpl.h"

#include "DCSManager.h"

#include "Base/App.h"
#include "Base/RunInfor.h"
#include "Base/TaskControl.h"
#include "Base/ThreadProcFileTran.h"
#include "Base/ThreadProcMsg.h"
#include "Base/Tool.h"
#include "Base/Toolbox.h"
#include "Common/ExceptionError.h"
#include "FileOpt/FileOpt.h"
#include "GDLog/GDLog.h"
#include "GDLog/GDTrace.h"
#include "Groundwork/NumberFormatter.h"
#include "SystemInfo/SystemInfo.h"

CExtQueue<MsgBlockStruct2> CMsgTranServerImpl::m_recvMsgQue;
string CMsgTranServerImpl::sAuthentication;

#ifdef WIN32

void MakeStartCmd(const std::string &sServiceName, const std::string &sDirPath, const std::string &sProgramName, std::string *pStartCmd)
{
	string sProgramPath = sDirPath + "\\" + sProgramName;
	// 默认没有安装服务，直接启动程序
	*pStartCmd = sProgramPath;
	SC_HANDLE scManager = NULL;
	SC_HANDLE scService = NULL;
	// 打开服务管理对象
	scManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	// 打开服务管理对象失败
	if (!scManager)
		return;
	// 查询服务状态
	scService = OpenService(scManager, TEXT(sServiceName.c_str()), SERVICE_QUERY_STATUS);
	// 查询失败
	if (!scService)
	{
		// 关闭服务管理对象
		CloseServiceHandle(scManager);
		return;
	}
	SERVICE_STATUS_PROCESS svStatus;
	DWORD dwBytesNeeded = 0;
	// 查询不到服务状态
	if (!QueryServiceStatusEx(scService, SC_STATUS_PROCESS_INFO, (LPBYTE)&svStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		CloseServiceHandle(scService);
		CloseServiceHandle(scManager);
		return;
	}
	// 判断服务状态
	switch (svStatus.dwCurrentState)
	{
	case SERVICE_RUNNING: // 已启动，正在运行
	case SERVICE_START_PENDING: // 正在启动
	case SERVICE_CONTINUE_PENDING: // 正在恢复
								   // 当且仅当sa或ma服务正在运行时，才能认为它是从服务启动的
		*pStartCmd = "net start " + sServiceName;
		break;
	default:
		break;
	}
	CloseServiceHandle(scService);
	CloseServiceHandle(scManager);
	return;
}


DWORD WINAPI RestartAppRoutine(LPVOID param)
{
	// 休眠1000毫秒，确保MC收到返回值
	CDateTime::Sleep(1000);
	// 预备重启
	string sAppRootPath = GetInforGuardPath();
	const char *lpFile = "c:\\windows\\system32\\cmd.exe";
	std::string sLpParametes = "/c (echo 1)";
	// 根据端口号结束当前程序
	std::string sLocalPort = CAppConfig::Instance().GetLocalPort();
	std::string sBinPath = sAppRootPath + S_PATHLASH + "bin";
	char szStopCmd[1024];
	std::string sStartCmd;
	if (strcmp(GetAppName(), "sa") == 0)
	{
		// 根据端口找到名为InforGuardSa.exe的进程并杀死。如果查找失败直接杀死所有InforGuardSa.exe
		sprintf(szStopCmd, "(for /f \"tokens=2,5 delims= \" %%a in ('netstat -ano ^| findstr \":%s \"') do tasklist | findstr %%b | findstr InforGuardSa.exe && taskkill /f /pid %%b) || (taskkill /f /im InforGuardSa.exe)", sLocalPort.c_str());
		sLpParametes = sLpParametes + " && (" + szStopCmd + " || echo 1)";
		MakeStartCmd("InforGuardSa", sBinPath, "InforGuardSa.exe", &sStartCmd);
	}
	else if (strcmp(GetAppName(), "ma") == 0)
	{
		// 根据端口找到名为InforGuardMa.exe的进程并杀死。如果查找失败直接杀死所有InforGuardMa.exe
		sprintf(szStopCmd, "(for /f \"tokens=2,5 delims= \" %%a in ('netstat -ano ^| findstr \":%s \"') do tasklist | findstr %%b | findstr InforGuardMa.exe && taskkill /f /pid %%b) || (taskkill /f /im InforGuardMa.exe)", sLocalPort.c_str());
		sLpParametes = sLpParametes + " && (" + szStopCmd + " || echo 1)";
		MakeStartCmd("InforGuardMa", sBinPath, "InforGuardMa.exe", &sStartCmd);
	}
	else
	{
		return -1;
	}
	sLpParametes += " && (timeout /nobreak /t 1 || echo 1)";
	sLpParametes += " && (" + sStartCmd + " || echo 1)";
	{
		CGDTrace trace(LOG_L6, "MsgTran_impl:RestartAppRoutine(...) cmd=\"%s\"", sLpParametes.c_str());
	}
	// 隐藏cmd窗口执行命令
#define DEBUG_RESTART_CMD 0 // 是否调试重启脚本
#if DEBUG_RESTART_CMD
	sLpParametes += " && pause";
	ShellExecute(NULL, "open", lpFile, sLpParametes.c_str(), NULL, SW_SHOW);
#else
	ShellExecute(NULL, "open", lpFile, sLpParametes.c_str(), NULL, SW_HIDE);
#endif
	return 0;
}

#else
void *RestartAppRoutine(void *pParam)
{
	// 休眠1000毫秒确保mc收到返回值
	CDateTime::Sleep(1000);
	std::string sAppRootPath = GetInforGuardPath();
	std::string sCmd;
	sCmd += "INFORGUARD_HOME=`cd " + sAppRootPath + " && pwd` \n";
	if (strcmp(GetAppName(), "sa") == 0)
	{
		sCmd += "killall -9 GuardSAKeeper \n";
		sCmd += "killall -9 InforGuardSa \n";
		sCmd += "$INFORGUARD_HOME/bin/GuardSAKeeper \n";
	}
	else if (strcmp(GetAppName(), "ma") == 0)
	{
		sCmd += "killall -9 GuardMAKeeper \n";
		sCmd += "killall -9 InforGuardMa \n";
		sCmd += "$INFORGUARD_HOME/bin/GuardMAKeeper \n";
	}
	{
		CGDTrace trace(LOG_L6, "MsgTran_impl:RestartAppRoutine(...) cmd=\"%s\"", sCmd.c_str());
	}
	system(sCmd.c_str());
}
#endif

void GetThreadNameVec(vector<string> &threadNameVec)
{
	threadNameVec.clear();
	// 主进程
	threadNameVec.push_back("");
	if (strcmp(GetAppName(), "sa") == 0)
	{
		string sAppRootPath = GetInforGuardPath();
		// 辅助进程
#ifdef WIN32
		intptr_t hFinder;
		_finddata_t findData;
		string sFindPath = sAppRootPath + "\\*";
		hFinder = _findfirst(sFindPath.c_str(), &findData);
		if (hFinder == -1)
			return;
		do
		{
			if (findData.attrib & _A_SUBDIR)
			{
				int nThreadId = 0;
				if (sscanf(findData.name, "sa_%d", &nThreadId) == 1)
				{
					threadNameVec.push_back(findData.name);
				}
			}
		} while (_findnext(hFinder, &findData) == 0);
		_findclose(hFinder);
#else
		DIR *dir = opendir(sAppRootPath.c_str());
		if (!dir)
			return;
		struct dirent *ent;
		while (ent = readdir(dir))
		{
			if (ent->d_type == DT_DIR)
			{
				int nThreadId = 0;
				if (sscanf(ent->d_name, "sa_%d", &nThreadId) == 1)
				{
					threadNameVec.push_back(ent->d_name);
				}
			}
		}
		closedir(dir);
#endif
	}
}

CMsgTranServerImpl::CMsgTranServerImpl()
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


CMsgTranServerImpl::~CMsgTranServerImpl()
{
	//...
}

int
CMsgTranServerImpl::
GetMessage(const DistCommSysData_::HostChain &seqIpPort, st_MsgBlock &mb, st_ExceptionError &ex)
{
	printf("GetMessage\n");

	CGDTrace trace(LOG_L9, "MsgTran_impl:GetMessage( InforGuard::HostChain& seqIpPort, InforGuard::MsgBlock_out mb )");

	// 读本地消息队列
	switch (mb.mid)
	{
	case MID_MC_FETCH_SERVICE_INFO:
	{
		//mb.pl.length(2);
		mb.pl.push_back(GetAppName());
		//mb.pl[0] = CORBA::string_dup(GetAppName());
		char temp[64] = { 0 };
		sprintf(temp, "[%s]", seqIpPort[1].sIp.c_str());
		string sInfo = temp;
		sInfo = sInfo.substr(sInfo.find_first_of("[") + 1, sInfo.find_last_of("]") - 1);

		if (strcmp(sInfo.c_str(), sAuthentication.c_str()) != 0)
		{
			CGDLog::WriteErrLog("A second MC is not allowed local is [%s] MC is [%s]", sAuthentication.c_str(), sInfo.c_str());
			return trace.SetRetValue(3); //这种类型的返回是3
		}
#if defined WIN32
		mb.pl.push_back("Win32");
		//mb.pl[1] = CORBA::string_dup("Win32");
#elif defined Linux
		mb.pl.push_back("Linux");
		//mb.pl[1] = CORBA::string_dup("Linux");
#else
		mb.pl.push_back("UNIX");
		//mb.pl[1] = CORBA::string_dup("UNIX");
#endif
		break;
	}
	case MID_MC_FETCH_WEBSITE_STATUS:
	{
		long taskType = 0;
		//疑点，by Sis on 2020-11-20
/*
		mb.pl.length(1);
		CApp::Instance().TaskControl().GetWebSiteTask(mb.pl[0].in(), taskType);
		mb.pl[0] = CORBA::string_dup(InforGuard::Groundwork::NumberFormatter::format(taskType).c_str());
*/
		break;
	}
	case MID_MA_DYNAMIC_INFO:
	{
		char dynamicInfo[256] = { 0 };
		GetDynamicInfomation(dynamicInfo);
		//mb.pl.length(1);
		mb.pl.push_back(dynamicInfo);
		//mb.pl[0] = CORBA::string_dup(dynamicInfo);

		GDPrint("\n\npl is [%s]\n", mb.pl[0].c_str());
		break;
	}
	case MID_MA_STATIC_INFO:
	{
		char staticInfo[40960] = { 0 };
		GetStaticInfomation(staticInfo, seqIpPort[0].sIp.c_str());
		//mb.pl.length(1);
		mb.pl.push_back(staticInfo);
		//mb.pl[0] = CORBA::string_dup(staticInfo);

		GDPrint("\n\npl is [%s]\n", mb.pl[0].c_str());
		break;
	}
	case MID_SA_TO_SA_RACE:
	{
		char temNum[12] = { 0 };
		sprintf(temNum, "%d", CAppConfig::randNum);
		//mb.pl.length(1);
		mb.pl.push_back(temNum);
		//mb.pl[0] = CORBA::string_dup(temNum);
		break;
	}
	// add by zhao_kwen on 2020-06-08
	case MID_MC_FETCH_LOGS_LIST:
	{
		string sAppRootPath = GetInforGuardPath();
		vector<string> logFileInfoVec;
		int nLogFileInfoVecSize = 0;
		vector<string> threadNameVec;
		GetThreadNameVec(threadNameVec);
		vector<string>::iterator threadNameVecIter;
		for (threadNameVecIter = threadNameVec.begin(); threadNameVecIter != threadNameVec.end(); ++threadNameVecIter)
		{
			string sThreadName = *threadNameVecIter; // 对于主进程此值为空，而对于sa的辅助进程此值则类似于sa_1、sa_2
			bool bIsMainThread = !sThreadName.length();
			string sLogDirPath; // log文件所在目录
			if (bIsMainThread) // 主进程
			{
				sLogDirPath = sAppRootPath + S_PATHLASH + "log" + S_PATHLASH;
			}
			else // 辅助进程
			{
				sLogDirPath = sAppRootPath + S_PATHLASH + sThreadName + S_PATHLASH + "log" + S_PATHLASH;
			}
#ifdef WIN32
			intptr_t hFinder;
			_finddata_t findData;
			string sFindPath = sLogDirPath + "*.*";
			hFinder = _findfirst(sFindPath.c_str(), &findData);
			if (hFinder == -1)
			{
				// 没有日志文件
				continue;
			}
			do
			{
				if (findData.attrib & _A_ARCH)
				{
					string sLogFileName = findData.name;
#else
			DIR *dir = opendir(sLogDirPath.c_str());
			if (!dir)
				continue;
			struct dirent *ent;
			while (ent = readdir(dir))
			{
				if (ent->d_type == DT_REG)
				{
					string sLogFileName = ent->d_name;
#endif
					// 过滤文件后缀不为log的文件()
					string sSuffix = sLogFileName.substr(sLogFileName.find_last_of(".") + 1);
#ifdef WIN32
					if (stricmp(sSuffix.c_str(), "log") != 0)
#else
					if (strcasecmp(sSuffix.c_str(), "log") != 0)
#endif
					{
						continue;
					}
					nLogFileInfoVecSize++;
					// 获取文件大小及文件修改时间
					string sLogFilePath = sLogDirPath + sLogFileName;
#ifdef WIN32
					struct _stat64 buf;
					_stati64(sLogFilePath.c_str(), &buf);
#else
					struct stat buf;
					stat(sLogFilePath.c_str(), &buf);
#endif
					long long nLogFileSize = buf.st_size;
					char szLogFileSize[20];
					sprintf(szLogFileSize, "%lu", nLogFileSize);
					time_t mtime = buf.st_mtime;
					struct tm tm_mtime;
#ifdef WIN32
					localtime_s(&tm_mtime, &mtime);
#else
					localtime_r(&mtime, &tm_mtime);
#endif
					char szLogFileMtime[32];
					sprintf(szLogFileMtime, "%d-%02d-%02d %02d:%02d:%02d",
						tm_mtime.tm_year + 1900, tm_mtime.tm_mon + 1, tm_mtime.tm_mday, tm_mtime.tm_hour, tm_mtime.tm_min, tm_mtime.tm_sec);
					// sLogKey由进程名及文件名组成，MC根据此值下载日志文件
					string sLogKey;
					if (bIsMainThread) // 主进程
					{
						sLogKey = sLogFileName;
					}
					else // 辅助进程
					{
						sLogKey = sThreadName + "@" + sLogFileName;
					}
					// 组装日志文件信息
					string sLogInfo;
					sLogInfo.append(sLogKey);
					sLogInfo.append("|");
					sLogInfo.append(szLogFileSize);
					sLogInfo.append("|");
					sLogInfo.append(szLogFileMtime);
					logFileInfoVec.push_back(sLogInfo);
				}
#ifdef WIN32
			} while (_findnext(hFinder, &findData) == 0);
			_findclose(hFinder);
#else
				}
			closedir(dir);
#endif
			} // 遍历logDirVec结束
			  // 组装日志文件列表
		//mb.pl.length(nLogFileInfoVecSize);
		mb.pl = logFileInfoVec;
		//for (int i = 0; i < nLogFileInfoVecSize; i++)
		//{
		//	mb.pl[i] = CORBA::string_dup(logFileInfoVec[i].c_str());
		//}
		break;
		}
	case MID_MC_FETCH_LOG_FILE:
	{
		// 由于当时与mc没有文件传输的接口，这里日志以字符串方式传输。将来考虑使用流分片传输进行重构
		for (int i = 0; i < mb.pl.size(); i++)
		{
			string sAppRootPath = GetInforGuardPath();
			string sLogFilePath;
			string sLogKey = mb.pl[i];
			char szThreadName[128];
			char szLogFileName[256];
			if (sscanf(sLogKey.c_str(), "%[^@]@%s", szThreadName, szLogFileName) == 2)
			{
				// 辅助进程文件下载
				sLogFilePath = sAppRootPath + S_PATHLASH + string(szThreadName) + S_PATHLASH + "log" + S_PATHLASH + string(szLogFileName);
			}
			else
			{
				// 主进程文件下载
				sLogFilePath = sAppRootPath + S_PATHLASH + "log" + S_PATHLASH + sLogKey;
			}
			const int MAX_FILE_SIZE = 50 * 1024 * 1024; // 50MiB
			if (CFileOpt::GetFileSize(sLogFilePath.c_str()) > MAX_FILE_SIZE)
			{
				mb.pl[i] = "[错误] 文件大小超过50MiB，不支持下载！";
				continue;
			}
			FILE *pFile = fopen(sLogFilePath.c_str(), "rb");
			if (!pFile)
			{
				CGDLog::WriteErrLog("[MsgTran_impl:GetMessage] open file \"%s\" failed: %s\n", sLogFilePath.c_str(), strerror(errno));
				continue;
			}
			string sContent = "";
			const int MAX_BUF_SIZE = 1024;
			char szBuf[MAX_BUF_SIZE + 1];
			int nBufSize = -1;
			do
			{
				nBufSize = fread(szBuf, 1, MAX_BUF_SIZE, pFile);
				szBuf[nBufSize] = 0;
				sContent.append(szBuf);
			} while (nBufSize == MAX_BUF_SIZE);
			fclose(pFile);
			// GDPrintln("sContent=\n%s", sContent.c_str());
			mb.pl[i] = sContent;
		}
		break;
	}
	case MID_MC_REQUEST_RESTART:
	{
#ifdef WIN32
		DWORD tid = 0;
		HANDLE hAppStoper = CreateThread(NULL, 0, RestartAppRoutine, NULL, 0, &tid);
#else
		pthread_t pid = 0;
		pthread_create(&pid, NULL, RestartAppRoutine, NULL);
#endif
	}
	return 0;
	case MID_MC_GET_START_TIME:
	{
		char appStartTime[32];
		sprintf(appStartTime, "%ld", CApp::Instance().GetAppStartTime());
		//mb.pl.length(1);
		//mb.pl[0] = CORBA::string_dup(appStartTime);
		mb.pl.push_back(appStartTime);
	}
	break;
	default:
		break;
	}

	return 0;
}

int
CMsgTranServerImpl::
PutMessage(const DistCommSysData_::HostChain &seqIpPort, const st_MsgBlock &mb, st_ExceptionError &ex)
{
	printf("PutMessage\n");

	MsgBlockStruct mb_;
	//mb_.nMid = mb.mid;
	Int2enumMsgID(mb.mid, mb_.nMid);
	mb_.nLevel = mb.level;
	mb_.nSerial = mb.serial;
	mb_.sSrc = mb.src;
	mb_.sDst = mb.dst;
	mb_.pl = mb.pl;

	string sParam;
	sParam = sParam + "mb[" + CTool::MB2String(mb_) + "]seqIpPort[" + CTool::HostChain2String(seqIpPort) + "]";

	CGDTrace trace(LOG_L6, "MsgTran_impl:PutMessage(%s)", sParam.c_str());

	int nRet = 0;

	string sToIp;
	string sToPort;

	try
	{
		// 检测转发
		if (CTool::IsTransmit(seqIpPort, sToIp, sToPort))
		{
			//** gRPC替换CORBA并实现隔离封装 by Sis on 2020-11-20
			//MsgTran_var ref;
			//CNetTran::GetMsgTranObject(sToIp.c_str(), sToPort.c_str(), ref);
			//return ref->PutMessage(seqIpPort, mb);
			CApp::Instance().GetDCSManager().GetClient().GetMsgTran().PutMessage(sToIp, sToPort, seqIpPort, mb);
		}

		// 消息数据结构转换
		MsgBlockStruct2 mb2;
		//mb2.mb = mb;
		//mb2.hosts = seqIpPort;
		mb2.mb.mid = mb.mid;
		mb2.mb.level = mb.level;
		mb2.mb.serial = mb.serial;
		mb2.mb.src = mb.src;
		mb2.mb.dst = mb.dst;
		mb2.mb.pl = mb.pl;
		mb2.hosts = seqIpPort;
/*		int nCount = mb.pl.length();
		mb2.mb.pl.length(nCount);
		int i = 0;
		for (i = 0; i < nCount; i++)
		{
			mb2.mb.pl[i] = CORBA::string_dup(mb.pl[i]);
		}
		nCount = seqIpPort.length();
		mb2.hosts.length(nCount);
		for (i = 0; i < nCount; i++)
		{
			InforGuard::netIpPort host;
			host.sIp = CORBA::string_dup(seqIpPort[i].sIp.in());
			host.sPort = CORBA::string_dup(seqIpPort[i].sPort.in());
			mb2.hosts[i] = host;
		}*/

		if (mb.level)
		{
			//CApp::Instance().RunInfor().SendToMc( INF, "(*gpDealMsgCallback)(%d)", mb.mid );
			nRet = CApp::Instance().MessageHandler().HandleMessage(mb2);
		}
		else
		{
			// 消息队列处理(异步)
			// 线程互斥
			trace.GDTrace(LOG_DBG, "MsgTran_impl::PutMessage put msg to queue");
			m_recvMsgQue.Add(mb2);
		}
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:PutMessage(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("MsgTran_impl:PutMessage(%s)", sParam.c_str());
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		CGDLog::WriteErrLog("1150:MsgTran_impl:PutMessage\n%s", ex1.GetErrText().c_str());
	}
/*	catch (CORBA::Exception &ex)
	{
		ex._raise();
	}*/

	return trace.SetRetValue(nRet);
	return true;
}