#pragma once

#ifdef _WIN32
#	include <WS2tcpip.h>
#	include <Windows.h>
#	include <io.h>
#else
#	include <unistd.h>
#	include <dirent.h>
#	include <pthread.h>
#	include <strings.h>
#	include <sys/prctl.h>
#	include <arpa/inet.h>
#endif

#include <stdio.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <mutex>

//** C++11标准时统相关
#include <chrono>

using namespace std;
using namespace chrono;

#ifdef WIN32
#	pragma comment(lib, "ws2_32.lib")
#else

#endif

#define SUCCESS 0
#define FAIL -1
#define EXIST 1
#define NOTEXIST -2

#ifdef _WIN32
#	define SLEEP(sec) Sleep(sec*1000)
#else
#	define SLEEP(sec) sleep(sec)
#endif

#ifdef GetMessage
#	undef GetMessage
#endif

#ifndef _WIN32
#	define __int32 int
#	define __int64 long long
#endif

//** 服务端密钥
static const char *serverkey_path = "server_privatekey.pem";
//** 服务端自签名证书
static const char *servercert_path = "server_self_signed_crt.pem";
//** 客户端密钥
static const char *clientkey_path = "client_privatekey.pem";
//** 客户端自签名证书
static const char *clientcert_path = "client_self_signed_crt.pem";