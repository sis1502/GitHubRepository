/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2021-04-25
*
***		内容：CEnDeBase类声明
*
**==================== 版本说明 ====================*/

#pragma once

#include "stdafx.h"

namespace Sis_
{
	class CEnDeBase
	{
	public:
		CEnDeBase() {};
		virtual ~CEnDeBase() {};

	public:
		virtual int Init(void *p) = 0;
		virtual int EncryptBinary(const string &plain, string &cipher) = 0;
		virtual int DecryptBinary(const string &cipher, string &plain) = 0;
		virtual int EncryptFile(const string &plain, const string &cipher) = 0;
		virtual int DecryptFile(const string &cipher, const string &plain) = 0;
	};
}