#include "Server/GRPCServer.h"

#include "Server/FileTran/FileTranServerCarry.h"
#include "Server/FileTran/FileTranServerData.h"
#include "Server/FileTran/FileTranServerImpl.h"

#include "Server/MsgTran/MsgTranServerCarry.h"
#include "Server/MsgTran/MsgTranServerData.h"
#include "Server/MsgTran/MsgTranServerImpl.h"

#include "Server/NetConfig/NetConfigServerCarry.h"
#include "Server/NetConfig/NetConfigServerData.h"
#include "Server/NetConfig/NetConfigServerImpl.h"

#include "Server/NetDirectory/NetDirectoryServerCarry.h"
#include "Server/NetDirectory/NetDirectoryServerData.h"
#include "Server/NetDirectory/NetDirectoryServerImpl.h"

#include "Server/NetWaterMark/NetWaterMarkServerCarry.h"
#include "Server/NetWaterMark/NetWaterMarkServerData.h"
#include "Server/NetWaterMark/NetWaterMarkServerImpl.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

CGRPCServer::
CGRPCServer(const string &ip,
	const unsigned int &port,
	const string &certClient,
	const string &certServer,
	const string &keyServer)
{
	m_Conn = string("[::]:") + to_string(port);
	//m_Conn = ip + string(":") + to_string(port);
	m_ClientCert = certClient;
	m_ServerCert = certServer;
	m_ServerKey = keyServer;
}


CGRPCServer::
~CGRPCServer()
{
	//...
}

bool 
CGRPCServer::
Run()
{
	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();

	grpc::ServerBuilder builder;

	grpc::SslServerCredentialsOptions ssl_opts(GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY);
	//** 客户端根证书
	ssl_opts.pem_root_certs = m_ClientCert;
	//** 服务端私钥和服务端证书
	ssl_opts.pem_key_cert_pairs.push_back(grpc::SslServerCredentialsOptions::PemKeyCertPair{m_ServerKey, m_ServerCert});

	builder.AddListeningPort(m_Conn, grpc::SslServerCredentials(ssl_opts));
	//builder.AddListeningPort(m_Conn, grpc::InsecureServerCredentials());

	builder.RegisterService(m_FileTranCarry);
	builder.RegisterService(m_MsgTranCarry);
	builder.RegisterService(m_NetConfigCarry);
	builder.RegisterService(m_NetDirectoryCarry);
	builder.RegisterService(m_NetWaterMarkCarry);

	std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());

	if (server != nullptr)
	{
		printf("对（%s）监听成功\n", m_Conn.c_str());
	}
	else
	{
		printf("对（%s）监听失败\n", m_Conn.c_str());
		return false;
	}

	server->Wait();

	return true;
}

bool 
CGRPCServer::
Init()
{
	//** FileTran接口
	m_FileTranImpl = new CFileTranServerImpl();
	m_FileTranData = new CFileTranServerData(m_FileTranImpl);
	m_FileTranCarry = new CFileTranServerCarry(m_FileTranData);

	//** MsgTran接口
	m_MsgTranImpl = new CMsgTranServerImpl();
	m_MsgTranData = new CMsgTranServerData(m_MsgTranImpl);
	m_MsgTranCarry = new CMsgTranServerCarry(m_MsgTranData);

	//** NetConfig接口
	m_NetConfigImpl = new CNetConfigServerImpl();
	m_NetConfigData = new CNetConfigServerData(m_NetConfigImpl);
	m_NetConfigCarry = new CNetConfigServerCarry(m_NetConfigData);

	//** NetDirectory接口
	m_NetDirectoryImpl = new CNetDirectoryServerImpl();
	m_NetDirectoryData = new CNetDirectoryServerData(m_NetDirectoryImpl);
	m_NetDirectoryCarry = new CNetDirectoryServerCarry(m_NetDirectoryData);

	//** NetDirectory接口
	m_NetWaterMarkImpl = new CNetWaterMarkServerImpl();
	m_NetWaterMarkData = new CNetWaterMarkServerData(m_NetWaterMarkImpl);
	m_NetWaterMarkCarry = new CNetWaterMarkServerCarry(m_NetWaterMarkData);

	return true;
}