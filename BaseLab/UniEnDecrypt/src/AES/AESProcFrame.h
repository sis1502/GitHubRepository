/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2021-04-25
*
***		���ݣ�AES�ӽ���ģ��ר���������ݽṹ����
*
**==================== �汾˵�� ====================*/

#pragma once

#include "ExternFunc.h"

namespace Sis_ {

	typedef enum AESType_
	{
		AES_NORMAL = 0,
		AES_ECB,
		AES_CBC,
		AES_CTR,
		AES_CFB,
		AES_OFB
	}em_AESType, *em_AESType_ptr;

	inline void ConvertAESType(em_AESType &type, const int &typeI)
	{
		switch (typeI)
		{
		case 1:
			type = AES_ECB;
			break;
		case 2:
			type = AES_CBC;
			break;
		case 3:
			type = AES_CTR;
			break;
		case 4:
			type = AES_CFB;
			break;
		case 5:
			type = AES_OFB;
			break;
		default:
			type = AES_NORMAL;
			//break;
		}
	}

	typedef struct AESParam_
	{
	//private:
		em_AESType type;
		unsigned char *key;
		unsigned int len;

	public:
		AESParam_()
		{
			this->type = AES_NORMAL;
			this->key = nullptr;
			this->len = 0;
		}

		AESParam_(const int &type, const unsigned char *key, const int &len)
		{
			ConvertAESType(this->type, type);
			this->key = new unsigned char[len];
			memcpy(this->key, key, len);
			this->len = len;
		}

		~AESParam_()
		{
			if (this->key != nullptr)
			{
				delete this->key;
				this->key = nullptr;
			}
			this->len = 0;
		}

		const string Self(void) const
		{
			return string("AES");
		}

		void Display()
		{
			//...
		}
	}st_AESParam, *st_AESParam_ptr;
}