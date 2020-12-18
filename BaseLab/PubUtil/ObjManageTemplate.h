/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：对象资源管理模板声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "stdafx.h"

/*- - - - - - - - - - - - - - - - - - - - 类模板 - - - - - - - - - - - - - - - - - - - -**
*
***		名称：对象资源管理类模板
*
***		目的：提供对象资源共性管理
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		算法概述：
***		- - - - 1. 资源互斥提取
***		- - - - 2. 资源统一管控
***		- - - - 3. 由使用方显示调用Destroy进行对象池销毁，须确定所有对象都处于空闲状态
*
***		模板变量：
***		- - - - 对象：T
*
***		成员变量：
***		- - - - （私有）对象队列：m_Objs
***		- - - - （私有）最大对象数：m_Max
***		- - - - （私有）实际对象数：m_Cur
***		- - - - （私有）对象队列操作互斥锁：m_Mutex
***		- - - - （私有）对象参数：m_ObjPara
*
***		成员方法：
***		- - - - （公有）唯一构造函数：TObjManage
***		- - - - （公有）析构函数：~TObjManage
***		- - - - （公有）销毁所有对象，退还资源：Destroy
***		- - - - （公有）使用对象：Occupy
***		- - - - （公有）归还对象：Release
*
**- - - - - - - - - - - - - - - - - - - - 类模板 - - - - - - - - - - - - - - - - - - - -*/
template <typename T>
class TObjManage
{
public:
	explicit TObjManage(void *para, const unsigned int &max = 10)
	{
		m_ObjPara = para;
		if (max <= 0)
		{
			m_Max = 1;
		}
		else
		{
			m_Max = max;
		}
		m_Cur = 0;
	}
	
	~TObjManage() {}
	
public:
	bool Destroy()
	{
		while (!m_Objs.empty())
		{
			T *obj = m_Objs.pop();
			if (obj)
			{
				delete obj;
			}
		}
		
		return true;
	}

	bool Occupy(T *&obj)
	{
		lock_guard <mutex> lock(m_Mutex);
		
		if (m_Objs.empty())
		{
			try
			{
				obj = new T(m_ObjPara);
			}
			catch(...)
			{
				return false;
			}
			if (obj)
			{
				m_Cur ++;
			}
			else
			{
				return false;
			}
		}
		else
		{
			obj = m_Objs.front();
			m_Objs.pop();
		}
		
		return true;
	}


	bool Release(T *&obj)
	{
		lock_guard <mutex> lock(m_Mutex);
	
		m_Objs.push(obj);
		
		return true;
	}
	
private:
	queue<T*> m_Objs;
	unsigned int m_Max;
	unsigned int m_Cur;
	
private:
	mutex m_Mutex;
	void *m_ObjPara;
};
