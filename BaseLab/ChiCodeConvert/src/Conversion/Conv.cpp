/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2020-10-19
*
***		���ݣ�CConv����
*
**==================== �汾˵�� ====================*/

#include "Conv.h"

CConv::
CConv(void *para)
{
	st_ConstructPara_ptr p = (st_ConstructPara_ptr)para;
	m_AppName = p->app;
	m_MoudleName = p->mdl;
	m_ClassName = p->cls;
	m_LogPrefix = "[" + m_AppName + "][" + m_MoudleName + "][" + m_ClassName + "]";
}

CConv::
~CConv()
{
	//...
}

const em_ConvStatus  
CConv::
Convert(const string &from_C, const string &to_C, const string &from_S, string &to_S)
{
	//** �ж���ʶ
	em_ConvStatus errCode = _ConvStatus::SUCCESS;
	
	iconv_t cd = iconv_open(to_C.c_str(), from_C.c_str());
	if (cd == (iconv_t)(-1))
	{
		printf("[ERROR]%sopen iconv failed\n", m_LogPrefix.c_str());
		return _ConvStatus::CCONV_CONVERT_ICONVOPEN;
	}

#ifdef _DEBUG
	printf("[DEBUG]%sfrom.size:%d, to.size:%d\n", m_LogPrefix.c_str(), from_S.size(), to_S.size());
#endif
	
	//** ����ת��
	char *inbuff = nullptr;
	char *pIn = nullptr;	//** �����ͷ������ַ����ռ����ʱָ��
	size_t inbytesleft = from_S.size();
	char *outbuff = nullptr;
	size_t outbytesleft = to_S.size();
	char *pOut = nullptr;	//** �����ͷ�����ַ����ռ����ʱָ��
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
		errCode = _ConvStatus::CCONV_CONVERT_BADALLOC;
	}
	
	if (errCode == _ConvStatus::SUCCESS)
	{
		pIn = inbuff;
		pOut = outbuff;
		if (iconv(cd, &inbuff, &inbytesleft, &outbuff, &outbytesleft) == (size_t)(-1))
		{
			printf("[ERROR]%siconv failed\n", m_LogPrefix.c_str());
			to_S.assign("");
			errCode = _ConvStatus::CCONV_CONVERT_ICONV;
		}
		else
		{
			to_S.assign(pOut, to_S.size() - outbytesleft);
		}
	}
	
	iconv_close(cd);
	
	//** �ͷſռ�
	if (pIn)
	{
		delete pIn;
	}
	if (pOut)
	{
		delete pOut;
	}
	
	return errCode;
}

const em_ConvStatus  
CConv::
UTF8toGBK(const string &utf8, string &gbk)
{
	gbk.resize(utf8.size());
	return this->Convert("utf-8", "gbk", utf8, gbk);
}

const em_ConvStatus  
CConv::
GBKtoUTF8(const string &gbk, string &utf8)
{
	utf8.resize(gbk.size() * 3);
	return this->Convert("gbk", "utf-8", gbk, utf8);
}
