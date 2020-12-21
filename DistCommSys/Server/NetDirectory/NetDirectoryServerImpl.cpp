#include "Server/NetDirectory/NetDirectoryServerImpl.h"

#include "DCSManager.h"

#include "Base/App.h"
#include "Base/FileListEx.h"
#include "Base/Tool.h"
#include "Base/Toolbox.h"
//#include "Base/NetTran.h"
#include "Common/GDString.h"
#include "FileOpt/FileOpt.h"
#include "GDLog/ThreadData.h"
#include "GDLog/GDTrace.h"
//#include "NetDirectory/NetDirectory_impl.h"

CNetDirectoryServerImpl::CNetDirectoryServerImpl()
{
	//...
}


CNetDirectoryServerImpl::~CNetDirectoryServerImpl()
{
	//...
}

int
CNetDirectoryServerImpl::
Check(st_ExceptionError &ex)
{
	printf("Check\n");

	return 0;
}

int
CNetDirectoryServerImpl::
GetTree(st_NetCallData &call,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileTreeList &treenode,
	st_ExceptionError &ex)
{
	printf("GetTree\n");

	assert(0);

	return 0;
}

int
CNetDirectoryServerImpl::
GetList(st_NetCallData &call,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist,
	st_ExceptionError &ex)
{
	printf("GetList\n");

	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("dirserver", true);
	CThreadData::SetThreadSerial(call.nSerial, call.nSubSerial, call.nRecSerial);

	string sParam;
	sParam = sParam + "seqIpPort[" + CTool::HostChain2String(seqIpPort) + "]remotefoldername[" + remotefoldername + "]mode[" + CGDString::ltoa(mode) + "]";

	CGDTrace trace(LOG_L6, "NetDirectory_impl:GetList(%s)", sParam.c_str());

	int nRet = 0;
	try
	{
		// 判断是否符号链接
		char sRealPath[GD_MAX_PATH] = { 0 };
		if (CFileOpt::IsLink(remotefoldername.c_str(), sRealPath))
		{
			// 符号链接，特殊同处理
			string sDstFileReal = sRealPath;
			string sDstFileLink = remotefoldername;
			// by wang_jin at 2009-02-28
			sDstFileReal += "|";
			sDstFileReal += sDstFileLink;

			DistCommSysData_::st_NetFileListNode curnode;
			curnode.name = sDstFileReal;
			curnode.size = 0;
			curnode.time = 0;
			curnode.isfolder = false;
			filelist.push_back(curnode);

			//filelist = new NetFileList;
			//filelist->length(1);

			//NetFileListNode curnode;
			//curnode.name = CORBA::string_dup(sDstFileReal.c_str());
			//curnode.size = 0;
			//curnode.time = 0;
			//curnode.isfolder = false;

			//filelist[0] = curnode;
			trace.GDTrace(LOG_NOT, "GetList() return [50505] [%s]", sDstFileReal.c_str());

			return trace.SetRetValue(0); // 返回符号链接信息
		}

		nRet = GetFileList(call, seqIpPort, remotefoldername, mode, filelist, ex);

		CThreadData::GetThreadSerial((long *)&call.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		char tmpErrMsg[1024] = {0};
		sprintf("NetDirectory_impl:GetList(%s,%x)", remotefoldername.c_str(), mode);
		ex.vErrText.push_back(tmpErrMsg);

		//ex.AddErrText("NetDirectory_impl:GetList(%s,%x)", remotefoldername, mode);
		// 转换异常格式
		//InforGuard::ExceptionError e; 
		//CNetTran::ConvertException(ex, e);
		//e._raise();
	}

	return nRet;
}

int
CNetDirectoryServerImpl::
GetTreeEx(const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileTreeList &treenode,
	st_ExceptionError &ex)
{
	printf("GetTreeEx\n");

	DistCommSysData_::st_NetCallData callData;
	callData.nIndent = 0;
	callData.nRecSerial = 0;
	callData.nSerial = 0;
	callData.nSubSerial = 0;
	callData.nThreadID = 0;
	callData.sIp = "";
	callData.sPort = 0;

	return GetTree(callData, seqIpPort, remotefoldername, mode, treenode, ex);
}

int
CNetDirectoryServerImpl::
GetListEx(const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist,
	st_ExceptionError &ex)
{
	printf("GetListEx\n");

	DistCommSysData_::st_NetCallData callData;
	callData.nIndent = 0;
	callData.nRecSerial = 0;
	callData.nSerial = 0;
	callData.nSubSerial = 0;
	callData.nThreadID = 0;
	callData.sIp = "";
	callData.sPort = 0;

	return GetFileList(callData, seqIpPort, remotefoldername, mode, filelist, ex, true);
}

int 
CNetDirectoryServerImpl::
GetFileList(st_NetCallData &callData,
	const HostChain &seqIpPort,
	const string &remotefoldername,
	const long &mode,
	NetFileList &filelist,
	st_ExceptionError &ex,
	bool bSort)
{
	CThreadData threadData;
	CThreadData::SetCurrentThreadLogFile("dirserver", true);
	CThreadData::SetThreadSerial(callData.nSerial, callData.nSubSerial, callData.nRecSerial);

	string sParam;
	sParam = sParam + "seqIpPort[" + CTool::HostChain2String(seqIpPort) + "]remotefoldername[" + remotefoldername + "]mode[" + CGDString::ltoa(mode) + "]";

	CGDTrace trace(LOG_L6, "NetDirectory_impl:GetFileList(%s)", sParam.c_str());

	string sToIp;
	string sToPort;
	int nRet = 0;
	FileList orifilelist;
	string sTmpTopFile = remotefoldername;
	CGDString::MakeSureLocalPath(sTmpTopFile);

	try
	{
		// 检测转发
		if (CTool::IsTransmit(seqIpPort, sToIp, sToPort))
		{
			//NetDirectory_var ref;
			//CNetTran::GetNetDirectoryObject(sToIp.c_str(), sToPort.c_str(), ref);
			DistCommSysData_::st_NetCallData call;
			//InforGuard::netCallData callData;
			CTool::InitNetCallData(call);
			nRet = CApp::Instance().GetDCSManager().GetClient().GetNetDirectory().GetList(sToIp, sToPort, call, seqIpPort, remotefoldername, mode, filelist);
			//nRet = ref->GetList(callData, seqIpPort, remotefoldername, mode, filelist);
			CThreadData::SetThreadSerial(call.nRecSerial);
			return nRet;
		}

		nRet = CFileListEx().CreateListEx(sTmpTopFile.c_str(), orifilelist, CFileListEx::NO_POLICY, mode, bSort);

		CThreadData::GetThreadSerial((long *)&callData.nRecSerial);
	}
	catch (CExceptionError &ex1)
	{
		ex.nErrCode = ex1.m_nErrCode;
		ex.vErrText = ex1.m_vErrText;

		char tmpErrMsg[1024] = { 0 };
		sprintf("NetDirectory_impl:GetFileList(%s,%x)", remotefoldername.c_str(), mode);
		ex.vErrText.push_back(tmpErrMsg);

		//ei.AddErrText("NetDirectory_impl:GetFileList(%s,%x)", remotefoldername.c_str(), mode);
		// 转换异常格式
		//InforGuard::ExceptionError ex;
		//CNetTran::ConvertException(ei, ex);
		//ex._raise();
		nRet = -1;
	}
/*	catch (const InforGuard::ExceptionError &ei)
	{
		ei._raise();
	}
	catch (const CORBA::Exception &ei)
	{
		CExceptionError ex;
		CNetTran::ConvertException(ei, ex);
		ex.AddErrText("NetDirectory_impl:GetFileList(%s,%x)", remotefoldername, mode);
		// 抛出异常
		InforGuard::ExceptionError eo;
		CNetTran::ConvertException(ex, eo);
		eo._raise();
	}*/

	filelist.clear();
	if (nRet == 0)
	{
		long nCount = orifilelist.size();
		//filelist->length(nCount);

		//转换为sequence存储的列表
		FileList::iterator iter;
		int i = 0;
		for (iter = orifilelist.begin(); iter != orifilelist.end(); ++iter, i++)
		{
			//string name = (*iter).name;
			//long size = (*iter).size;
			//long time = (*iter).time;
			//bool bFolder = (*iter).isfolder;

			//NetFileListNode curnode;
			//curnode.name = CORBA::string_dup(name.c_str());
			//curnode.size = size;
			//curnode.time = time;
			//curnode.isfolder = bFolder;

			st_NetFileListNode curnode;
			curnode.name = (*iter).name;
			curnode.size = (*iter).size;
			curnode.time = (*iter).time;
			curnode.isfolder = (*iter).isfolder;

			filelist.push_back(curnode);
		}
	}

	return nRet;
}