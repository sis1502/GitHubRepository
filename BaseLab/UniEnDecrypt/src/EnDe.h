/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2021-04-25
*
***		���ݣ�CEnDe�ඨ��
*
**==================== �汾˵�� ====================*/

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