/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadQueue类声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "ThreadFrame.h"

namespace Sis_ {

	/*- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：线程状态管理队列操作类
	*
	***		目的：线程统一管控
	*
	***		作者：Sis
	*
	***		建立时间：2020-10-19
	*
	***		算法概述：
	***		- - - - 无
	*
	***		成员变量：
	***		- - - - （私有）线程队列：m_Threads
	***		- - - - （私有）队列操作锁：m_Mutex
	*
	***		成员方法：
	***		- - - - （公有）唯一构造函数：CThreadQueue
	***		- - - - （公有）析构函数：~CThreadQueue
	***		- - - - （公有）获取线程：Get
	***		- - - - （公有）置入线程：Set
	*
	**- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -*/
	class CThreadQueue final
	{
	public:
		explicit CThreadQueue();
		~CThreadQueue();
	
	public:
		bool Get(int &id);
		bool Set(const int &id);
	
	private:
		queue<int> m_Threads;
		mutex m_Mutex;
	};

};