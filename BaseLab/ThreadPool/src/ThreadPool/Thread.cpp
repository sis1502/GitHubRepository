/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThread类定义
*
**==================== 版本说明 ====================*/

#include "Thread.h"

using namespace Sis_;

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		唯一构造函数
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 初始化停止标识和暂停标识
***		- - - - 2. 初始化同步控制标识
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
CThread::
CThread()
{
	m_Stop = false;
	m_Pause = false;
	m_CondLocked = false;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		析构函数
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：无
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
CThread::
~CThread()
{
	//...
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程创建
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 创建线程
***		- - - - 2. 与主线程分离，线程结束后独占资源自动回收
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThread::
Start()
{
	try
	{
		thread t(CThread::ThreadProc, this);
		t.detach();
	}
	catch (const system_error &ex)
	{
#ifdef _DEBUG
		printf("[CThread::Start]system_error_code:%d\n", ex.code().value());
#endif
		return false;
	}

	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程停止
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 置停止状态
***		- - - - 2. 检查线程是否休眠，若休眠则唤醒，使其自然结束
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThread::
Stop()
{
	m_Stop = true;
	if (m_CondLocked)
	{
		/*
		***	停止一个处于休眠状态的线程时
		*/
		this->Notify();
	}
	
	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程恢复
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 检查暂停标识
***		- - - - 2. 置暂停标识为假
***		- - - - 3. 检查线程是否休眠，若休眠则唤醒
*
***		说明：
***		- - - - 1. 应当注意，唤醒线程的先决条件：已暂停和已休眠必须同时达成。
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThread::
Resume()
{
	if (m_Pause)
	{
		m_Pause = false;
		if (m_CondLocked)
		{
			this->Notify();
		}
	}

	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程暂停
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 置暂停标识为真，不阻断线程运行，使其自然暂停
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThread::
Pause()
{
	m_Pause = true;

	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程等待
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 等待时间：sec
*
***		流程：
***		- - - - 1. 检测同步锁指示器状态
***		- - - - 2. 释放线程锁，锁定同步锁，进入等待状态，直至信号激发
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThread::
Wait(const unsigned int &sec)
{
	try
	{
		unique_lock <mutex> lock(m_Mutex);

		if (!m_CondLocked)
		{
#		ifdef _DEBUG
			printf("[CThread::Wait]%s:%d Waiting[%ds] Begin\n", m_Name.c_str(), m_Id, sec);
#		endif
			m_CondLocked = true;
			if (sec == 0)
			{
				m_Cond.wait(lock);
			}
			else
			{
				cv_status status = m_Cond.wait_until(lock, chrono::steady_clock::now()+chrono::seconds(sec));
#			ifdef _DEBUG
				if (status == cv_status::timeout)
				{
					printf("[CThread::Wait]%s:%d Waiting[%ds] Timeout\n", m_Name.c_str(), m_Id, sec);
				}
#			endif
			}
#		ifdef _DEBUG
			printf("[CThread::Wait]%s:%d Waiting[%ds] End\n", m_Name.c_str(), m_Id, sec);
#		endif		
			m_CondLocked = false;
		}
	}
	catch (const system_error &ex)
	{
#	ifdef _DEBUG
		printf("[CThread::Wait]system_error_code:%d\n", ex.code().value());
#	endif
		return false;
	}

	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程激活
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 检测是否处于暂停状态，尚未恢复的线程不允许激活
***		- - - - 2. 设置同步锁指示器，激活线程
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThread::
Notify()
{
	try
	{
		unique_lock <mutex> lock(m_Mutex);

		if (m_Pause)
		{
#		ifdef _DEBUG
			printf("[CThread::Notify]%s:%d PAUSED\n", m_Name.c_str(), m_Id);
#		endif
			return false;
		}

		if (m_CondLocked)
		{
			m_CondLocked = false;
			m_Cond.notify_one();
		}
	}
	catch (const system_error &ex)
	{
#	ifdef _DEBUG
		printf("[CThread::Wait]system_error_code:%d\n", ex.code().value());
#	endif
		return false;
	}

	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程操作函数
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 线程虚基类实现对象首地址：para
*
***		流程：
***		- - - - 1. 转换参数类型
***		- - - - 2. 执行实现对象的Run方法
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThread::
ThreadProc(void *para)
{
	CThread *p = (CThread*)para;
	p->Run();

	return ;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		线程清理函数
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 线程虚基类实现对象首地址：para
*
***		流程：无
*
***		说明：
***		- - - - 1. 老旧版本设计，已弃用
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThread::
ThreadClean(void *para)
{
	//...
}