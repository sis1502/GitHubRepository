/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2021-04-25
*
***		���ݣ��ӽ���ģ��ר���������ݽṹ����
*
**==================== �汾˵�� ====================*/

#pragma once

#include "ExternFunc.h"

namespace Sis_ {

	typedef struct RSAParam_
	{
	//private:
		int type;
		string pri;
		string pub;
		int len;

	public:
		RSAParam_()
		{
			this->type = 0;
			this->pri.clear();
			this->pub.clear();
			this->len = 0;
		}

		RSAParam_(const int &type, const string &pri, const string &pub, const int &len)
		{
			this->type = type;
			this->pri = pri;
			this->pub = pub;
			this->len = len;
		}

		~RSAParam_()
		{
			this->type = 0;
			this->pri.clear();
			this->pub.clear();
			this->len = 0;
		}

		const string Self(void) const
		{
			return string("RSA");
		}

		void Display()
		{
			//...
		}
	}st_RSAParam, *st_RSAParam_ptr;
}