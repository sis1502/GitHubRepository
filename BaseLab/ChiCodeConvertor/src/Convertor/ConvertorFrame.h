/*==================== 版本说明 ====================**
*
***		版本号：v0.0.0.1
*
***		作者：Sis
*
***		建立时间：2020-10-19
*
***		内容：转码模块专属基础数据结构定义
*
**==================== 版本说明 ====================*/

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
***		对象构造初始化参数集
*/
typedef struct _ConstructPara
{
	string app;
	string mdl;
	string cls;
}st_ConstructPara, *st_ConstructPara_ptr;
