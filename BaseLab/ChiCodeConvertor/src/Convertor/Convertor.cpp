/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：CConvertor定义
*
**==================== 版本说明 ====================*/

#include "Convertor.h"

CConvertor::
CConvertor(void *para)
{
	st_ConstructPara_ptr p = (st_ConstructPara_ptr)para;
	m_AppName = p->app;
	m_MoudleName = p->mdl;
	m_ClassName = p->cls;
	m_LogPrefix = "[" + m_AppName + "][" + m_MoudleName + "][" + m_ClassName + "]";
}

CConvertor::
~CConvertor()
{
	//...
}

const em_ConvStatus  
CConvertor::
Convert(const string &from_C, const string &to_C, const string &from_S, string &to_S)
{
	//** 判定标识
	em_ConvStatus errCode = _ConvStatus::SUCCESS;

#ifdef _WIN32
	UINT cp_From, cp_To;
	string tmpFromC, tmpToC;
	tmpFromC.resize(from_C.size());
	tmpToC.resize(to_C.size());
	transform(from_C.begin(), from_C.end(), tmpFromC.begin(), ::toupper);
	transform(to_C.begin(), to_C.end(), tmpToC.begin(), ::toupper);
	if (tmpFromC == "UTF-8")
	{
		cp_From = CP_UTF8;
	}
	else if (tmpFromC == "GBK")
	{
		cp_From = CP_ACP;
	}
	if (tmpToC == "UTF-8")
	{
		cp_To = CP_UTF8;
	}
	else if (tmpToC == "GBK")
	{
		cp_To = CP_ACP;
	}

	printf("tmpFormC:%s, tmpToC:%s\n", tmpFromC.c_str(), tmpToC.c_str());
	printf("cp_From:%d, cp_To:%d\n", cp_From, cp_To);

	//转Unicode
	int len = MultiByteToWideChar(cp_From, 0, from_S.c_str(), -1, NULL, 0);
	printf("To Unicode:%d\n", len);
	wchar_t *strUnicode = new wchar_t[len];
	wmemset(strUnicode, 0, len);
	MultiByteToWideChar(cp_From, 0, from_S.c_str(), -1, strUnicode, len);

	//从Unicode转
	len = WideCharToMultiByte(cp_To, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	char *strUtf8 = new char[len];
	WideCharToMultiByte(cp_To, 0, strUnicode, -1, strUtf8, len, NULL, NULL);

	to_S.assign(strUtf8, len);
	
	delete strUnicode;
	delete strUtf8;
#else
	iconv_t cd = iconv_open(to_C.c_str(), from_C.c_str());
	if (cd == (iconv_t)(-1))
	{
		printf("[ERROR]%sopen iconv failed\n", m_LogPrefix.c_str());
		return _ConvStatus::CCONVERTOR_CONVERT_ICONVOPEN;
	}
	
	//** 数据转存
	char *inbuff = nullptr;
	char *pIn = nullptr;	//** 用于释放输入字符串空间的临时指针
	size_t inbytesleft = from_S.size();
	char *outbuff = nullptr;
	size_t outbytesleft = to_S.size();
	char *pOut = nullptr;	//** 用于释放输出字符串空间的临时指针
	inbuff = new (nothrow)char[inbytesleft];
	outbuff = new (nothrow)char[outbytesleft];
	if (inbuff && outbuff)
	{
		memcpy(inbuff, from_S.c_str(), inbytesleft);
		memset(outbuff, '\0', outbytesleft);
	}
	else
	{
		printf("[ERROR]%salloc failed\n", m_LogPrefix.c_str());
		errCode = _ConvStatus::CCONVERTOR_CONVERT_BADALLOC;
	}
	
	if (errCode == _ConvStatus::SUCCESS)
	{
		pIn = inbuff;
		pOut = outbuff;
		if (iconv(cd, &inbuff, &inbytesleft, &outbuff, &outbytesleft) == (size_t)(-1))
		{
			printf("[ERROR]%siconv failed\n", m_LogPrefix.c_str());
			to_S.assign("");
			errCode = _ConvStatus::CCONVERTOR_CONVERT_ICONV;
		}
		else
		{
			to_S.assign(pOut, to_S.size() - outbytesleft);
		}
	}
	
	iconv_close(cd);
	
	//** 释放空间
	if (pIn)
	{
		delete pIn;
	}
	if (pOut)
	{
		delete pOut;
	}
#endif

	return errCode;
}

const em_ConvStatus  
CConvertor::
UTF8toGBK(const string &utf8, string &gbk)
{
	gbk.resize(utf8.size());
	return this->Convert("utf-8", "gbk", utf8, gbk);
}

const em_ConvStatus  
CConvertor::
GBKtoUTF8(const string &gbk, string &utf8)
{
	utf8.resize(gbk.size() * 3);
	return this->Convert("gbk", "utf-8", gbk, utf8);
}
