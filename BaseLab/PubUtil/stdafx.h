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

#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <iconv.h>
#include <string.h>

#include <string>
#include <map>
#include <queue>
#include <mutex>

using namespace std;

#ifndef SLEEP
#	ifdef WIN32
#		define SLEEP(sec) Sleep(sec*1000)
#	else
#		define SLEEP(sec) sleep(sec)
#	endif
#endif
