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

#include "EnDeFrame.h"
#include "EnDe.h"

#include "AESProc.h"
//#include "RSAProc.h"

using namespace Sis_;

CEnDe::
CEnDe()
{
	m_Base = nullptr;
	m_Reset = false;
}

CEnDe::
~CEnDe()
{
	//...
}

int 
CEnDe::
InitAES(const unsigned char *key, const unsigned int len, const int type)
{
	if (m_Base)
	{
		return -10;
	}

	m_Base = new (nothrow) CAESProc();
	if (!m_Base)
	{
		return -11;
	}

	st_AESParam param(type, key, len);

	return m_Base->Init(&param);
}

int 
CEnDe::
InitRSA(const string &pri, const string &pub, const int len)
{
	if (m_Base)
	{
		return -10;
	}
}

int 
CEnDe::
Reset()
{
	if (m_Base)
	{
		delete m_Base;
		m_Base = nullptr;
	}

	return 0;
}

int 
CEnDe::
Encrypt(const string &plain, string &cipher, const int type)
{
	if (!m_Base)
	{
		return -1;
	}

	//** 流加密
	if (type == 0)
	{
		return m_Base->EncryptBinary(plain, cipher);
	}

	//** 文件加密
	if (type == 1)
	{
		return m_Base->EncryptFile(plain, cipher);
	}

	return -1;
}

int 
CEnDe::
Decrypt(const string &cipher, string &plain, const int type)
{
	if (!m_Base)
	{
		return -1;
	}

	//** 流加密
	if (type == 0)
	{
		return m_Base->DecryptBinary(cipher, plain);
	}

	//** 文件加密
	if (type == 1)
	{
		return m_Base->DecryptFile(cipher, plain);
	}

	return -1;
}