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

#include "EnDeBase.h"

namespace Sis_ {

	class CRSAProc final : public CEnDeBase
	{
	public:
		CRSAProc();
		~CRSAProc();

	public:
		virtual int Init(void *p);
		virtual int EncryptBinary(const string &plain, string &cipher);
		virtual int DecryptBinary(const string &cipher, string &plain);
		virtual int EncryptFile(const string &plain, const string &cipher);
		virtual int DecryptFile(const string &cipher, const string &plain);

	private:
		int Init(const int &keyLength, const string &filePrivate, const string &filePublic);
		int GenerateRSAKey();
		int EncryptWithPrivate(const string &clear, string &cipher);
		int EncryptWithPublic(const string &clear, string &cipher);
		int DecryptWithPrivate(const string &cipher, string &clear);
		int DecryptWithPublic(const string &cipher, string &clear);

	//** ˽Կ����Կ
	private:
		int m_Mode;
		int m_KeyLength;
		string m_KeyPrivate;
		string m_KeyPublic;

	//** ����
	private:
		string m_FilePrivate;	//** ˽Կ�洢
		string m_FilePublic;	//** ��Կ�洢
	};
}