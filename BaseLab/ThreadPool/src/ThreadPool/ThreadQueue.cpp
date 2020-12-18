﻿/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadQueue类定义
*
**==================== 版本说明 ====================*/

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
***		参数：无
*
***		流程：无
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
CThreadQueue::
CThreadQueue()
{
	//...
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
CThreadQueue::
~CThreadQueue()
{
	//...
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		获取线程
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 线程号：id
*
***		流程：
***		- - - - 1. 检查是否队列是否为空
***		- - - - 2. 队列为空，返回false；队列不为空，弹出第一条线程的线程号
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThreadQueue::
Get(int &id)
{
	lock_guard<mutex> lock(m_Mutex);
	
	if (m_Threads.size() == 0)
	{
		return false;
	}
	else
	{
		id = m_Threads.front();
		m_Threads.pop();
#ifdef _DEBUG
		printf("[CThreadQueue::Get]%d\n", id);
#endif
	}

	return true;
}

/*- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -**
*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*												*
***		置入线程
*											*
* = = = = = = = = = = = = = = = = = = * * * ** * * *
*
***		参数：
***		- - - - 线程号：id
*
***		流程：
***		- - - - 1. 向队列尾部追加线程
*
**- - - - - - - - - - - - - - - - - - - - 函数说明 - - - - - - - - - - - - - - - - - - - -*/
bool 
CThreadQueue::
Set(const int &id)
{
	lock_guard<mutex> lock(m_Mutex);

#ifdef _DEBUG
	printf("[CThreadQueue::Set]%d\n", id);
#endif
	m_Threads.push(id);

	return true;
}

