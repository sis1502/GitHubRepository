/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadPool类定义
*
**==================== 版本说明 ====================*/

#include "ThreadPool.h"

#include "ThreadWorking.h"
#include "ThreadRunJob.h"
#include "ThreadJobQueue.h"
#include "ThreadQueue.h"

#ifndef _UNIT_TEST
#	include "GDLog/GDLog.h"
#endif

using namespace Sis_;

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		唯一构造函数
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 任务逻辑实际操作对象首地址：p_J
***		- - - - 原始任务队列实际操作对象首地址：p_O
***		- - - - 结果队列实际操作对象首地址：p_R
***		- - - - 最大线程数：max
***		- - - - 最大同时运行线程数：cur
*
***		流程：
***		- - - - 1. 初始化赋值
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
CThreadPool::
CThreadPool(	CThreadRunJob *p_J,
				CThreadJobQueue *p_O,
				CThreadJobQueue *p_R,
				const string &name,
				const unsigned int &id,
				const int &max,
				const int &cur)
{
	m_j_Working = p_J;
	m_OrigJobs = p_O;
	m_ResultJobs = p_R;
	m_Name = name;
	m_Id = id;
	m_Init = false;
	if (cur <= 0)
	{
		m_Cur = 3;
		m_Max = 5;
	}
	else if (cur > max)
	{
		m_Cur = cur;
		m_Max = cur;
	}
	else
	{
		m_Cur = cur;
		m_Max = max;
	}
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
***		流程：
***		- - - - 1. 清理堆上的空间
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
CThreadPool::
~CThreadPool()
{
	if (m_Idles)
	{
		delete m_Idles;
		m_Idles = NULL;
	}
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		执行逻辑
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 初始化检测
***		- - - - 2. 等待直至收到停止信号
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThreadPool::
Run()
{
	if (!m_Init)
	{
		printf("[CThreadPool/Run]NOT Init\n");
		return ;
	}
	
	this->Wait();
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		初始化
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 检测各项应用程序唯一性对象
***		- - - - 2. 创建空闲线程管理对象
***		- - - - 3. 创创建并启动挂起状态的工作线程
***		- - - - 4. 告知初始化标识
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThreadPool::
Init()
{
	if (!m_j_Working)
	{
		printf("[CThreadPool/Init]工作执行逻辑控制对象（m_j_Working）不存在\n");
		return false;
	}
	
	/*
	***		创建空闲线程队列控制对象
	*/
	try
	{
		m_Idles = new CThreadQueue();
	}
	catch (const bad_alloc &ex)
	{
#	ifndef _UNIT_TEST
		CGDLog::WriteErrLog("[CThreadPool/Init]创建空闲线程队列控制对象（m_Idles）失败，可能是内存不足");
#	else
#		ifdef _CONSOLE
			printf("[CThreadPool/Init]创建空闲线程队列控制对象（m_Idles）失败，可能是内存不足\n");
#		endif
#	endif
		
		return false;
	}
	catch (const exception &ex)
	{
#	ifndef _UNIT_TEST
		CGDLog::WriteErrLog("[CThreadPool/Init]创建空闲线程队列控制对象（m_Idles）失败，可能是内存不足");
#	else
#		ifdef _CONSOLE
		printf("[CThreadPool/Init]创建空闲线程队列控制对象（m_Idles）失败，失败原因：%s\n", ex.what());
#		endif
#	endif

		return false;
	}
	catch (...)
	{
		return false;
	}
	
	for (int i = 0; i < m_Cur; i++)
	{
		CThreadWorking *p_W;
		try
		{
			p_W = new CThreadWorking(m_Idles, m_j_Working, m_OrigJobs, m_ResultJobs, m_Name + "_Working", m_Id + i + 1, 0);
		}
		catch(const bad_alloc &ex)
		{
#		ifndef _UNIT_TEST
			CGDLog::WriteErrLog("[CThreadPool/Init]创建工作线程（m_t_Working）失败，可能是内存不足");
#		else
#			ifdef _CONSOLE
				printf("[CThreadPool/Init]创建工作线程（m_t_Working）失败，可能是内存不足\n");
#			endif
#		endif
			return false;
		}
		p_W->Start();
		m_t_Working[m_Id + i + 1] = p_W;
	}

	return (m_Init = true);
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		停止线程池
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：无
*
***		流程：
***		- - - - 1. 置线程状态为正在停止
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThreadPool::
StopWorking(const bool &all)
{
	map<int, CThreadWorking*>::iterator it = m_t_Working.begin();
	while (it != m_t_Working.end())
	{
		it->second->Stop();
		it->second = NULL;
		++ it;
	}
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		激活工作线程
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 激活量标识：all
*
***		流程：
***		- - - - 1. 初始化检测
***		- - - - 2. 从空闲线程队列中取出线程并激活
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThreadPool::
NotifyWorking(const bool &all)
{
	if (!m_Init)
	{
		printf("[CThreadPool/NotifyWorking]NOT Init\n");
		return ;
	}
	
	int id;
	while (m_Idles->Get(id))
	{
		m_t_Working[id]->Notify();
		if (!all)
		{
			break;
		}
	}
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		暂停工作线程
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 暂停量标识：all
*
***		流程：
***		- - - - 1. 初始化检测
***		- - - - 2. 从空闲线程队列中取出线程并激活
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThreadPool::
PauseWorking(const bool &all)
{
	if (!m_Init)
	{
		printf("[CThreadPool/PauseWorking]NOT Init\n");
		return;
	}

	map<int, CThreadWorking*>::iterator it = m_t_Working.begin();
	while (it != m_t_Working.end())
	{
		it->second->Pause();
		++it;
	}
}

void 
CThreadPool::
ResumeWorking(const bool &all)
{
	if (!m_Init)
	{
		printf("[CThreadPool/ResumeWorking]NOT Init\n");
		return;
	}

	map<int, CThreadWorking*>::iterator it = m_t_Working.begin();
	while (it != m_t_Working.end())
	{
		it->second->Resume();
		++it;
	}
}

/*
***		测试用
*/
const unsigned int  
CThreadPool::
GetWorkingMapSize() const
{
	return m_t_Working.size();
}

/*
***		测试用
*/
void 
CThreadPool::
DisplayWorkingAddr()
{
	printf("size:%d\n", m_t_Working.size());
	map<int, CThreadWorking*>::iterator it = m_t_Working.begin();
	while (it != m_t_Working.end())
	{
		printf("%d, %p\n", it->first, it->second);
		++ it;
	}
}
