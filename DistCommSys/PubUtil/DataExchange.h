#pragma once

#include "PubUtil/BaseDef.h"

namespace DistCommSysData_
{
	typedef struct _NetCallData
	{
		__int32 nThreadID;
		string sIp;
		__int32 sPort;
		__int32 nSerial;
		__int32 nSubSerial;
		__int32 nRecSerial;
		__int32 nIndent;
		_NetCallData()
		{
			this->nThreadID = 0;
			this->sIp = "";
			this->sPort = 0;
			this->nSerial = 0;
			this->nSubSerial = 0;
			this->nRecSerial = 0;
			this->nIndent = 0;
		}
		_NetCallData & operator=(const _NetCallData &right)
		{
			this->nThreadID = right.nThreadID;
			this->sIp = right.sIp;
			this->sPort = right.sPort;
			this->nSerial = right.nSerial;
			this->nSubSerial = right.nSubSerial;
			this->nRecSerial = right.nRecSerial;
			this->nIndent = right.nIndent;
			return *this;
		}
		void Display(void) const
		{
			cout << "*** = = = = = _NetCallData = = = = = ***" << endl;
			cout << "* * - - - - - nThreadID:" << this->nThreadID << endl;
			cout << "* * - - - - - sIp:" << this->sIp << endl;
			cout << "* * - - - - - sPort:" << this->sPort << endl;
			cout << "* * - - - - - nSerial:" << this->nSerial << endl;
			cout << "* * - - - - - nSubSerial:" << this->nSubSerial << endl;
			cout << "* * - - - - - nRecSerial:" << this->nRecSerial << endl;
			cout << "* * - - - - - nIndent:" << this->nIndent << endl;
			cout << "*** = = = = = _NetCallData = = = = = ***" << endl;
		}
	}st_NetCallData, *st_NetCallData_ptr;

	typedef struct _NetIpPort
	{
		string sIp;
		string sPort;
		_NetIpPort & operator=(const _NetIpPort &right)
		{
			this->sIp = right.sIp;
			this->sPort = right.sPort;
			return *this;
		}
		void Display(void)
		{
			cout << "*** = = = = = _NetIpPort = = = = = ***" << endl;
			cout << "* * - - - - - sIp:" << this->sIp << endl;
			cout << "* * - - - - - sPort:" << this->sPort << endl;
			cout << "*** = = = = = _NetIpPort = = = = = ***" << endl;
		}
	}st_NetIpPort, st_NetIpPort_ptr;
	typedef vector<st_NetIpPort> HostChain;

	typedef struct _ExceptionError
	{
		__int32 nErrCode;
		vector<string> vErrText;
		_ExceptionError & operator=(const _ExceptionError &right)
		{
			this->nErrCode = right.nErrCode;
			this->vErrText = right.vErrText;
		}
		void Display(void)
		{
			cout << "*** = = = = = _ExceptionError = = = = = ***" << endl;
			cout << "* * - - - - - nErrCode:" << this->nErrCode << endl;
			vector<string>::iterator it = this->vErrText.begin();
			short i = 0;
			while (it != this->vErrText.end())
			{
				cout << "* * - - - - - vErrText[" << i << "]:" << *it << endl;
				++i;
				++it;
			}
			cout << "*** = = = = = _ExceptionError = = = = = ***" << endl;
		}
	}st_ExceptionError, *st_ExceptionError_ptr;

	typedef struct _NetFileTreeNode
	{
		string name;
		__int32 size;
		__int32 time;
		bool isfolder;
		_NetFileTreeNode & operator=(const _NetFileTreeNode &right)
		{
			this->name = right.name;
			this->size = right.size;
			this->time = right.time;
			this->isfolder = right.isfolder;
			return *this;
		}
		void Display(void)
		{
			cout << "*** = = = = = _NetFileTreeNode = = = = = ***" << endl;
			cout << "* * - - - - - name:" << this->name << endl;
			cout << "* * - - - - - size:" << this->size << endl;
			cout << "* * - - - - - time:" << this->time << endl;
			cout << "* * - - - - - isfolder:" << (this->isfolder ? "true" : "false") << endl;
			cout << "*** = = = = = _NetFileTreeNode = = = = = ***" << endl;
		}
	}st_NetFileTreeNode, *st_NetFileTreeNode_ptr;
	typedef vector<st_NetFileTreeNode> NetFileTreeList;

	typedef struct _NetFileListNode
	{
		string name;
		__int32 size;
		__int32 time;
		bool isfolder;
		_NetFileListNode & operator=(const _NetFileListNode &right)
		{
			this->name = right.name;
			this->size = right.size;
			this->time = right.time;
			this->isfolder = right.isfolder;
			return *this;
		}
		void Display(void)
		{
			cout << "*** = = = = = _NetFileListNode = = = = = ***" << endl;
			cout << "* * - - - - - name:" << this->name << endl;
			cout << "* * - - - - - size:" << this->size << endl;
			cout << "* * - - - - - time:" << this->time << endl;
			cout << "* * - - - - - isfolder:" << (this->isfolder ? "true" : "false") << endl;
			cout << "*** = = = = = _NetFileListNode = = = = = ***" << endl;
		}
	}st_NetFileListNode, *st_NetFileListNode_ptr;
	typedef vector<st_NetFileListNode> NetFileList;

	typedef struct _FileNodeInfo
	{
		string name;
		bool isfile;
		__int32 mtime;
		__int32 type;
		_FileNodeInfo & operator=(const _FileNodeInfo &right)
		{
			this->name = right.name;
			this->isfile = right.isfile;
			this->mtime = right.mtime;
			this->type = right.type;
			return *this;
		}
		void Display(void)
		{
			cout << "*** = = = = = _FileNodeInfo = = = = = ***" << endl;
			cout << "* * - - - - - name:" << this->name << endl;
			cout << "* * - - - - - isfile:" << (this->isfile ? "true" : "false") << endl;
			cout << "* * - - - - - mtime:" << this->mtime << endl;
			cout << "* * - - - - - type:" << this->type << endl;
			cout << "*** = = = = = _FileNodeInfo = = = = = ***" << endl;
		}
	}st_FileNodeInfo, *st_FileNodeInfo_ptr;
	typedef struct _RemoteDirectory
	{
		string id;
		vector<st_FileNodeInfo> list;
		_RemoteDirectory & operator=(const _RemoteDirectory &right)
		{
			this->id = right.id;
			this->list = right.list;
		}
	}st_RemoteDirectory, *st_RemoteDirectory_ptr;
	typedef vector<st_RemoteDirectory> RemoteDirectoryList;

	typedef vector<string> ParamList;

	typedef struct _MsgBlock
	{
		__int32 mid;
		__int32 level;
		__int32 serial;
		string src;
		string dst;
		ParamList pl;
		_MsgBlock & operator=(const _MsgBlock &right)
		{
			this->mid = right.mid;
			this->level = right.level;
			this->serial = right.serial;
			this->src = right.src;
			this->dst = right.dst;
			this->pl = right.pl;
			return *this;
		}
	}st_MsgBlock, *st_MsgBlock_ptr;
};

#define __BADCHANNELEXCEPTION_STUFF__ \
		::InforGuard_::ExceptionError *ex = response->mutable_ex(); \
		ex->set_nerrcode(-1); \
		string *node = ex->add_verrtext(); \
		node->assign("CHANNEL INVALID");

#define __BADSTUBEXCEPTION_STUFF__ \
		::InforGuard_::ExceptionError *ex = response->mutable_ex(); \
		ex->set_nerrcode(status.error_code()); \
		string *node = ex->add_verrtext(); \
		node->assign("STUB INVALID:" + status.error_message());

#define __DATAEXCEPTION_TRANS__ \
		ex.nErrCode = response.ex().nerrcode(); \
		::google::protobuf::RepeatedPtrField<string> errors = response.ex().verrtext(); \
		for (auto error : errors) \
		{ \
			ex.vErrText.push_back(error); \
		}

#define __DATAEXCEPTION_SERVER_STUFF__ \
		InforGuard_::ExceptionError *ex_ = response->mutable_ex(); \
		ex_->set_nerrcode(ex.nErrCode); \
		vector<string>::iterator it = ex.vErrText.begin(); \
		while (it != ex.vErrText.end()) \
		{ \
			string *errtxt = ex_->add_verrtext(); \
			errtxt->assign(*it); \
			++it; \
		}

#ifdef _UNITTEST
#	define __IMPLEXCEPTION_CONVERT__ \
		return -1;
#else
#	define __IMPLEXCEPTION_CONVERT__ \
		CExceptionError ex_; \
		ex_.m_nErrCode = ex.nErrCode; \
		ex_.m_vErrText = ex.vErrText; \
		throw ex_;
#endif

#define __DATACOPY_NETCALLDATA_REQUEST__ \
		::InforGuard_::netCallData *req_call_ = request.mutable_call(); \
		req_call_->set_nthreadid(req_call.nThreadID); \
		req_call_->set_sip(req_call.sIp); \
		req_call_->set_sport(req_call.sPort); \
		req_call_->set_nserial(req_call.nSerial); \
		req_call_->set_nsubserial(req_call.nSubSerial); \
		req_call_->set_nrecserial(req_call.nRecSerial); \
		req_call_->set_nindent(req_call.nIndent);

#define __DATACOPY_NETCALLDATA_RESPONSE__ \
		res_call.nThreadID = response.call().nthreadid(); \
		res_call.sIp = response.call().sip(); \
		res_call.sPort = response.call().sport(); \
		res_call.nSerial = response.call().nserial(); \
		res_call.nSubSerial = response.call().nsubserial(); \
		res_call.nRecSerial = response.call().nrecserial(); \
		res_call.nIndent = response.call().nindent();

#define __DATACOPY_SERVER_NETCALLDATA_REQUEST__ \
		call.nThreadID = request->call().nthreadid(); \
		call.sIp = request->call().sip(); \
		call.sPort = request->call().sport(); \
		call.nSerial = request->call().nserial(); \
		call.nSubSerial = request->call().nsubserial(); \
		call.nRecSerial = request->call().nrecserial(); \
		call.nIndent = request->call().nindent();

#define __DATACOPY_SERVER_NETCALLDATA_RESPONSE__ \
		InforGuard_::netCallData *call_ = response->mutable_call(); \
		call_->set_nthreadid(call.nThreadID); \
		call_->set_sip(call.sIp); \
		call_->set_sport(call.sPort); \
		call_->set_nserial(call.nSerial); \
		call_->set_nsubserial(call.nSubSerial); \
		call_->set_nrecserial(call.nRecSerial); \
		call_->set_nindent(call.nIndent);

#define __DATACOPY_HOSTCHAIN_REQUEST__ \
		HostChain::const_iterator it_H = seqIpPort.begin(); \
		while (it_H != seqIpPort.end()) \
		{ \
			InforGuard_::netIpPort *node = request.add_seqipport(); \
			node->set_sip(it_H->sIp); \
			node->set_sport(it_H->sPort); \
			++it_H; \
		}

#define __DATACOPY_SERVER_HOSTCHAIN_REQUEST__ \
		::google::protobuf::RepeatedPtrField<::InforGuard_::netIpPort> nodes_IP = request->seqipport(); \
		for (auto node_IP : nodes_IP) \
		{ \
			st_NetIpPort tmp_IP; \
			tmp_IP.sIp = node_IP.sip(); \
			tmp_IP.sPort = node_IP.sport(); \
			seqIpPort.push_back(tmp_IP); \
		}
