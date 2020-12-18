/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadPool类声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "Thread.h"

namespace Sis_ {

	class CThreadWorking;
	class CThreadRunJob;
	class CThreadJobQueue;
	class CThreadQueue;

	/*- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：线程池
	*
	***		目的：实现线程池处理逻辑
	*
	***		作者：Sis
	*
	***		建立时间：2020-09-07
	*
	***		算法概述：
	***		- - - - 1. 初始化空闲线程队列
	***		- - - - 2. 对任务队列、结果队列、工作线程执行逻辑控制对象判空
	***		- - - - 3. 初始化工作线程组
	***		- - - - 4. 根据初始化标识判定是否允许调用功能性方法
	*
	***		成员变量：
	***		- - - - （私有）工作线程组：m_t_Working
	***		- - - - （私有）工作线程执行逻辑控制对象：m_j_Working
	***		- - - - （私有）任务队列：m_OrigJobs
	***		- - - - （私有）结果队列：m_ResultJobs
	***		- - - - （私有）空闲线程队列：m_Idles
	***		- - - - （私有）初始化标识：m_Init
	***		- - - - （私有）最大工作线程数：m_Max
	***		- - - - （私有）当前工作线程数：m_Cur
	*
	***		成员方法：
	***		- - - - （公有）唯一构造函数：CThreadPool
	***		- - - - （公有）析构函数：~CThreadPool
	***		- - - - （公有）线程池运行逻辑：Run
	***		- - - - （公有）初始化：Init
	***		- - - - （公有）停止工作线程：StopWorking
	***		- - - - （公有）激活工作线程：NotifyWorking
	*
	**- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -*/
	class CThreadPool final: public CThread
	{
	public:
		explicit CThreadPool(	CThreadRunJob *p_J,
								CThreadJobQueue *p_O,
								CThreadJobQueue *p_R,
								const string &name,
								const unsigned int &id = 0,
								const int &max = 5,
								const int &cur = 5);
		~CThreadPool();
	
	public:
		virtual void Run();
	
	public:
		bool Init();

	public:
		void StopWorking(const bool &all = true);
		void NotifyWorking(const bool &all = false);
		void PauseWorking(const bool &all = true);
		void ResumeWorking(const bool &all = true);
	
	/*
	***		测试用
	*/
	public:
		const unsigned int  GetWorkingMapSize() const;
		void DisplayWorkingAddr();

	private:
		map<int, CThreadWorking*> m_t_Working;
		CThreadRunJob *m_j_Working;
		CThreadJobQueue *m_OrigJobs;
		CThreadJobQueue *m_ResultJobs;
		CThreadQueue *m_Idles;

	private:
		bool m_Init;
		int m_Max;
		int m_Cur;
	};

};