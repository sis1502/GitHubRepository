/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：预编译集合
*
**==================== 版本说明 ====================*/

#pragma once

#ifdef _WIN32
#	include <Windows.h>
#else
#	include <unistd.h>
#	include <sys/time.h>
#	include <iconv.h>
#endif

#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <mutex>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef SLEEP
#	ifdef WIN32
#		define SLEEP(sec) Sleep(sec*1000)
#	else
#		define SLEEP(sec) sleep(sec)
#	endif
#endif
