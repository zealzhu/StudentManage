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
	//	no�ظ�
	class KeyUniqueException : public std::exception
	{
	public:
		KeyUniqueException(std::string name) : exception(name.append("�����ظ�").c_str()) {}
	};

	//	�������
	class InputException : public std::exception
	{
	public:
		InputException() : exception("�����ʽ����") {}
	};
	//	û���ҵ���Ӧ��
	class NotFoundException : public std::exception
	{
	public:
		NotFoundException(std::string name) : exception(("û���ҵ���Ӧ" + name + ",�������").c_str()) {}
	};
}

#endif
