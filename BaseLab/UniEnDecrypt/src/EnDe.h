/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2021-04-25
*
***		内容：CEnDe类定义
*
**==================== 版本说明 ====================*/

#pragma once

#include "stdafx.h"

namespace Sis_
{
	class CEnDeBase;

	class CEnDe final
	{
	public:
		CEnDe();
		virtual ~CEnDe();

	public:
		int InitAES(const unsigned char *key, const unsigned int len, const int type = 0);
		int InitRSA(const string &pri, const string &pub, const int len);
		int Reset();
		int Encrypt(const string &plain, string &cipher, const int type = 0);
		int Decrypt(const string &cipher, string &plain, const int type = 0);

	private:
		CEnDeBase *m_Base;

	private:
		bool m_Reset;
	};
}