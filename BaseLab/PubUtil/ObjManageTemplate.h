/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2020-10-19
*
***		���ݣ�������Դ����ģ������
*
**==================== �汾˵�� ====================*/

#pragma once

#include "stdafx.h"

/*- - - - - - - - - - - - - - - - - - - - ��ģ�� - - - - - - - - - - - - - - - - - - - -**
*
***		���ƣ�������Դ������ģ��
*
***		Ŀ�ģ��ṩ������Դ���Թ���
*
***		���ߣ�Sis
*
***		����ʱ�䣺2020-10-19
*
***		�㷨������
***		- - - - 1. ��Դ������ȡ
***		- - - - 2. ��Դͳһ�ܿ�
***		- - - - 3. ��ʹ�÷���ʾ����Destroy���ж�������٣���ȷ�����ж��󶼴��ڿ���״̬
*
***		ģ�������
***		- - - - ����T
*
***		��Ա������
***		- - - - ��˽�У�������У�m_Objs
***		- - - - ��˽�У�����������m_Max
***		- - - - ��˽�У�ʵ�ʶ�������m_Cur
***		- - - - ��˽�У�������в�����������m_Mutex
***		- - - - ��˽�У����������m_ObjPara
*
***		��Ա������
***		- - - - �����У�Ψһ���캯����TObjManage
***		- - - - �����У�����������~TObjManage
***		- - - - �����У��������ж����˻���Դ��Destroy
***		- - - - �����У�ʹ�ö���Occupy
***		- - - - �����У��黹����Release
*
**- - - - - - - - - - - - - - - - - - - - ��ģ�� - - - - - - - - - - - - - - - - - - - -*/
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
