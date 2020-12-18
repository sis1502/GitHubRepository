/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadJobQueue类定义
*
**==================== 版本说明 ====================*/

#pragma once

namespace Sis_{

	/*- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：任务队列虚基类
	*
	***		目的：实现任务队列托管
	*
	***		作者：Sis
	*
	***		建立时间：2020-10-19
	*
	***		算法概述：无
	*
	***		成员变量：无
	*
	***		成员方法：
	***		- - - - （公有）唯一构造函数：CThreadJobQueue
	***		- - - - （公有）虚析构函数：~CThreadJobQueue
	***		- - - - （公有）获取一个任务：Get，纯虚函数
	***		- - - - （公有）置入一个任务：Set，纯虚函数
	***		- - - - （公有）设置任务完成标识：Done，纯虚函数
	*
	**- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -*/
	class CThreadJobQueue
	{
	public:
		explicit CThreadJobQueue(){}
		virtual ~CThreadJobQueue(){}
	
	public:
		virtual bool Get(void * &job) = 0;
		virtual bool Set(void * &job) = 0;
		virtual bool Done(void * &job, const bool &succ) = 0;
	};

};