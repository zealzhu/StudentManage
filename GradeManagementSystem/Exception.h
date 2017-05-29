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
	//	no重复
	class KeyUniqueException : public std::exception
	{
	public:
		KeyUniqueException(std::string name) : exception(name.append("不能重复").c_str()) {}
	};

	//	输入错误
	class InputException : public std::exception
	{
	public:
		InputException() : exception("输入格式错误") {}
	};
	//	没有找到对应项
	class NotFoundException : public std::exception
	{
	public:
		NotFoundException(std::string name) : exception(("没有找到对应" + name + ",请先添加").c_str()) {}
	};
}

#endif
