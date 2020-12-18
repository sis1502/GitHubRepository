/*==================== �汾˵�� ====================**
*
***		�汾�ţ�v0.0.0.1
*
***		���ߣ�Sis
*
***		����ʱ�䣺2020-10-19
*
***		���ݣ�ת��ģ��ר���������ݽṹ����
*
**==================== �汾˵�� ====================*/

#pragma once

#include "stdafx.h"

typedef enum _ConvStatus
{
	SUCCESS = 0,
	CCONV_CONVERT_ICONVOPEN,
	CCONV_CONVERT_BADALLOC,
	CCONV_CONVERT_ICONV
}em_ConvStatus;
inline const string getConvStatusMessage(const em_ConvStatus &status)
{
	switch(status)
	{
	case SUCCESS:
		return "Success";
	case CCONV_CONVERT_ICONVOPEN:
		return "Failed to do ICONV_OPEN";
	case CCONV_CONVERT_BADALLOC:
		return "Failed to alloc in/out buff";
	case CCONV_CONVERT_ICONV:
		return "Failed to do ICONV";
	default:
		return "ERROR!";
	};
}

/*
***		�������ʼ��������
*/
typedef struct _ConstructPara
{
	string app;
	string mdl;
	string cls;
}st_ConstructPara, *st_ConstructPara_ptr;
