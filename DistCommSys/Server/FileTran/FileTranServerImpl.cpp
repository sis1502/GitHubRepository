#include "FileTranServerImpl.h"

#include "Base/App.h"
#include "Base/AppConfig.h"
#include "Base/FileListEx.h"
#include "Base/FileOptEx.h"
#include "Base/MonitorDef.h"
#include "Base/RunInfor.h"
#include "Base/Tool.h"
#include "Base/Toolbox.h"
#include "Common/AppError.h"
#include "Common/Common.h"
#include "Common/ExceptionError.h"
#include "Common/GDFile.h"
#include "Common/GDString.h"
#include "CompressData/CompressData.h"
#include "FileOpt/FileOpt.h"
#include "FileTran/PullListSaver.h"
#include "GDLog/GDLog.h"
#include "GDLog/GDTrace.h"
#include "GDLog/ThreadData.h"

#ifdef WIN32
#define FMT_LL "I64"
#else
#define FMT_LL "ll"
#endif

CFileTranServerImpl::
CFileTranServerImpl()
{
	transblock = new char[262144];
}

CFileTranServerImpl::
~CFileTranServerImpl()
{
	delete[] transblock;
}

int
CFileTranServerImpl::
Check(st_ExceptionError &ex)
{
	printf("Check\n");

	return 0;
}

int
CFileTranServerImpl::
GetFileBlock(st_NetCallData &call,
	const string &filename,
	const __int64 off,
	__int32 &len,
	string &buff,
	st_ExceptionError &ex)
{
	printf("GetFileBlock\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("fileserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);
	char trans_flag = '0';
	trans_flag = filename[0];

	string sTmpFileName = filename;
	sTmpFileName = sTmpFileName.substr(1);

	CGDString::MakeSureLocalPath(sTmpFileName);
	//////////////////////////////
	//add by zhangtao at 2010-7-13 for 加解密
	char sTempPath[521] = { 0 };
	FILE *fp;
	if (CAppConfig::encryption == 1) //启用了备份端加解密
	{
		if (strcmp(GetAppName(), "sa") == 0)
		{
#ifdef WIN32
			char temp_Path[128] = { 0 };
			sprintf(sTempPath, "%c%c%c", sTmpFileName[0], sTmpFileName[1], sTmpFileName[2]);
			strcat(sTempPath, "GDWorkPath\\Temporary\\");
			int index = 0;
			for (int j = strlen(sTmpFileName.c_str()) - 1;; j--)
			{
				if (sTmpFileName[j] == '\\')
				{
					break;
				}
				temp_Path[index] = sTmpFileName[j];
				index++;
			}
			int j = 0;
			for (int i = strlen(temp_Path) - 1; i >= 0; i--)
			{
				sTempPath[j + 24] = temp_Path[i];
				j++;
			}
			if (off == 0)
			{
				//只是在第一次读取文件的时候进行解密即可
				int nRet = Lzwd(sTmpFileName.c_str(), sTempPath);
			}
			fp = CGDFile::open(sTempPath, "rb");

#else
			char temp_Path[128] = { 0 };
			strcpy(sTempPath, CToolbox::GetGDTempPath(GetInforGuardPath()).c_str());
			int index = 0, j = 0, pathlen = strlen(sTempPath);
			for (j = sTmpFileName.length() - 1;; j--)
			{
				if (sTmpFileName[j] == '/')
				{
					break;
				}
				temp_Path[index] = sTmpFileName[j];
				index++;
			}
			j = 0;
			for (int i = strlen(temp_Path) - 1; i >= 0; i--)
			{
				sTempPath[j + pathlen] = temp_Path[i];
				j++;
			}

			if (off == 0)
			{
				//只是在第一次读取文件的时候进行解密即可
				int nRet = Lzwd(sTmpFileName.c_str(), sTempPath);
			}
			fp = CGDFile::open(sTempPath, "rb");

#endif
		}
		else
		{
			fp = CGDFile::open(sTmpFileName.c_str(), "rb");
		}
	} //endif 启用加解密
	else
	{
		fp = CGDFile::open(sTmpFileName.c_str(), "rb");
	}
	//////////////////////////////
	// 打开文件读
	// FILE *fp = CGDFile::open(sTmpFileName.c_str(), "rb");
	if (fp)
	{
		// liu_yfeng 为支持大文件改为fsetpos
		if (off > 0)
		{
#ifdef AIX
			int retval = fsetpos64(fp, (const fpos64_t *)&off);
#elif defined Linux
			fpos_t nOffset = { 0 };
			nOffset.__pos = off;
			int retval = fsetpos(fp, &nOffset);
#else
			int retval = fsetpos(fp, (const fpos_t *)&off);
#endif
			if (retval)
			{
				CGDLog::WriteErrLog("FileTran_impl:GetFileBlock(): fsetpos(%" FMT_LL "d) failed with [%d][%s]", off, errno, strerror(errno));
			}
		}

		//out = new OctetSeq;
		//out->length(len);
		//len = fread(out->get_buffer(), 1, len, fp);
		char *buff_ = new char[len];
		len = fread(buff_, 1, len, fp);
		CGDFile::close(fp);

		if (trans_flag == '1') //////传输前加密 MA从SA拉文件
		{
			for (int index = 0; index < len; index++)
			{
				//out->get_buffer()[index] = out->get_buffer()[index] ^ 12345;
				buff_[index] = buff_[index] ^ 12345;
			}
		}

		buff.assign(buff_, len);

		/////////////////////////
		//本来不能确定何时删除文件，但如果len<262144，就可以说明该文件已经读取完毕。
		if (CAppConfig::encryption == 1) //启用了备份端加解密
		{
			if (strcmp(GetAppName(), "sa") == 0)
			{
				if (len < 262144)
				{
#ifdef WIN32
					DeleteFile(sTempPath);
#else
					unlink(sTempPath);
#endif
				}
			}
		}
		////////////////////////
		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	else
	{
		// 打开文件读失败
		ErrCode errCode = GetLastError();
		// 抛出异常
		//InforGuard::ExceptionError e;
		ex.nErrCode = errCode;
		char sBuf[512] = { 0 };
		if (errCode == 5)
		{
			sprintf(sBuf, "FileTran_impl:GetFileBlock(). CGDFile:open(%s)失败[%d][%s][拒绝访问]",
				sTmpFileName.c_str(), ex.nErrCode, GetErrText(ex.nErrCode));
		}
		else
		{
			sprintf(sBuf, "FileTran_impl:GetFileBlock(). CGDFile:open(%s)失败[%d][%s]",
				sTmpFileName.c_str(), ex.nErrCode, GetErrText(ex.nErrCode));
		}
		//ex.vErrText.length(1);
		ex.vErrText.push_back(sBuf);

		return -1;
	}

	return 0;
}

int
CFileTranServerImpl::
PutFileBlock(	st_NetCallData &call,
				const string &filename,
				const __int64 off,
				__int32 &len,
				const string &buff,
				st_ExceptionError &ex)
{
	printf("PutFileBlock\n");

	printf("filename:%s\n", filename.c_str());
	printf("off:%d\n", off);
	printf("len:%d\n", len);
	printf("buff.len:%d\n", buff.size());

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("fileserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);
	char trans_flag = '0';
	//string buff = "";
	trans_flag = filename[0];

	string sTmpFileName = filename;
	sTmpFileName = sTmpFileName.substr(1);
	CGDString::MakeSureLocalPath(sTmpFileName);

	// 打开文件写
	FILE *fp = NULL;

	if (off == 0)
	{
		fp = CGDFile::open(sTmpFileName.c_str(), "wb");
	}
	else
	{
		fp = CGDFile::open(sTmpFileName.c_str(), "ab");
	}

	if (fp)
	{
		// liu_yfeng 为支持大文件改为fsetpos
		if (off)
		{
#ifdef AIX
			int retval = fsetpos64(fp, (const fpos64_t *)&off);
#elif defined Linux
			fpos_t nOffset = { 0 };
			nOffset.__pos = off;
			int retval = fsetpos(fp, &nOffset);
#else
			int retval = fsetpos(fp, (const fpos_t *)&off);
#endif
			if (retval)
			{
				CGDLog::WriteErrLog("FileTran_impl:PutFileBlock(): fsetpos(% " FMT_LL " d) failed with [%d][%s]",
					off, errno, strerror(errno));
			}
		}
		if (trans_flag == '1') ////////////传过来后解密 SA推文件到MA后,或者MA推文件到SA后
		{
			for (int index = 0; index < len; index++)
			{
				// buff += ( buf.get_buffer() )[index]^12345;
				//transblock[index] = (buf.get_buffer())[index] ^ 12345;
				transblock[index] = buff[index] ^ 12345;
			}
		}
		if (len > 0)
		{
			long realen = 0;
			//	realen = fwrite( buf.get_buffer(), 1, len, fp );
			if (trans_flag == '1')
				//	realen = fwrite( buff.c_str(), 1, len, fp );
				realen = fwrite(transblock, 1, len, fp);
			else
				//realen = fwrite(buf.get_buffer(), 1, len, fp);
				realen = fwrite(buff.c_str(), 1, len, fp);

			if (realen != len)
			{
				// 写入文件失败
				CGDFile::close(fp);
				//CExceptionError ex;
				string tmpErrMsg;
				ex.nErrCode = GetLastError();
				tmpErrMsg = GetErrText(ex.nErrCode);
				ex.vErrText.push_back(tmpErrMsg);
				//ex.AddErrText("%s", GetErrText(ex.nErrCode)); //wu_bin加前台错误信息

				tmpErrMsg = "写入数据失败[";
				tmpErrMsg += sTmpFileName;
				tmpErrMsg += "][";
				tmpErrMsg += to_string(ex.nErrCode);
				tmpErrMsg += "][";
				tmpErrMsg += GetErrText(ex.nErrCode);
				tmpErrMsg += "]";
				ex.vErrText.push_back(tmpErrMsg);
				//ex.AddErrText("写入数据失败[%s][%d][%s]", sTmpFileName.c_str(), ex.m_nErrCode, GetErrText(ex.m_nErrCode));
				
				tmpErrMsg = "FileTran_impl::PutFileBlock(";
				tmpErrMsg += sTmpFileName;
				tmpErrMsg += ")";
				ex.vErrText.push_back(tmpErrMsg);
				//ex.AddErrText("FileTran_impl::PutFileBlock(%s)", sTmpFileName.c_str());
				// 抛出异常
				//InforGuard::ExceptionError e;
				//CNetTran::ConvertException(ex, e);
				//e._raise();
				return ex.nErrCode;
			}
		}

		CGDFile::close(fp);

		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	else
	{
		// 写打开文件失败
		//CExceptionError ex;
		//ex.m_nErrCode = GetLastError();
		//ex.AddErrText("%s", GetErrText(ex.m_nErrCode)); //wu_bin加前台错误信息
		string tmpErrMsg;
		ex.nErrCode = GetLastError();
		tmpErrMsg = GetErrText(ex.nErrCode);
		ex.vErrText.push_back(tmpErrMsg);

		tmpErrMsg = "写打开文件失败[";
		tmpErrMsg += sTmpFileName;
		tmpErrMsg += "][";
		tmpErrMsg += to_string(ex.nErrCode);
		tmpErrMsg += "][";
		tmpErrMsg += GetErrText(ex.nErrCode);
		tmpErrMsg += "]";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("写打开文件失败[%s][%d][%s]", sTmpFileName.c_str(), ex.m_nErrCode, GetErrText(ex.m_nErrCode));

		tmpErrMsg = "FileTran_impl::PutFileBlock(";
		tmpErrMsg += sTmpFileName;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("FileTran_impl::PutFileBlock(%s)", sTmpFileName.c_str());
		// 抛出异常
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		return ex.nErrCode;
	}

	return 0;
}

int
CFileTranServerImpl::
MakeDirectory(	st_NetCallData &call,
				const string &filename,
				const bool &temp,
				st_ExceptionError &ex)
{
	printf("MakeDirectory\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("fileserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	string sParam;
	sParam = sParam + "sFileName[" + filename + "]bTmp[" + (temp ? "1" : "0") + "]";

	CGDTrace trace(LOG_L6, "FileTran_impl:MakeDirectory(%s)", sParam.c_str());

	string sTmpFileName = filename;

	try
	{
#ifndef WIN32
		// 判断是否符号链接
		int nSplit = sTmpFileName.find_first_of('|');
		if (nSplit > 0)
		{
			bool bFileDriver = false; //文件保护监控器 add by dai_hyan 2010-2-22
#ifdef Linux
			string sBasePath = "";
			string tmpName = sTmpFileName.substr(nSplit + 1);
			bFileDriver = CFileOptEx::IsProtect(tmpName.c_str());
			if (bFileDriver)
			{
				int nLen = strlen(tmpName.c_str());
				while (nLen >= 3 && tmpName[nLen - 2] != C_PATHLASH)
					nLen--;
				if (nLen < 3)
				{
					// 目录名称无效，抛
					string tmpErrMsg;
					//CExceptionError ex;
					//ex.m_nErrCode = CAppError::GD_APP_ERR_EXCEPTION_INFORGUARD;
					ex.nErrCode = CAppError::GD_APP_ERR_EXCEPTION_INFORGUARD;

					tmpErrMsg = "创建目录时目录名称无效[";
					tmpErrMsg += tmpName;
					tmpErrMsg += "]";
					ex.vErrText.push_back(tmpErrMsg);
					//ex.AddErrText("创建目录时目录名称无效[%s]", tmpName.c_str());

					tmpErrMsg = "ProctectMakeSureDirExistLegally(";
					tmpErrMsg += tmpName;
					tmpErrMsg += ")";
					ex.vErrText.push_back(tmpErrMsg);
					//ex.AddErrText("ProctectMakeSureDirExistLegally(%s)", tmpName.c_str());

					tmpErrMsg = "ProtectMakeSureDirExist(";
					tmpErrMsg += tmpName;
					tmpErrMsg += ")";
					ex.vErrText.push_back(tmpErrMsg);
					//ex.AddErrText("ProtectMakeSureDirExist(%s)", tmpName.c_str());
					//throw ex;
				}
				sBasePath = tmpName;
				sBasePath = sBasePath.substr(0, nLen - 2);
				trace.GDTrace(LOG_NOT, "delete attrbute[%s]", sBasePath.c_str());
				int nTemp = CFileProtect::chDirAttr(sBasePath.c_str(), false, false, false, "");
				if (nTemp > 0)
				{
					nTemp = 0;
					CGDLog::WriteErrLog("FileTran_impl:MakeDirectory[%s] delete", sBasePath.c_str());
				}
			}
			string sCmd = "ln -s ";
			sCmd += sTmpFileName.substr(0, nSplit);
			sCmd += " ";
			sCmd += sTmpFileName.substr(nSplit + 1);
			trace.GDTrace(LOG_NOT, "create link[%s]", sCmd.c_str());
			//注册事件
			EVENT_S newEvt = { 0 };
			newEvt.event_type = MONITOR_EVENT_NOFIER_CREATE; //上报新建
			strcpy(newEvt.o_filepath, sTmpFileName.substr(nSplit + 1).c_str());
			CFileOptEx::RegisterLegalEvent(newEvt);
			system(sCmd.c_str());
			if (bFileDriver)
			{
				int mTemp = CFileProtect::chDirAttr(sBasePath.c_str(), true, false, false, "");
				if (mTemp > 0)
				{
					mTemp = 0;
					CGDLog::WriteErrLog("FileTran_impl:MakeDirectory[%s] add", sBasePath.c_str());
				}
			}

			return 0;
#else
			string sCmd = "ln -s ";
			sCmd += sTmpFileName.substr(0, nSplit);
			sCmd += " ";
			sCmd += sTmpFileName.substr(nSplit + 1);
			trace.GDTrace(LOG_NOT, "create link[%s]", sCmd.c_str());
			//注册事件
			EVENT_S newEvt = { 0 };
			newEvt.event_type = MONITOR_EVENT_NOFIER_CREATE; //上报新建
			strcpy(newEvt.o_filepath, sTmpFileName.substr(nSplit + 1).c_str());
			CFileOptEx::RegisterLegalEvent(newEvt);
			system(sCmd.c_str());
			return 0;
#endif
		}
#endif
		CGDString::MakeSureLocalPath(sTmpFileName);
		if (temp) // 临时目录
		{
			CFileOpt::MakeSureDirExist(sTmpFileName.c_str());
		}
		else // 工作目录
		{
			// 建立文件夹
			CFileOptEx::MakeSureDirExistLegally(sTmpFileName.c_str());
		}

		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:MakeDirectory(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("FileTran_impl:MakeDirectory(%s)", sParam.c_str());
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		return ex.nErrCode;
	}
	catch (...)
	{
		//CExceptionError ex;
		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:MakeDirectory(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")catch(...)";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("FileTran_impl:MakeDirectory(%s)catch(...)", sParam.c_str());
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		return ex.nErrCode;
	}

	return 0;
}

int
CFileTranServerImpl::
MoveFileIn(	st_NetCallData &call,
			const string &srcfile,
			const string &dstfile,
			const string &delfile,
			const bool &bTopPath,
			st_ExceptionError &ex)
{
	printf("MoveFileIn\n");

	printf("srcfile:%s\n", srcfile.c_str());
	printf("dstfile:%s\n", dstfile.c_str());
	printf("delfile:%s\n", delfile.c_str());

	//==========================hy的完全同步日志.setdata("2013.1.22")==================================
	//==========================warning:以下内容必须在ma监控开启下使用=================================
	string hoststring = CAppConfig::Instance().GetHostId();
	vector<string> newfile, coverfile;
	GDDateTime tam_time;
	bool isdir = false;
	bool sendlog = false;
	//if(CFileOpt::IsExist(srcfile,&isdir)&&CFileOpt::IsExist(dstfile,&isdir)&&(strcmp(GetAppName(),"ma")==0))
	if (CFileOpt::IsExist(srcfile.c_str(), &isdir) && isdir)	
	{
		//判断是否为完全同步，ma篡改恢复不走这里，sa新建新文件、文件夹、复制目录结构时srcfile全部为实际文件，目前只有完全同步srcfile为实际目录
		if ((CAppOption::Instance().GetOption("runinfor.synclog", 0) == 1) && (strcmp(GetAppName(), "ma") == 0))
		{
			sendlog = true;
		}
		vector<string> delfile;
		int ifdel = CAppOption::Instance().GetOption("syncdel.fullsyncdel", 0);
		if (sendlog || ifdel)
		{
			CFileOptEx::GetOperationVector(srcfile.c_str(), dstfile.c_str(), newfile, coverfile, delfile);
		}
		GDDateTime tam_time;
		CDateTime::GetTime(tam_time);
		int i;
		bool temp = false;
		if (ifdel == 0)
		{
			delfile.clear();
		}
		for (i = 0; i < delfile.size(); i++)
		{
			char tempchar = delfile[i].at(delfile[i].length() - 1);
			if (tempchar == C_PATHLASH)
			{
				string removedirpath = dstfile + delfile[i].substr(0, delfile[i].length() - 1);
				bool tempbool = CAppConfig::Instance().IsExcludeFile(removedirpath, dstfile);
				// CApp和CAppConfig是static，可以调用多种函数，这里用来判断排除文件
				if (!tempbool)
				{
					CDateTime::GetTime(tam_time);
					try
					{
						if (!CFileOpt::IsExist(removedirpath.c_str()))
						{
							if (sendlog)
							{
								CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法删除", &tam_time, &tam_time, NULL, removedirpath.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
							}
							continue;
						}
						CFileOpt::RemoveDir(removedirpath.c_str());
						if (sendlog)
						{
							CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法删除", &tam_time, &tam_time, NULL, removedirpath.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
						}
					}
					catch (CExceptionError &)
					{
						if (sendlog)
						{
							CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法删除", &tam_time, &tam_time, NULL, removedirpath.c_str(), 0, RUN_INFOR_OPT_FAIL, 0, CAppConfig::Instance().GetLocalIp().c_str());
						} //throw ex;
					}
				}
				else
				{
					// cout << "exclude dir:" << removedirpath << "\n";
				}
			}
			else
			{
				string removefilepath = dstfile + delfile[i];
				bool tempbool = CAppConfig::Instance().IsExcludeFile(removefilepath, dstfile);
				if (!tempbool)
				{
					CDateTime::GetTime(tam_time);
					try
					{
						if (!CFileOpt::IsExist(removefilepath.c_str()))
						{
							if (sendlog)
							{
								CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法删除", &tam_time, &tam_time, NULL, removefilepath.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
							}
							continue;
						}
						CFileOpt::RemoveFile(removefilepath.c_str());
						if (sendlog)
						{
							CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法删除", &tam_time, &tam_time, NULL, removefilepath.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
						}
					}
					catch (CExceptionError &)
					{
						if (sendlog)
						{
							CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法删除", &tam_time, &tam_time, NULL, removefilepath.c_str(), 0, RUN_INFOR_OPT_FAIL, 0, CAppConfig::Instance().GetLocalIp().c_str());
						} //throw ex;
					}
				}
				else
				{
					//cout<<"exclude file:"<<removefilepath<<"\n";
				}
			}
		}
	}
	//===================================hy的完全同步日志.flush()=================================

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("fileserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	string sParam;
	sParam = sParam + "srcfile[" + srcfile + "]dstfile[" + dstfile + "]delfile[" + delfile + "]bTopPath[" + (bTopPath ? "1" : "0") + "]";

	CGDTrace trace(LOG_L6, "FileTran_impl:MoveFileIn(%s)", sParam.c_str());

	int nRet = -1;
	string sTmpSrcFile = srcfile;
	string sTmpDstFile = dstfile;
	string sTmpDelFile = delfile;

	CGDString::MakeSureLocalPath(sTmpSrcFile);
	CGDString::MakeSureLocalPath(sTmpDstFile);
	CGDString::MakeSureLocalPath(sTmpDelFile);

	char tmpDelDir[GD_MAX_PATH] = { 0 };
	CFileOpt::GetParentDir(delfile.c_str(), tmpDelDir);
	CFileOpt::MakeSureDirExist(tmpDelDir);

	bool bMonitor = CAppConfig::Instance().IsFileMonitoring(dstfile);

	try
	{
#if 0 // 已优化 at 2010-01-05 by wang_jin 暂时不优化 at 2008-11-27 by wang_jin at 2008-11-21 优化Windows平台文件移入

#if defined WIN32 || defined INOTIFY_SUPPORT // 监控顶级目录不能直接移入
		if (bTopPath)
		{
			nRet = CFileOptEx::MoveAllIntoWorkspace(bMonitor, sTmpSrcFile.c_str(), sTmpDstFile.c_str(), sTmpDelFile.c_str());
		}
		else
		{
			nRet = CFileOptEx::MoveFileInLegally(bMonitor, sTmpSrcFile.c_str(), sTmpDstFile.c_str(), sTmpDelFile.c_str());
		}
#else // 监控顶级目录可以直接移入
		nRet = CFileOptEx::MoveFileInLegally(bMonitor, sTmpSrcFile.c_str(), sTmpDstFile.c_str(), sTmpDelFile.c_str());
#endif

#else
		CFileOptEx::MoveFileIntoWorkspace(bTopPath, sTmpSrcFile.c_str(), sTmpDstFile.c_str(), sTmpDelFile.c_str());
		nRet = 0;

#endif
		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		//============================hy的完全同步日志.setdata("2013.1.22")==================================================
		int i;
		if (strcmp(GetAppName(), "ma") == 0 && sendlog)
		{

			string errorlog, analystr = dstfile;
			int errorlogpos = 0, keywordpos;
			while (errorlogpos < ex1.m_vErrText.size())
			{
				errorlog = ex1.m_vErrText[errorlogpos];
				keywordpos = errorlog.find("MoveFileEx(");
				if (keywordpos == string::npos)
				{
					errorlogpos++;
					continue;
				}
				errorlog = errorlog.substr(keywordpos + 11, errorlog.find_first_of(",") - (keywordpos * 2 + 1));
				errorlog = errorlog.substr(analystr.length());
				//遍历合法新建
				for (i = 0; i < newfile.size(); i++)
				{
					if (newfile[i] == errorlog)
					{
						string currfile = dstfile + newfile[i];
						newfile[i] = S_PATHLASH;
						CDateTime::GetTime(tam_time);
						CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法新建", &tam_time, &tam_time, NULL, currfile.c_str(), 0, RUN_INFOR_OPT_FAIL, 0, CAppConfig::Instance().GetLocalIp().c_str());
						break;
					}
				}
				if ((i == 0) && (newfile.size() != 0))
				{
					errorlogpos++;
					continue;
				}
				//遍历合法修改
				for (i = 0; i < coverfile.size(); i++)
				{
					if (coverfile[i] == errorlog)
					{
						string currfile = dstfile + coverfile[i];
						coverfile[i] = S_PATHLASH;
						CDateTime::GetTime(tam_time);
						CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法修改", &tam_time, &tam_time, NULL, currfile.c_str(), 0, RUN_INFOR_OPT_FAIL, 0, CAppConfig::Instance().GetLocalIp().c_str());
						break;
					}
				}
				errorlogpos++;
			}
			//失败检查完毕
			for (i = 0; i < newfile.size(); i++)
			{
				if (newfile[i] == S_PATHLASH)
				{
					continue;
				}
				string currfile = dstfile + newfile[i];
				CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法新建", &tam_time, &tam_time, NULL, currfile.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
			}
			for (i = 0; i < coverfile.size(); i++)
			{
				if (coverfile[i] == S_PATHLASH)
				{
					continue;
				}
				string currfile = dstfile + coverfile[i];
				CDateTime::GetTime(tam_time);
				CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法修改", &tam_time, &tam_time, NULL, currfile.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
			}
		}
		//发送消息完毕
		//===================================hy的完全同步日志.flush()=================================

		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:MoveFileIn(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("FileTran_impl:MoveFileIn(%s)", sParam.c_str());
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		return ex.nErrCode;
	}
	int i = 0;
	//===============hy add @13.9.2013=============================================
	if (sendlog)
	{
		for (i = 0; i < coverfile.size(); i++)
		{
			if (coverfile[i] != S_PATHLASH)
			{
				string currfile = dstfile + coverfile[i];
				CDateTime::GetTime(tam_time);
				CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法修改", &tam_time, &tam_time, NULL, currfile.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
			}
		}
		for (i = 0; i < newfile.size(); i++)
		{
			if (newfile[i] != S_PATHLASH)
			{
				string currfile = dstfile + newfile[i];
				CDateTime::GetTime(tam_time);
				CApp::Instance().RunInfor().SendToMcWithWebsiteID(0, RUN_MANUAL_SYNC, "合法新建", &tam_time, &tam_time, NULL, currfile.c_str(), 0, RUN_INFOR_OPT_SUCESS, 0, CAppConfig::Instance().GetLocalIp().c_str());
			}
		}
	}
#ifndef WIN32
	if (CAppOption::Instance().GetOption("handleevent.chattr", 0) == 1)
	{
		SiteDirectory siteDirectory;
		CAppConfig::Instance().GetSiteDirectoryByLocalFileName(dstfile, siteDirectory);
		CFileList Clist;
		FileList Temp;
		Clist.CreateList(dstfile, Temp, CFileList::FILE_OPTION_FILE | CFileList::FILE_OPTION_DIRECTORY);
		list<FileListNode>::iterator tempIter;
		for (tempIter = Temp.begin(); tempIter != Temp.end(); ++tempIter)
		{
			if (CFileOpt::IsExist(dstfile, &isdir) && !(isdir))
			{
				string FastSyncFileName = tempIter->name;
				SiteDirectory tempSiteDir;
				CAppConfig::Instance().GetSiteDirectoryByLocalFileName(FastSyncFileName, tempSiteDir);
				if (tempSiteDir.localPath.size() > 0)
				{
					while (FastSyncFileName != tempSiteDir.localPath)
					{
						CFileOpt::GetParentDir(FastSyncFileName.c_str(), FastSyncFileName);
						nRet = lchown(FastSyncFileName.c_str(), siteDirectory.uid, siteDirectory.gid);
					}
				}
			}
			//修正快速同步，增量同步文件夹用户权限问题
			nRet = lchown(tempIter->name.c_str(), siteDirectory.uid, siteDirectory.gid);
			if (tempIter->isfolder)
			{
				nRet = chmod(tempIter->name.c_str(), siteDirectory.dattr);
			}
			else
			{
				nRet = chmod(tempIter->name.c_str(), siteDirectory.fattr);
			}
		}
	}
#endif

	//=================hy add end==================================================
	return trace.SetRetValue(nRet);
}

int
CFileTranServerImpl::
MoveFileOut(st_NetCallData &call,
			const string &srcfile,
			const string &dstfile,
			st_ExceptionError &ex)
{
	printf("MoveFileOut\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("fileserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	string sParam;
	sParam = sParam + "srcfile[" + srcfile + "]dstfile[" + dstfile + "]";

	CGDTrace trace(LOG_L6, "FileTran_impl:MoveFileOut(%s)", sParam.c_str());

	int nRet = 0;
	string sTmpSrcFile = srcfile;
	string sTmpDstFile = dstfile;

	CGDString::MakeSureLocalPath(sTmpSrcFile);
	CGDString::MakeSureLocalPath(sTmpDstFile);

	try
	{
		nRet = CFileOptEx::MoveFileOutLegally(sTmpSrcFile.c_str(), sTmpDstFile.c_str());
		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:MoveFileOut(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("FileTran_impl:MoveFileOut(%s)", sParam.c_str());
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}

	return nRet;
}

int
CFileTranServerImpl::
RenameFile(	st_NetCallData &call,
			const string &oldfile,
			const string &newfile,
			const __int32 &attr,
			st_ExceptionError &ex)
{
	printf("RenameFile\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("fileserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	string sParam;
	sParam = sParam + "oldfile[" + oldfile + "]newfile[" + newfile + "]attr[" + CGDString::ltoa(attr) + "]";

	CGDTrace trace(LOG_L6, "FileTran_impl:RenameFile(%s)", sParam.c_str());

	int nRet = 0;
	string sTmpOldFile = oldfile;
	string sTmpNewFile = newfile;

	CGDString::MakeSureLocalPath(sTmpOldFile);
	CGDString::MakeSureLocalPath(sTmpNewFile);

	try
	{
		nRet = CFileOptEx::RenameLegally(sTmpOldFile.c_str(), sTmpNewFile.c_str(), attr);

		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:RenameFile(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("FileTran_impl:RenameFile(%s)", sParam.c_str());
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}

	return nRet;
}

int
CFileTranServerImpl::
QueryBasePath(string &basepath, st_ExceptionError &ex)
{
	printf("QueryBasePath\n");

	CGDTrace trace(LOG_L6, "FileTran_impl:QueryBasePath()");
	basepath = "";
	int nRet = 0;

	try
	{
		const char *curPath = GetInforGuardPath();
		if (curPath && (strlen(curPath) > 0))
		{
			basepath = curPath;
			trace.SetOutParam(curPath);
		}
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:QueryBasePath";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("FileTran_impl:QueryBasePath");
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}

	return nRet;
}

int
CFileTranServerImpl::
isFileExist(const string &filePath, __int32 &fileSize, st_ExceptionError &ex)
{
	printf("isFileExist\n");

	CGDTrace trace(LOG_L6, "FileTran_impl:isFileExist()");
	int nRet = 9999; //默认返回一个极大值
	bool bExist = false;

	try
	{
		bExist = CFileOpt::IsExist(filePath.c_str());
		if (bExist == true)
		{ //如果文件存在的话，把返回值转换成零，表示文件存在，并获得文件大小
			nRet = 0;
			fileSize = CFileOpt::GetFileSize(filePath.c_str());
		}
		else
			nRet = 1; //文件不存在返回1，这里没有考虑文件没有读权限的情况
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:isFileExist";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("FileTran_impl:isFileExist");
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}

	return nRet;
}

int
CFileTranServerImpl::
setFileTime(st_NetCallData &call,
			const string &filename,
			const __int32 &mtime,
			st_ExceptionError &ex)
{
	printf("setFileTime\n");

	CGDTrace trace(LOG_L6, "FileTran_impl:setFileTime()");
	int nRet = 9999; //默认返回一个极大值

	try
	{
		// GDPrint("ma:mtime:%l\n", mtime);
		long mtime_ = mtime;
		nRet = CFileOpt::setFileTime(filename.c_str(), mtime_);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:setFileTime";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("FileTran_impl:setFileTime");
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}

	return nRet;
}

int
CFileTranServerImpl::
getFileTime(st_NetCallData &call,
			const string &filename,
			__int32 &mtime,
			st_ExceptionError &ex)
{
	printf("getFileTime\n");

	CGDTrace trace(LOG_L6, "FileTran_impl:getFileTime()");
	int nRet = 9999; //默认返回一个极大值

	try
	{
		long mtime_ = mtime;
		if (CFileOpt::getFileTime(filename.c_str(), mtime_) == 0)
			nRet = 0;
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:getFileTime";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("FileTran_impl:getFileTime");
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}

	return nRet;
}

int
CFileTranServerImpl::
sendFileList(const DistCommSysData_::RemoteDirectoryList &list, st_ExceptionError &ex)
{
	printf("sendFileList\n");

	CGDTrace trace(LOG_L6, "FileTran_impl:sendFileList()");
	int nRet = 0;

	CGDLog::WriteSysLog("[FileTran_impl-sendFileList] started --------------------");

	if (strcmp(GetAppName(), "ma") != 0)
	{
		CGDLog::WriteSysLog("[FileTran_impl-sendFileList] warning: sendFileList is only for InforGuardMa.");
		return -1;
	}

	unsigned long int ulSerialNo = time(NULL) << 10;

	try
	{
		// 遍历目录列表
		//for (int i = 0; i < remoteDirectoryList.length(); i++)
		for (int i = 0; i < list.size(); i++)
		{
			string remoteDirectoryId = list[i].id;

			// 根据 remoteDirectoryId 获取本地目录id及其他信息
			string sBackupId;
			string sBackupIp;
			string sBackupPort;
			string sBackupRoot;
			string sLocalRoot;
			bool bGetConfig = false;
			std::vector<WebSite> webSites;
			CAppConfig::Instance().GetWebSites(webSites);
			std::vector<WebSite>::iterator itWebSite;
			for (itWebSite = webSites.begin(); itWebSite != webSites.end() && !bGetConfig; ++itWebSite)
			{
				std::vector<SiteDirectory>::iterator itDirectory;
				for (itDirectory = itWebSite->siteDirectorys.begin(); itDirectory != itWebSite->siteDirectorys.end() && !bGetConfig; ++itDirectory)
				{
					std::vector<RemotePath> remotePaths = itDirectory->remotePaths;
					std::vector<RemotePath>::iterator itRemotePath;
					for (itRemotePath = remotePaths.begin(); itRemotePath != remotePaths.end() && !bGetConfig; ++itRemotePath)
					{
						if (itRemotePath->id == remoteDirectoryId)
						{
							sBackupId = itRemotePath->id;
							sBackupIp = itRemotePath->ip;
							sBackupPort = itRemotePath->port;
							sBackupRoot = itRemotePath->path;
							sLocalRoot = itDirectory->localPath;
							bGetConfig = true;
						}
					}
				}
			}
			if (!bGetConfig)
			{
				CGDLog::WriteErrLog("Cannot find a directory whose id is \"%s\".", remoteDirectoryId.c_str());
				GDPrintln("Cannot find a directory whose id is \"%s\".", remoteDirectoryId.c_str());
				continue;
			}

#ifdef WIN32
			string sDustDir = CToolbox::GetGDDustPath(sLocalRoot.c_str());
#else
			string sDustDir = CToolbox::GetGDDustPath(GetInforGuardPath()); // 垃圾目录
			if (sDustDir.empty())
			{
				CGDLog::WriteErrLog("1002:GetPeerDustPath() fail");
				return -1;
			}
#endif

			CPullListSaver *writer = CPullListSaver::CreateWriter(remoteDirectoryId);
			if (writer == NULL)
			{
				CGDLog::WriteErrLog("[FileTran_impl-sendFileList] CreateWriter(\"%s\") failed.", remoteDirectoryId.c_str());
				continue;
			}
			string writerFilePath = writer->GetFilePath();
			int fileInfoCount = 0;

			// 遍历文件列表
			int fileListLength = list[i].list.size();
			CGDLog::WriteSysLog("From [%s:%s] \"%s\" received fileList length is %d", sBackupIp.c_str(), sBackupPort.c_str(), sBackupRoot.c_str(), fileListLength);
			for (int j = 0; j < fileListLength; j++)
			{
				string sFilepathSa = list[i].list[j].name; // 文件路径
				string sFilepathLocal = sFilepathSa;
				CTool::FormatPath(sFilepathSa);
				sFilepathLocal.replace(0, sBackupRoot.length(), sLocalRoot);
				CTool::FormatPath(sFilepathLocal);
				// GDPrintln("sFilePathSa=\"%s\", sFilePathLocal=\"%s\"", sFilepathSa.c_str(), sFilepathLocal.c_str());
				// 对排除文件不做任何处理
				if (CAppConfig::Instance().IsExcludeFile(sFilepathLocal))
				{
					continue;
				}

				long mtimeSa = list[i].list[j].mtime; // 修改时间
				long operation = list[i].list[j].type; // 1:新增 2:删除 3:修改
				bool bIsFile = list[i].list[j].isfile; // true:文件 false:文件夹

																	  // GDPrintln("name=\"%s\", mtime=%d, operation=%d, isfile=%s", remoteDirectoryList[i].list[j].name.in(), mtimeSa, operation, bIsFile ? "true" : "false");

				if (operation == 2)
				{ // 执行删除操作
				  //char tmpPath[sDustDir.length() + 16];
				  //必须含有常量值，所以不能动态定义数组
					char tmpPath[1024] = { 0 };
					sprintf(tmpPath, "%s%lu", sDustDir.c_str(), ulSerialNo++);
					// GDPrint("preparing to move \"%s\" to \"%s\".\n",
					// sFilepathLocal.c_str(), tmpPath);
					nRet = CFileOptEx::MoveFileOutLegally(sFilepathLocal.c_str(), tmpPath);
					if (nRet != 0 || nRet != 404)
					{
						CGDLog::WriteErrLog("[FileTran_impl:sendFileList] delete file or directory \"%s\" failed!", sFilepathLocal.c_str());
						GDPrintln("[FileTran_impl:sendFileList] delete file or directory \"%s\" failed!", sFilepathLocal.c_str());
					}
					continue; // 直接进行到下一轮循环
				}

				if (bIsFile) // 把文件除删除外操作记录到本地文件
				{
					long mtimeLocal = -1;
					struct stat buf;
					if (stat(sFilepathLocal.c_str(), &buf) == 0)
					{
						mtimeLocal = buf.st_mtime;
					}
					// GDPrintln("sFilepathSa=%s sFilepathLocal=%s mtimeSa=%ld mtimeLocal=%ld operation=%ld bIsFile=%d",
					//           sFilepathSa.c_str(), sFilepathLocal.c_str(), mtimeSa, mtimeLocal, operation, bIsFile);
					if (mtimeSa <= mtimeLocal) // 文件已更新，直接进行到下一轮循环
					{
						continue;
					}
					CFileNodeInfo info(sFilepathSa, mtimeSa);
					writer->WriteLine(info);
					fileInfoCount++;
				} // if ( bIsFile ) end
				else // 处理文件夹除删除外操作，创建文件夹
				{
					GDPrintln("prepare to make directory \"%s\".", sFilepathLocal.c_str());
					if (CFileOptEx::MakeSureDirExistLegally(sFilepathLocal.c_str()) != 0)
					{
						CGDLog::WriteErrLog("[FileTran_impl:sendFileList] create directory \"%s\" failed!", sFilepathLocal.c_str());
						GDPrintln("[FileTran_impl:sendFileList] create directory \"%s\" failed!", sFilepathLocal.c_str());
					}
					continue;
				} // if ( bIsFile ) else end
			} // for (int j = 0; j < fileListLength; j++) end
			if (fileInfoCount == 0)
			{
				writer->CloseAndDelete();
			}
			else
			{
				writer->Close();
			}
			delete writer;
			writer = NULL;
		} // for (int i = 0; i < remoteDirectoryList.length(); i++) end
	}
	catch (CExceptionError &ex1)
	{
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] error!");
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] CExceptionError");
		GDPrintln("[FileTran_impl:sendFileList] CExceptionError");

		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "FileTran_impl:sendFileList()";
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("FileTran_impl:sendFileList()");
		// 转换异常格式
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = ex.nErrCode;
	}
/*	catch (const InforGuard::ExceptionError &ex)
	{
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] error!");
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] InforGuard::ExceptionError");
		GDPrintln("[FileTran_impl:sendFileList] InforGuard::ExceptionError");
		ex._raise();
	}
	catch (const CORBA::Exception &ex)
	{
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] error!");
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] CORBA::Exception");
		GDPrintln("[FileTran_impl:sendFileList] CORBA::Exception");
		nRet = -1;
	}*/
	catch (const std::exception &ex)
	{
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] error!");
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] std::exception");
		GDPrintln("[FileTran_impl:sendFileList] std::exception");
		nRet = -1;
	}
	catch (...)
	{
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] error!");
		CGDLog::WriteErrLog("[FileTran_impl:sendFileList] other exception");
		GDPrintln("[FileTran_impl:sendFileList] other exception");
		nRet = -1;
	}
	// remoteDirectoryList = NULL;
	CGDLog::WriteSysLog("[FileTran_impl-sendFileList] finished.");

	return nRet;
}

int
CFileTranServerImpl::
sendAccess(st_ExceptionError &ex)
{
	printf("sendAccess\n");

	// 判断是否启用时间戳
	if (!CAppOption::Instance().GetOption("filetran.sendmtime", 0))
	{
		CGDLog::WriteErrLog("Time stamp is off, FileSynchronizer not availiable!");
		return -1;
	}
	return 0;
}

int
CFileTranServerImpl::
checkFileList(	const DistCommSysData_::NetFileList &inList,
	DistCommSysData_::ParamList &notExistList,
	DistCommSysData_::ParamList &diffList,
	st_ExceptionError &ex)
{
	printf("checkFileList\n");

	vector<string> notExistVec;
	vector<string> diffVec;
	int nInListSize = inList.size();
	GDPrintln("FileTran_impl::checkFileList nInListSize=%d", nInListSize);
	for (int i = 0; i < nInListSize; ++i)
	{
		string sPath = inList[i].name;
		GDPrintln("sPath=\"%s\"", sPath.c_str());
		bool bFolder = inList[i].isfolder;
		long nSize = inList[i].size;
		long nMtime = inList[i].time;
		bool bLocalIsDir;
		// 文件或目录存在
		if (CFileOpt::IsExist(sPath.c_str(), &bLocalIsDir))
		{
			if (bLocalIsDir != bFolder) // 本地与远端文件类型不一致
			{
				diffVec.push_back(sPath);
			}
			else if (!bLocalIsDir) // 文件类型都为文件，比对文件修改时间
			{
				time_t nLocalTime = CFileOpt::GetFileTime(sPath.c_str());
				if (nLocalTime == -1)
				{
					notExistVec.push_back(sPath);
				}
				else if (nLocalTime != nMtime || CFileOpt::GetFileSize(sPath.c_str()) != nSize)
				{
					diffVec.push_back(sPath);
				}
			}
		}
		// 文件或目录不存在
		else
		{
			notExistVec.push_back(sPath);
		}
	}
	try
	{
		int nNotExistSize = notExistVec.size();
		//notExistList = new InforGuard::ParamList();
		//notExistList->length(nNotExistSize);
		//for (int i = 0; i < nNotExistSize; ++i)
		//{
		//	notExistList[i] = CORBA::string_dup(notExistVec[i].c_str());
		//}
		notExistList = notExistVec;

		int nDiffSize = diffVec.size();
		//diffList = new InforGuard::ParamList();
		//diffList->length(nDiffSize);
		//for (int i = 0; i < nDiffSize; ++i)
		//{
		//	diffList[i] = CORBA::string_dup(diffVec[i].c_str());
		//}
		diffList = diffVec;

		GDPrintln("FileTran_impl::checkFileList nDiffSize=%d, nNotExistSize=%d", nDiffSize, nNotExistSize);
	}
	catch (...)
	{
		//CExceptionError ex;
		string tmpErrMsg;
		tmpErrMsg = "CheckFileList error: ";
		tmpErrMsg += strerror(errno);
		ex.vErrText.push_back(tmpErrMsg);
		//ex.AddErrText("CheckFileList error: %s", strerror(errno));
		//throw ex;
		return ex.nErrCode;
	}

	return 0;
}