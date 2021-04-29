/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2021-04-25
*
***		内容：CRSAProc声明
*
**==================== 版本说明 ====================*/

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

	//** 私钥，公钥
	private:
		int m_Mode;
		int m_KeyLength;
		string m_KeyPrivate;
		string m_KeyPublic;

	//** 参数
	private:
		string m_FilePrivate;	//** 私钥存储
		string m_FilePublic;	//** 公钥存储
	};
}