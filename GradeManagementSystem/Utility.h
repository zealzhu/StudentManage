//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: ������
//////////////////////////////////////////////////
#ifndef _ZHU_UTILITY_H
#define _ZHU_UTILITY_H

#include <stdarg.h>

namespace zhu 
{
	class CUtility 
	{
	public:
		static void IsNumber();
		static void CheckParam(char* arg1, ...);
	};
}

#endif