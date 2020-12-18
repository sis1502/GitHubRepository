/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadWorking类定义
*
**==================== 版本说明 ====================*/

#include "ThreadWorking.h"

#include "ThreadRunJob.h"
#include "ThreadJobQueue.h"
#include "ThreadQueue.h"

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
***		- - - - 空闲线程实际操作对象首地址：p_I
***		- - - - 任务逻辑实际操作对象首地址：p_J
***		- - - - 原始任务队列实际操作对象首地址：p_O
***		- - - - 结果队列实际操作对象首地址：p_R
***		- - - - 线程标识号：id
***		- - - - 线程休眠间隔时间：interval
*
***		流程：
***		- - - - 1. 初始化赋值
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
CThreadWorking::
CThreadWorking(	CThreadQueue *p_I,
				CThreadRunJob *p_J,
				CThreadJobQueue *p_O,
				CThreadJobQueue *p_R,
				const string &name,
				const unsigned int &id,
				const unsigned int &interval)
{
	m_Idles = p_I;
	m_RunJob = p_J;
	m_OrigJobs = p_O;
	m_ResultJobs = p_R;
	m_Name = name;
	m_Id = id;
	m_Interval = interval;
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
CThreadWorking::
~CThreadWorking()
{
	//...
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
***		- - - - 1. 检测必要成员变量
***		- - - - 2. 首发进入空闲等待状态
***		- - - - 3. 执行任务逻辑
***		- - - - 4. 视具体情况进行空闲线程管理
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThreadWorking::
Run()
{
	/*
	***		不允许工作线程托管类的实例化对象为空
	*/
	if (!m_RunJob)
	{
		return ;
	}
	
	/*
	***		首发无限期等待
	*/
	if (m_Idles)
	{
		//printf("[CThreadWorking::Run]%s:%d FIRST_RUN to WAIT\n", m_Name.c_str(), m_Id);
		m_Idles->Set(m_Id);
	}
	this->Wait();
	
	while (true)
	{
		/*
		***		线程已被停止
		*/
		if (m_Stop)
		{
#		ifdef _DEBUG
			printf("[CThreadWorking::Run]%s:%d STOP\n", m_Name.c_str(), m_Id);
#		endif
			break;
		}
		/*
		***		线程已被暂停
		*/
		if (m_Pause)
		{
#		ifdef _DEBUG
			printf("[CThreadWorking::Run]%s:%d PAUSE\n", m_Name.c_str(), m_Id);
#		endif
			if (m_Idles)
			{
				m_Idles->Set(m_Id);
			}
			this->Wait();
			//** 唤醒后不应直接执行任务
			continue;
		}

		if (!m_RunJob->Run(m_OrigJobs, m_ResultJobs))
		{
			//** 自我唤醒的线程不应进入空闲线程队列
			//** 一般情况下，当m_Interval不为0时，不应设置m_Idles（即：自启动线程不应使用空闲队列管理机制）
			if (m_Idles && (m_Interval == 0))
			{
#			ifdef _DEBUG
				printf("[CThreadWorking::Run]%s:%d FALSE to WAIT [interval:%d]\n", m_Name.c_str(), m_Id, m_Interval);
#			endif
				m_Idles->Set(m_Id);
			}
			this->Wait(m_Interval);
		}
	}
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		设置线程休眠间隔时间
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 线程休眠间隔时间：interval
*
***		流程：
***		- - - - 1. 对类中的线程休眠间隔时间赋值
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
void 
CThreadWorking::
setInterval(const int &interval)
{
	m_Interval = interval;
}
