/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：线程专属基础数据结构定义
*
**==================== 版本说明 ====================*/

#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#endif

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <queue>
#include <string>

//** C++11标准线程相关
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

#ifdef WIN32
#	define SLEEP(sec) Sleep(sec*1000)
#else
#	define SLEEP(sec) sleep(sec)
#endif

namespace Sis_ {

#	define SUCCESS 0
#	define FAIL -1
#	define EXIST 1
#	define NOTEXIST -2

	static const char *VERSION = "v0.0.0.5";

	/*- - - - - - - - - - - - - - - - - - - - 枚举定义 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：线程状态
	*
	***		枚举量：
	***		- - - - 正在运行：RUNNING
	***		- - - - 正在停止：STOPPING
	***		- - - - 已经停止：STOPPED
	***		- - - - 等待：WAITING
	***		- - - - 就绪：READY
	***		- - - - 挂起：SUSPEND
	*
	**- - - - - - - - - - - - - - - - - - - - 枚举定义 - - - - - - - - - - - - - - - - - - - -*/
	typedef enum _ThreadState
	{
		RUNNING = 0,
		STOPPING,
		STOPPED,
		WAITING,
		READY,
		SUSPEND
	}em_ThreadState;

};
