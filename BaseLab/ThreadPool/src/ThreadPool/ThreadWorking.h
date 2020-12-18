/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadWorking类声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "Thread.h"

namespace Sis_ {

	class CThreadRunJob;
	class CThreadJobQueue;
	class CThreadQueue;

	/*- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：线程工作类
	*
	***		目的：线程操作共性封装
	*
	***		作者：Sis
	*
	***		建立时间：2020-10-19
	*
	***		算法概述：
	***		- - - - 1. 作为线程执行的逻辑对象存在，需要提供执行工作的实例对象
	***		- - - - 2. 目前，设计为仅在作为流水线工作线程组时需要向线程池告知空闲状态
	*
	***		成员变量：
	***		- - - - 空闲线程操作对象：m_Idles
	***		- - - - 线程执行逻辑托管类：m_RunJob
	***		- - - - 原始任务队列：m_OrigJobs
	***		- - - - 结果任务队列：m_ResultJobs
	***		- - - - 线程休眠自启间隔时间：m_Interval
	*
	**- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -*/
	class CThreadWorking final: public CThread
	{
	public:
		explicit CThreadWorking(CThreadQueue *p_I, 
								CThreadRunJob *p_J,
								CThreadJobQueue *p_O,
								CThreadJobQueue *p_R,
								const string &name,
								const unsigned int &id,
								const unsigned int &interval);
		~CThreadWorking();
	
	public:
		virtual void Run();

	public:
		void setInterval(const int &interval);
	
	private:
		CThreadQueue *m_Idles;
		CThreadRunJob *m_RunJob;
		CThreadJobQueue *m_OrigJobs;
		CThreadJobQueue *m_ResultJobs;

	private:
		unsigned int m_Interval;
	};

};