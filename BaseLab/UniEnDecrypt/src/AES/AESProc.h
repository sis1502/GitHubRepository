/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2021-04-25
*
***		内容：CAESProc声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "AESProcFrame.h"

#include "EnDeBase.h"

namespace Sis_ {

	class CAESProc final : public CEnDeBase
	{
	public:
		CAESProc();
		~CAESProc();

	public:
		virtual int Init(void *p);
		virtual int EncryptBinary(const string &plain, string &cipher);
		virtual int DecryptBinary(const string &cipher, string &plain);
		virtual int EncryptFile(const string &plain, const string &cipher);
		virtual int DecryptFile(const string &cipher, const string &plain);

	private:
		int Encrypt(const string &plain, string &cipher);
		int Decrypt(const string &cipher, string &plain);

	private:
		em_AESType m_Type;
		unsigned char *m_Key;
		int m_KeyLength;
		int m_KeyBit;
	};
}