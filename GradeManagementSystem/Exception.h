#pragma once
//////////////////////////////////////////////////
// Author:	朱鹏程
// Created:	2017/05/24
// Describe: 异常类
//////////////////////////////////////////////////
#ifndef _ZHU_EXCEPTION_H
#define _ZHU_EXCEPTION_H

#include <iostream>
#include <exception>

namespace zhu
{
	class KeyUniqueException : public std::exception
	{
	public:
		KeyUniqueException(std::string name) : exception(name.append("不能重复").c_str()) {}
	};

	class InputException : public std::exception
	{
	public:
		InputException() : exception("输入错误") {}
	};
}

#endif
