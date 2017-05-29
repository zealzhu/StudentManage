#pragma once
//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: �쳣��
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
		KeyUniqueException(std::string name) : exception(name.append("�����ظ�").c_str()) {}
	};

	class InputException : public std::exception
	{
	public:
		InputException() : exception("�������") {}
	};
}

#endif
