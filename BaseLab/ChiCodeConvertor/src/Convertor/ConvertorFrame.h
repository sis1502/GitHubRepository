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
	CCONVERTOR_CONVERT_ICONVOPEN,
	CCONVERTOR_CONVERT_BADALLOC,
	CCONVERTOR_CONVERT_ICONV
}em_ConvStatus;
inline const string getConvStatusMessage(const em_ConvStatus &status)
{
	switch(status)
	{
	case SUCCESS:
		return "Success";
	case CCONVERTOR_CONVERT_ICONVOPEN:
		return "Failed to do ICONV_OPEN";
	case CCONVERTOR_CONVERT_BADALLOC:
		return "Failed to alloc in/out buff";
	case CCONVERTOR_CONVERT_ICONV:
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