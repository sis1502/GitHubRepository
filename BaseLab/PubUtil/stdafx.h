/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2020-10-19
*
***		���ݣ�Ԥ���뼯��
*
**==================== �汾˵�� ====================*/

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
