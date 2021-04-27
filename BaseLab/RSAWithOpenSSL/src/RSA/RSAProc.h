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

	//** 私钥，公钥
	private:
		string m_KeyPrivate;
		string m_KeyPublic;

	//** 参数
	private:
		int m_KeyLength;		//** 密钥长度
		string m_FilePrivate;	//** 私钥存储
		string m_FilePublic;	//** 公钥存储
	};
}