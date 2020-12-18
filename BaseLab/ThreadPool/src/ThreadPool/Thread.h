/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThread类声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "ThreadFrame.h"

namespace Sis_ {

	/*- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：线程执行类
	*
	***		目的：系统线程执行动作
	*
	***		作者：Sis
	*
	***		建立时间：2020-10-19
	*
	***		算法概述：
	***		- - - - 1. 作为线程执行的物理对象存在，所有线程的虚基类
	***		- - - - 2. 提供线程控制方法
	*
	***		成员变量：
	***		- - - - （保护）停止标识：m_Stop
	***		- - - - （保护）暂停标识：m_Pause
	***		- - - - （保护）线程标识号：m_Id
	***		- - - - （保护）线程名：m_Name
	***		- - - - （私有）线程锁：m_Mutex
	***		- - - - （私有）同步信号：m_Cond
	***		- - - - （私有）同步锁指示器：m_CondLocked
	*
	***		成员方法：
	***		- - - - （公有）唯一构造函数：CThread
	***		- - - - （公有）虚析构函数：~CThread
	***		- - - - （公有）纯虚函数：Run，由继承类实现
	***		- - - - （公有）启动线程：Start
	***		- - - - （公有）停止线程：Stop
	***		- - - - （公有）激活线程：Resume
	***		- - - - （公有）线程暂停：Pause
	***		- - - - （公有）线程等待：Wait
	***		- - - - （公有）线程激活：Notify
	***		- - - - （保护）线程运行：ThreadProc，静态函数
	***		- - - - （保护）线程清理：ThreadClean，静态函数
	*
	**- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -*/
	class CThread
	{
	public:
		explicit CThread();
		virtual ~CThread();

	public:
		virtual void Run() = 0;

	public:
		bool Start();
		bool Stop();
		bool Resume();
		bool Pause();
		bool Wait(const unsigned int &sec = 0);
		bool Notify();

	protected:
		static void ThreadProc(void *para);
		static void ThreadClean(void *para);

	protected:
		bool m_Stop;
		bool m_Pause;
		unsigned int m_Id;
		string m_Name;

	private:
		mutex m_Mutex;
		condition_variable m_Cond;

	private:
		bool m_CondLocked;
	};

};