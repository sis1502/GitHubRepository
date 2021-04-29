/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2021-04-25
*
***		内容：CRSAProc定义
*
**==================== 版本说明 ====================*/

#include "RSAProc.h"

#include "openssl/rsa.h"
#include "openssl/pem.h"

//** 填充模式1（RSA_PKCS1_PADDING）：单次密文数据长度为RSA_size() - 11
#define RSA_PKCS1_PADDING_SIZE 11
//** 填充模式2（RSA_PKCS1_OAEP_PADDING）：单次密文数据长度为RSA_size() - 41
#define RSA_PKCS1_OAEP_PADDING_SIZE 41
//** 不填充（RSA_NO_PADDING）：单次密文数据长度为RSA_size()
#define RSA_NO_PADDING_SIZE 0

using namespace Sis_;

CRSAProc::
CRSAProc()
{
	m_KeyPrivate = "";
	m_KeyPublic = "";
	m_KeyLength = 2048;
	m_FilePrivate = GetRunningDirectory() + "private_key.pem";
	m_FilePublic = GetRunningDirectory() + "public_key.pem";
}

CRSAProc::
~CRSAProc()
{
	//...
}

int 
CRSAProc::
Init(void *p)
{
	st_RSAParam_ptr p_ = (st_RSAParam_ptr)p;

	m_KeyLength = p_->len;
	m_KeyPrivate = p_->pri;
	m_KeyPublic = p_->pub;

	return 0;
}

int 
CRSAProc::
EncryptBinary(const string &plain, string &cipher)
{
	return 0;
}

int 
CRSAProc::
DecryptBinary(const string &cipher, string &plain)
{
	return 0;
}

int 
CRSAProc::
EncryptFile(const string &plain, const string &cipher)
{
	return 0;
}

int 
CRSAProc::
DecryptFile(const string &cipher, const string &plain)
{
	return 0;
}



int 
CRSAProc::
Init(const int &keyLength, const string &filePrivate, const string &filePublic)
{
	m_KeyLength = keyLength;
	m_FilePrivate = filePrivate;
	m_KeyPrivate = GetFileContent(m_FilePrivate);
	m_FilePublic = filePublic;
	m_KeyPublic = GetFileContent(m_FilePublic);

	cout << "pri:" << m_KeyPrivate << endl;
	cout << "pub:" << m_KeyPublic << endl;

	return 0;
}

int 
CRSAProc::
GenerateRSAKey()
{
	int ret = 0;

	//** 私钥
	BIO *pri = BIO_new(BIO_s_mem());
	char *keyPri = nullptr;
	int lenPri = 0;

	//** 公钥
	BIO *pub = BIO_new(BIO_s_mem());
	char *keyPub = nullptr;
	int lenPub = 0;

	//** 生成密钥对
	RSA *pair = RSA_generate_key(m_KeyLength, RSA_3, nullptr, nullptr);

	//** 分离私钥
	PEM_write_bio_RSAPrivateKey(pri, pair, nullptr, nullptr, 0, nullptr, nullptr);
	lenPri = BIO_pending(pri);
	keyPri = new char[lenPri];
	BIO_read(pri, keyPri, lenPri);
	m_KeyPrivate.assign(keyPri, lenPri);
	if (SaveToFile(m_FilePrivate, m_KeyPrivate) != 0)
	{
		ret = -1;
	}

	//** 分离公钥
	PEM_write_bio_RSAPublicKey(pub, pair);
	lenPub = BIO_pending(pub);
	keyPub = new char[lenPub];
	BIO_read(pub, keyPub, lenPub);
	m_KeyPublic.assign(keyPub, lenPub);
	if (SaveToFile(m_FilePublic, m_KeyPublic) != 0)
	{
		ret = -2;
	}

	RSA_free(pair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	delete keyPub;
	delete keyPri;

	return ret;
}

int 
CRSAProc::
EncryptWithPrivate(const string &clear, string &cipher)
{
	RSA* rsa = RSA_new();

	BIO *bio = BIO_new_mem_buf((unsigned char *)m_KeyPrivate.c_str(), -1);
	rsa = PEM_read_bio_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
	if (!rsa)
	{
		BIO_free_all(bio);
		return -1;
	}

	int lenRSA = RSA_size(rsa);
	cout << "lenRSA:" << lenRSA << endl;
	//** RSA_PKCS1_PADDING方式
	int block = lenRSA - 11;

	char *blockCipher = new char[lenRSA];
	for (int pos = 0; pos < clear.size(); pos += block)
	{
		//** 取待编码的数据段
		string subClear = clear.substr(pos, block);
		cout << "clearSub:" << subClear << "[" << subClear.size() << "]" << endl;
		//** 清空密文缓冲区
		memset(blockCipher, '\0', lenRSA);
		int ret = RSA_private_encrypt(subClear.size(),
			(const unsigned char*)subClear.c_str(),
			(unsigned char*)blockCipher,
			rsa,
			RSA_PKCS1_PADDING);
		cout << "RSA_private_encrypt:" << ret << endl;
		cipher.append(blockCipher, ret);
	}

	delete blockCipher;
	BIO_free_all(bio);
	RSA_free(rsa);

	return 0;
}

int 
CRSAProc::
EncryptWithPublic(const string &clear, string &cipher)
{
	RSA* rsa = RSA_new();

	BIO *bio = BIO_new_mem_buf((unsigned char *)m_KeyPublic.c_str(), -1);
	rsa = rsa = PEM_read_bio_RSAPublicKey(bio, &rsa, nullptr, nullptr);
	if (!rsa)
	{
		BIO_free_all(bio);
		return -1;
	}

	int lenRSA = RSA_size(rsa);
	cout << "lenRSA:" << lenRSA << endl;
	//** RSA_PKCS1_PADDING方式
	int block = lenRSA - 11;

	char *blockCipher = new char[lenRSA];
	for (int pos = 0; pos < clear.size(); pos += block)
	{
		//** 取待编码的数据段
		string subClear = clear.substr(pos, block);
		cout << "clearSub:" << subClear << "[" << subClear.size() << "]" << endl;
		//** 清空密文缓冲区
		memset(blockCipher, '\0', lenRSA);
		int ret = RSA_public_encrypt(subClear.size(),
			(const unsigned char*)subClear.c_str(),
			(unsigned char*)blockCipher,
			rsa,
			RSA_PKCS1_PADDING);
		cout << "RSA_public_encrypt:" << ret << endl;
		cipher.append(blockCipher, ret);
	}

	delete blockCipher;
	BIO_free_all(bio);
	RSA_free(rsa);

	return 0;
}

int 
CRSAProc::
DecryptWithPrivate(const string &cipher, string &clear)
{
	RSA* rsa = RSA_new();

	BIO *bio = BIO_new_mem_buf((unsigned char *)m_KeyPrivate.c_str(), -1);
	rsa = PEM_read_bio_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
	if (!rsa)
	{
		BIO_free_all(bio);
		return -1;
	}

	int lenRSA = RSA_size(rsa);
	char *blockClear = new char[lenRSA];

	for (int pos = 0; pos < cipher.size(); pos += lenRSA)
	{
		//** 取待解密的数据段
		string subCipher = cipher.substr(pos, lenRSA);
		//** 清空明文缓冲区
		memset(blockClear, '\0', lenRSA);
		int ret = RSA_private_decrypt(subCipher.size(),
			(const unsigned char*)subCipher.c_str(),
			(unsigned char*)blockClear,
			rsa,
			RSA_PKCS1_PADDING);
		cout << "RSA_private_decrypt:" << ret << endl;
		clear.append(blockClear, ret);
	}

	delete blockClear;
	BIO_free_all(bio);
	RSA_free(rsa);

	return 0;
}

int 
CRSAProc::
DecryptWithPublic(const string &cipher, string &clear)
{
	RSA* rsa = RSA_new();

	BIO *bio = BIO_new_mem_buf((unsigned char *)m_KeyPublic.c_str(), -1);
	rsa = PEM_read_bio_RSAPublicKey(bio, &rsa, nullptr, nullptr);
	if (!rsa)
	{
		BIO_free_all(bio);
		return -1;
	}

	int lenRSA = RSA_size(rsa);
	char *blockClear = new char[lenRSA];

	for (int pos = 0; pos < cipher.size(); pos += lenRSA)
	{
		//** 取待解密的数据段
		string subCipher = cipher.substr(pos, lenRSA);
		//** 清空明文缓冲区
		memset(blockClear, '\0', lenRSA);
		int ret = RSA_public_decrypt(subCipher.size(),
			(const unsigned char*)subCipher.c_str(),
			(unsigned char*)blockClear,
			rsa,
			RSA_PKCS1_PADDING);
		cout << "RSA_public_decrypt:" << ret << endl;
		clear.append(blockClear, ret);
	}

	delete blockClear;
	BIO_free_all(bio);
	RSA_free(rsa);

	return 0;
}
