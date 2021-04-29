/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2021-04-25
*
***		内容：CAESProc定义
*
**==================== 版本说明 ====================*/

#include "AESProc.h"

#include "openssl/aes.h"

using namespace Sis_;

CAESProc::
CAESProc()
{
	m_Type = AES_NORMAL;
	m_Key = nullptr;
	m_KeyLength = 0;
	m_KeyBit = 0;
}

CAESProc::
~CAESProc()
{
	if (m_Key != nullptr)
	{
		delete m_Key;
		m_Key = nullptr;
	}
}

int 
CAESProc::
Init(void *p)
{
	st_AESParam_ptr p_ = (st_AESParam_ptr)p;
	//return this->Init(p_->key, p_->len, p_->type);

	m_KeyBit = p_->len * 8;
	if (m_KeyBit != 128 && m_KeyBit != 192 && m_KeyBit != 256)
	{
		return -1;
	}

	if (m_Key)
	{
		delete m_Key;
		m_Key = nullptr;
	}
	m_Key = new (nothrow) unsigned char[p_->len];
	if (!m_Key)
	{
		return -2;
	}
	memcpy(m_Key, p_->key, p_->len);
	m_KeyLength = p_->len;

	ConvertAESType(m_Type, p_->type);

	return 0;
}

int 
CAESProc::
EncryptBinary(const string &plain, string &cipher)
{
	return this->Encrypt(plain, cipher);
}

int 
CAESProc::
DecryptBinary(const string &cipher, string &plain)
{
	return this->Decrypt(cipher, plain);
}

int 
CAESProc::
EncryptFile(const string &plain, const string &cipher)
{
	return 0;
}

int 
CAESProc::
DecryptFile(const string &cipher, const string &plain)
{
	return 0;
}

int 
CAESProc::
Encrypt(const string &plain, string &cipher)
{
	AES_KEY aes;

	int ret = AES_set_encrypt_key(m_Key, m_KeyBit, &aes);
	if (ret < 0)
	{
		return ret;
	}
	//cout << "AES_set_encrypt_key:" << ret << endl;

	unsigned char *ustrPlain = new unsigned char[AES_BLOCK_SIZE];
	unsigned char *ustrCipher = new unsigned char[AES_BLOCK_SIZE];
	char *strCipher = new char[AES_BLOCK_SIZE];
	for (int pos = 0; pos < plain.size(); pos += AES_BLOCK_SIZE)
	{
		memset(ustrPlain, '\0', AES_BLOCK_SIZE);
		memset(ustrCipher, '\0', AES_BLOCK_SIZE);
		memset(strCipher, '\0', AES_BLOCK_SIZE);

		string subPlain = plain.substr(pos, AES_BLOCK_SIZE);
		memcpy(ustrPlain, subPlain.c_str(), subPlain.size());
		//DisplayUnsignedcharInHex(ustrClear, subClear.size(), "ustrClear");

		if (m_Type == AES_NORMAL)
		{
			AES_encrypt(ustrPlain, ustrCipher, &aes);
		}
		else if (m_Type == AES_ECB)
		{
			AES_ecb_encrypt(ustrPlain, ustrCipher, &aes, AES_ENCRYPT);
		}
		else if (m_Type == AES_CBC)
		{
			unsigned char iv[AES_BLOCK_SIZE] = { 0 };
			AES_cbc_encrypt(ustrPlain, ustrCipher, AES_BLOCK_SIZE, &aes, iv, AES_ENCRYPT);
		}		

		//DisplayUnsignedcharInHex(ustrCipher, AES_BLOCK_SIZE, "ustrCipher");
		memcpy(strCipher, ustrCipher, AES_BLOCK_SIZE);
		//DisplayCharInHex(strCipher, AES_BLOCK_SIZE, "strCipher");
		cipher.append(strCipher, AES_BLOCK_SIZE);
	}

	delete ustrPlain;
	delete ustrCipher;
	delete strCipher;

	return 0;
}

int 
CAESProc::
Decrypt(const string &cipher, string &plain)
{
	AES_KEY aes;

	int ret = AES_set_decrypt_key(m_Key, m_KeyBit, &aes);
	if (ret < 0)
	{
		return ret;
	}

	unsigned char *ustrCipher = new unsigned char[AES_BLOCK_SIZE];
	unsigned char *ustrPlain = new unsigned char[AES_BLOCK_SIZE];
	char *strPlain = new char[AES_BLOCK_SIZE];
	for (int pos = 0; pos < cipher.size(); pos += AES_BLOCK_SIZE)
	{
		memset(ustrCipher, '\0', AES_BLOCK_SIZE);
		memset(ustrPlain, '\0', AES_BLOCK_SIZE);
		memset(strPlain, '\0', AES_BLOCK_SIZE);

		string subCipher = cipher.substr(pos, AES_BLOCK_SIZE);
		memcpy(ustrCipher, subCipher.c_str(), subCipher.size());

		if (m_Type == AES_NORMAL)
		{
			AES_decrypt(ustrCipher, ustrPlain, &aes);
		}
		else if (m_Type == AES_ECB)
		{
			AES_ecb_encrypt(ustrCipher, ustrPlain, &aes, AES_DECRYPT);
		}
		else if (m_Type == AES_CBC)
		{
			unsigned char iv[AES_BLOCK_SIZE] = { 0 };
			AES_cbc_encrypt(ustrCipher, ustrPlain, AES_BLOCK_SIZE, &aes, iv, AES_DECRYPT);
		}

		memcpy(strPlain, ustrPlain, AES_BLOCK_SIZE);
		//DisplayCharInHex(strClear, AES_BLOCK_SIZE, "strClear");
		plain.append(strPlain, AES_BLOCK_SIZE);
	}

	//** 规整解密串
	plain = plain.substr(0, plain.find('\0'));

	delete ustrCipher;
	delete ustrPlain;
	delete strPlain;

	return 0;
}