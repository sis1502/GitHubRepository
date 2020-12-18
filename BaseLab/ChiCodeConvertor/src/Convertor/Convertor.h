/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2020-10-19
*
***		���ݣ�CConvertor����
*
**==================== �汾˵�� ====================*/

#pragma once

#include "ConvertorFrame.h"

class CConvertor final
{
public:
	explicit CConvertor(void *para);
	~CConvertor();

public:
	const em_ConvStatus Convert(const string &from_C, const string &to_C, const string &from_S, string &to_S);
	const em_ConvStatus UTF8toGBK(const string &utf8, string &gbk);
	const em_ConvStatus GBKtoUTF8(const string &gbk, string &utf8);

private:
	string m_AppName;
	string m_MoudleName;
	string m_ClassName;
	string m_LogPrefix;
	
private:
};
