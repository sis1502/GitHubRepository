#include "Server/NetWaterMark/NetWaterMarkServerImpl.h"

#include "Base/App.h"
#include "Base/FileListEx.h"
#include "Base/RunInfor.h"
#include "Base/Tool.h"
//#include "Base/NetTran.h"
#include "Base/FileTranQueue.h"
#include "FileOpt/FileOpt.h"
#include "GDLog/GDLog.h"
#include "GDLog/GDTrace.h"
#include "GDLog/ThreadData.h"
#include "WaterMark/WaterMarkDB.h"
//#include "NetWaterMark/NetWaterMark_impl.h"

CNetWaterMarkServerImpl::CNetWaterMarkServerImpl()
{
	//...
}


CNetWaterMarkServerImpl::~CNetWaterMarkServerImpl()
{
	//...
}

int
CNetWaterMarkServerImpl::
Check(st_ExceptionError &ex)
{
	printf("Check\n");

	return 0;
}

int
CNetWaterMarkServerImpl::
Set(st_NetCallData &call,
	const string &file,
	const string &wm,
	st_ExceptionError &ex)
{
	printf("Set\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("wmserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	//<< Ŀ¼ת��(������˷ֱ�ΪWindows�ͷ�Windows)
	char tmpfile[GD_MAX_PATH] = { 0 };
	strcpy(tmpfile, file.c_str());
	char * p = tmpfile;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	string sParam;
	sParam = sParam
		+ "file[" + tmpfile
		+ "]wm[" + wm
		+ "]";

	CGDTrace trace(LOG_L6, "NetWaterMark_impl:Set(%s)", sParam.c_str());

	int nRet = 0;

	try
	{
		nRet = CApp::Instance().WmDb().Set(tmpfile, wm.c_str());

		CThreadData::GetThreadSerial((long*)&call.nRecSerial);
	}
	catch (CExceptionError & ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "NetWaterMark_impl:Set(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("NetWaterMark_impl:Set(%s)", sParam.c_str());
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = -1;
	}

	return nRet;
}

int
CNetWaterMarkServerImpl::
Get(st_NetCallData &call,
	const string &file,
	string &wm,
	st_ExceptionError &ex)
{
	printf("Get\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("wmserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char tmpfile[GD_MAX_PATH] = { 0 };
	strcpy(tmpfile, file.c_str());
	char * p = tmpfile;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	string sParam;
	sParam = sParam
		+ "filePath[" + tmpfile
		+ "]";

	CGDTrace trace(LOG_L6, "NetWaterMark_impl:Get(%s)", sParam.c_str());

	int nRet = 0;
	try
	{
		//wm = CORBA::string_alloc(WMARK_LEN);

		char *tmp_Wm = new char[WMARK_LEN];
		nRet = CApp::Instance().WmDb().Get(tmpfile, tmp_Wm);
		wm.assign(tmp_Wm, WMARK_LEN);

		CThreadData::GetThreadSerial((long*)&call.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "NetWaterMark_impl:Get(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//CORBA::string_free(wm);
		//ex.AddErrText("NetWaterMark_impl:Get(%s)", sParam.c_str());
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = -1;
	}

	return nRet;
}

int
CNetWaterMarkServerImpl::
Add(st_NetCallData &call,
	const string &filePath,
	st_ExceptionError &ex)
{
	printf("Add\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("wmserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char tmppath[GD_MAX_PATH] = { 0 };
	strcpy(tmppath, filePath.c_str());
	char * p = tmppath;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	string sParam;
	sParam = sParam
		+ "filePath[" + tmppath
		+ "]";

	CGDTrace trace(LOG_L6, "NetWaterMark_impl:Add(%s)", sParam.c_str());

	int nRet = 0;

	try
	{
		nRet = CApp::Instance().WmDb().Add(tmppath);

		CThreadData::GetThreadSerial((long*)&call.nRecSerial);
	}
	catch (CExceptionError & ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "NetWaterMark_impl:Remove(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("NetWaterMark_impl:Remove(%s)", sParam.c_str());
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = -1;
	}

	return nRet;
}

int
CNetWaterMarkServerImpl::
Remove(st_NetCallData &call,
	const string &filePath,
	st_ExceptionError &ex)
{
	printf("Remove\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("wmserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char tmppath[GD_MAX_PATH] = { 0 };
	strcpy(tmppath, filePath.c_str());
	char * p = tmppath;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	string sParam;
	sParam = sParam
		+ "filePath[" + tmppath
		+ "]";

	CGDTrace trace(LOG_L6, "NetWaterMark_impl:Remove(%s)", sParam.c_str());

	int nRet = 0;
	try
	{
		nRet = CApp::Instance().WmDb().Remove(tmppath);

		CThreadData::GetThreadSerial((long*)&call.nRecSerial);
	}
	catch (CExceptionError & ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "NetWaterMark_impl:Remove(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("NetWaterMark_impl:Remove(%s)", sParam.c_str());
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = -1;
	}

	return nRet;
}

int
CNetWaterMarkServerImpl::
Rename(st_NetCallData &call,
	const string &oldfilename,
	const string &newfilename,
	st_ExceptionError &ex)
{
	printf("Rename\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("wmserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char tmp_O[GD_MAX_PATH] = { 0 };
	strcpy(tmp_O, oldfilename.c_str());
	char * p = tmp_O;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	char tmp_N[GD_MAX_PATH] = { 0 };
	strcpy(tmp_N, newfilename.c_str());
	p = tmp_N;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	string sParam;
	sParam = sParam
		+ "oldfilename[" + tmp_O
		+ "]newfilename[" + tmp_N
		+ "]";

	CGDTrace trace(LOG_L6, "NetWaterMark_impl:Rename(%s)", sParam.c_str());

	int nRet = 0;
	try
	{
		nRet = CApp::Instance().WmDb().Rename(tmp_O, tmp_N);

		CThreadData::GetThreadSerial((long*)&call.nRecSerial);
	}
	catch (CExceptionError & ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		string tmpErrMsg;
		tmpErrMsg = "NetWaterMark_impl:Rename(";
		tmpErrMsg += sParam;
		tmpErrMsg += ")";
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("NetWaterMark_impl:Rename(%s)", sParam.c_str());
		//InforGuard::ExceptionError e;
		//CNetTran::ConvertException(ex, e);
		//e._raise();
		nRet = -1;
	}

	return nRet;
}

int
CNetWaterMarkServerImpl::
Verify(st_NetCallData &call,
	const string &sFileName,
	const long &nFileSize,
	const string &sWm,
	const bool &bSimpleSync,
	st_ExceptionError &ex)
{
	printf("Verify\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("wmserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	CGDTrace trace(LOG_L6, "NetWaterMark_impl:Verify(%s,%d,%s)", sFileName.c_str(), nFileSize, sWm);

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char filePath[GD_MAX_PATH] = { 0 };
	strcpy(filePath, sFileName.c_str());
	char * p = filePath;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	int nRet = 0;
	// �ж���֤��Դ(nFileSizeΪ-1��ʾ���������󣬷����ʾͬ������)
	if (-1 == nFileSize)
	{
		// ��������֤����
		try
		{
			char sBakWm[WMARK_LEN] = { 0 };
			// �ж��ļ���Ŀ¼�Ƿ����

			if (!CFileOpt::IsExist(filePath))
			{
				// �ļ������ڣ������������һ���ļ������Ͳ�����(��ˮӡ)�������ļ����Ƿ�ɾ��(��ˮӡ)
				// �ж�����ˮӡ
				try
				{
					nRet = CApp::Instance().WmDb().Get(filePath, sBakWm);
				}
				catch (CExceptionError & ex)
				{
					ex.AddErrText("NetWaterMark_impl::Verify(%s,%d,%s)", sFileName.c_str(), nFileSize, sWm.c_str());
					// ��ˮӡʧ���ˣ��ǲ���Ҫ�׳��쳣
					trace.GDTrace(LOG_ERR, "������������֤�ļ�[%s]��ˮӡ�쳣\n%s",
						filePath, ex.GetErrText().c_str());
					// �Թ������׳��쳣����������ѽ
					return 403;
				}
				if (nRet == 0)
				{
					// ��ˮӡ�����ļ����Ƿ�ɾ��������ָ�
					//CResume::PutResumeTask( filePath );
					std::vector<RemotePath> remotePaths;
					CAppConfig::Instance().GetRemoteInfoByLocalFileName(filePath, remotePaths);

					if (remotePaths.size() > 0)
					{
						FileTranInfo info;
						info.sIp = remotePaths.at(0).ip;
						info.sPort = remotePaths.at(0).port;
						info.sTopPath = filePath;
						info.nHandleCount = 0;
						info.bIsPushFile = false;
						CApp::Instance().FileTranQueue().AddOneTaskIntoQue(info);
						// �Թ�������֤���󣬷���ʧ��
						return 403;
					}
					else
					{
						return 0;	// liu_yfeng ��ӣ���Ϊ������
					}
				}
				else if (nRet == -1)
				{
					// ��ˮӡ���ļ�����������
					// �Թ�������֤���󣬷�����֤�ɹ�
					return 0;
				}
				else
				{
					// ��ˮӡʧ����
					trace.GDTrace(LOG_ERR, "������������֤�ļ�[%s]��ˮӡʧ��[%d]",
						filePath, nRet);
					// �Թ������׳��쳣����������ѽ
					return 403;
				}
			}
			else
			{
				// �ļ�����
				// �ж��Ƿ񱻱������ļ�
				// liu_yfengɾ��GuardPolicy
				if (!CAppConfig::Instance().IsValidFile(filePath))
				{
					return 0;
				}
				/*
				CGuardPolicy policy;
				CFilePolicy::GetFilePolicy( POLICY_UPDATE, filePath, policy );
				if ( !policy.IsValidFile( filePath ) )
				{
				// �Ǳ������ļ�
				return 0;
				}
				*/
				else
				{
					// �������ļ�
					// ���ɵ�ǰˮӡ
					char sNewWm[WMARK_LEN] = { 0 };
					try
					{
						nRet = CWaterMarkDB::BuildWaterMark(filePath, sNewWm);
					}
					catch (CExceptionError & ex)
					{
						ex.AddErrText("NetWaterMark_impl::Verify(%s,%d,%s)", sFileName.c_str(), nFileSize, sWm.c_str());
						trace.GDTrace(LOG_ERR, "������������֤�ļ�[%s]����ˮӡ�쳣\n%s",
							filePath, ex.GetErrText().c_str());
						return 403;
					}
					if (nRet)
					{
						trace.GDTrace(LOG_ERR, "������������֤�ļ�[%s]����ˮӡʧ��[%d]", filePath, nRet);
						return 403;
					}

					// ȡ��ԭʼˮӡ
					try
					{
						nRet = CApp::Instance().WmDb().Get(filePath, sBakWm);
					}
					catch (CExceptionError & ex)
					{
						ex.AddErrText("NetWaterMark_impl::Verify(%s,%d,%s)", sFileName.c_str(), nFileSize, sWm.c_str());
						trace.GDTrace(LOG_ERR, "������������֤�ļ�[%s]��ˮӡ�쳣\n%s",
							filePath, ex.GetErrText().c_str());
						return 403;
					}

					// �Ƚϵ�ǰˮӡ��ԭʼˮӡ
					if (memcmp(sBakWm, sNewWm, WMARK_LEN) == 0)
					{
						// һ��
						return 0;
					}
					else
					{
						// ˮӡ��һ�£�����ָ�
						//CResume::PutResumeTask( filePath );

						std::vector<RemotePath> remotePaths;
						CAppConfig::Instance().GetRemoteInfoByLocalFileName(filePath, remotePaths);

						FileTranInfo info;
						info.sIp = remotePaths.at(0).ip;
						info.sPort = remotePaths.at(0).port;
						info.sTopPath = filePath;
						info.nHandleCount = 0;
						info.bIsPushFile = false;
						CApp::Instance().FileTranQueue().AddOneTaskIntoQue(info);
						// �Թ�������֤���󣬷���ʧ��
						return 403;
					}
				}
			}
		}
		catch (CExceptionError & ex)
		{
			CGDLog::WriteErrLog("1051:NetWaterMark_impl::Verify(%s,%d,%s)\n%s", sFileName.c_str(), nFileSize, sWm.c_str(), ex.GetErrText().c_str());

			ex.AddErrText("NetWaterMark_impl::Verify(%s,%d,%s)\n%s", sFileName.c_str(), nFileSize, sWm.c_str(), ex.GetErrText().c_str());
			trace.GDTrace(LOG_ERR, "������������֤�ļ�[%s]��ˮӡ�쳣\n%s",
				filePath, ex.GetErrText().c_str());
			return 500;
		}
	}
	else
	{
		// ͬ����֤����
		// ͬ�����ࣨ���ܣ���
		//		����ͬ����ֻ����������Է���һ�µ��ļ�
		//			�򵥣�ֻ�����������ҶԷ�û�е��ļ�
		//		��ȫͬ�����������������ļ�
		// ͬ�����ࣨҵ�񣩣�
		//		��������
		//		�������£�����ͬ����
		// �ж��ļ���Ŀ¼�Ƿ����

		try
		{
			if (!CFileOpt::IsExist(filePath))
			{
				// �ļ������ڣ���
				return 404;
			}
			else
			{
				// �ļ�����
				// �ж��Ƿ��ͬ��
				if (bSimpleSync)
				{
					// ��ͬ�����ļ����ڣ����贫��
					return 0;
				}
				else
				{
					// ��ȷͬ��
					// �ȱȽ��ļ���С(�����С����ͬ�򲻱رȽ�ˮӡ)
					if (CFileOpt::GetFileSize(filePath) != nFileSize)
					{
						// �����ļ�
						return 403;
					}

					// ��С��ͬ������֤ˮӡ
					char sNewWm[WMARK_LEN] = { 0 };

					try
					{
						nRet = CWaterMarkDB::BuildWaterMark(filePath, sNewWm);
					}
					catch (CExceptionError & ex1)
					{
						ex.nErrCode = ex1.m_nErrCode;
						ex.vErrText = ex1.m_vErrText;

						string tmpErrMsg;
						tmpErrMsg = "Get(";
						tmpErrMsg += filePath;
						tmpErrMsg += ")";
						ex.vErrText.push_back(tmpErrMsg);

						//ex.AddErrText("Get(%s)", filePath);
						// ת���쳣��ʽ
						//InforGuard::ExceptionError e;
						//e.nErrCode = ex.m_nErrCode;
						//int nCount = ex.m_vErrText.size();
						//e.vErrText.length(nCount);
						//for (int i = 0; i<nCount; i++)
						//{
						//	e.vErrText[i] = CORBA::string_dup(ex.m_vErrText[i].c_str());
						//}
						//e._raise();
						return -1;
					}
					if (nRet)
					{
						// Ҫô�ɹ���Ҫô�쳣
						//InforGuard::ExceptionError e;
						ex.nErrCode = 0x1000 + 0x404;
						//e.vErrText.length(1);
						char szTmp[512] = { 0 };
						sprintf(szTmp, "��ȷͬ��������֤�ļ�[%s]����ˮӡʧ��[%d]", filePath, nRet);
						//e.vErrText[0] = CORBA::string_dup(szTmp);
						ex.vErrText.push_back(szTmp);
						//e._raise();
						nRet = -1;
					}

					// �Ƚ�ˮӡ
					if (memcmp(sWm.c_str(), sNewWm, WMARK_LEN) == 0)
					{
						// ˮӡ����
						return 0;
					}
					else
					{
						// ˮӡ����
						// �����ļ�
						return 403;
					}
				}
			}
		}
		catch (CExceptionError & ex1)
		{
			CGDLog::WriteErrLog("1052:NetWaterMark_impl::Verify(%s,%d,%s)\n%s", sFileName.c_str(), nFileSize, sWm.c_str(), ex1.GetErrText().c_str());
			
			ex.nErrCode = ex1.m_nErrCode;
			ex.vErrText = ex1.m_vErrText;

			char tmpErrMsg[1024] = { 0 };
			sprintf(tmpErrMsg, "NetWaterMark_impl::Verify(%s,%d,%s)", sFileName.c_str(), nFileSize, sWm.c_str());
			ex.vErrText.push_back(tmpErrMsg);
			
			//ex.AddErrText("NetWaterMark_impl::Verify(%s,%d,%s)", sFileName, nFileSize, sWm);
			// ת���쳣��ʽ
			//InforGuard::ExceptionError e;
			//CNetTran::ConvertException(ex, e);
			//e._raise();
			return -1;
		}
	}

	return -1;
}

int
CNetWaterMarkServerImpl::
VerifyForFilter(const string &files, st_ExceptionError &ex)
{
	printf("VerifyForFilter\n");

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char filePath[GD_MAX_PATH] = { 0 };
	strcpy(filePath, files.c_str());
	char * p = filePath;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	int nResult = 0;
	/*
	CORBA::Long  nResult = VERIFYRESULT_SUCCESS;
	CORBA::Long  nRet = VERIFYRESULT_SUCCESS;

	string sFiles = files;
	string filePath;
	if (sFiles.length() <= 0)
	{
	return nResult;
	}

	string::size_type bi, ei;

	bi = sFiles.find_first_not_of("|");
	while (bi != string::npos)
	{
	ei = sFiles.find_first_of("|", bi);
	if (ei == string::npos)
	{
	ei = sFiles.length();
	}
	filePath = sFiles.substr(bi, ei - bi);

	nRet = VerifySingleFileForFilter(filePath.c_str());
	if (nRet)
	{
	nResult = nRet;
	gpLog->WriteInfo( ERR, "��������֤ʧ��[%d], �ļ�:%s", nResult, filePath.c_str());
	GDPrint("��������֤ʧ��[%d]: %s\r\n", nResult, filePath.c_str());
	}
	else
	{
	GDPrint("�������������: %s\r\n", filePath.c_str());
	}

	bi = sFiles.find_first_not_of("|", ei);
	}
	*/
	return nResult;
}

int
CNetWaterMarkServerImpl::
RequestResume(const string &filename, st_ExceptionError &ex)
{
	printf("RequestResume\n");

	//<< Ŀ¼ת��(�����վ�ֱ�ΪWindows�ͷ�Windows)
	char filePath[GD_MAX_PATH] = { 0 };
	strcpy(filePath, filename.c_str());
	char * p = filePath;
	while (p && *p)
	{
		if (*p == '\\' || *p == '/')
		{
			*p = C_PATHLASH;
		}
		p++;
	}
	//>>

	//���������͵�����ָ�
	//CResume::PutResumeTask( filePath );
	std::vector<RemotePath> remotePaths;
	CAppConfig::Instance().GetRemoteInfoByLocalFileName(filePath, remotePaths);

	FileTranInfo info;
	info.sIp = remotePaths.at(0).ip;
	info.sPort = remotePaths.at(0).port;
	info.sTopPath = filePath;
	info.nHandleCount = 0;
	info.bIsPushFile = false;
	CApp::Instance().FileTranQueue().AddOneTaskIntoQue(info);

	return 0;
}