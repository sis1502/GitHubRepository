#pragma once

#ifdef _WIN32
#	include <Windows.h>
#	include <io.h>
#else
#	include <unistd.h>
#	include <dirent.h>
#	include <pthread.h>
#	include <strings.h>
#	include <sys/prctl.h>
#endif

#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <mutex>

//** C++11标准时统相关
#include <chrono>

using namespace std;
using namespace chrono;

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
