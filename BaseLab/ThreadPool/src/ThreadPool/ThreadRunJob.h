/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.5
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CThreadRunJob类定义
*
**==================== 版本说明 ====================*/

#pragma once

namespace Sis_ {

	class CThreadJobQueue;

	/*- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -**
	*
	***		名称：任务执行虚基类
	*
	***		目的：实现任务执行逻辑托管
	*
	***		作者：Sis
	*
	***		建立时间：2020-10-19
	*
	***		算法概述：
	***		- - - - 1. 通过Run方法将相关队列传递至应用层，由应用层实现具体逻辑
	*
	***		成员变量：无
	*
	***		成员方法：
	***		- - - - （公有）唯一构造函数：CThreadRunJob
	***		- - - - （公有）虚析构函数：~CThreadRunJob
	***		- - - - （公有）逻辑实现：Run，纯虚函数
	*
	**- - - - - - - - - - - - - - - - - - - - 类封装 - - - - - - - - - - - - - - - - - - - -*/
	class CThreadRunJob
	{
	public:
		explicit CThreadRunJob(){}
		virtual ~CThreadRunJob(){}
	
	public:
		virtual bool Run(CThreadJobQueue *p_O, CThreadJobQueue *p_R) = 0;
	};

};