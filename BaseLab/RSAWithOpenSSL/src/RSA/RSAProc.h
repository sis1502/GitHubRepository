/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2021-04-25
*
***		���ݣ�CRSAProc����
*
**==================== �汾˵�� ====================*/

#pragma once

#include "RSAProcFrame.h"

namespace Sis_ {

	class CRSAProc final
	{
	public:
		CRSAProc();
		~CRSAProc();

	public:
		int Init(const int &keyLength, const string &filePrivate, const string &filePublic);
		int GenerateRSAKey();

	public:
		int EncryptWithPrivate(const string &clear, string &cipher);
		int EncryptWithPublic(const string &clear, string &cipher);
		int DecryptWithPrivate(const string &cipher, string &clear);
		int DecryptWithPublic(const string &cipher, string &clear);

	//** ˽Կ����Կ
	private:
		string m_KeyPrivate;
		string m_KeyPublic;

	//** ����
	private:
		int m_KeyLength;		//** ��Կ����
		string m_FilePrivate;	//** ˽Կ�洢
		string m_FilePublic;	//** ��Կ�洢
	};
}