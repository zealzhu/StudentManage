#pragma once
//////////////////////////////////////////////////
// Author:	朱鹏程
// Created:	2017/05/24
// Describe: 文件帮助类
//////////////////////////////////////////////////
#ifndef _ZHU_FILE_HELPER_H
#define _ZHU_FILE_HELPER_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>

#include "Info.h"

const std::string STUDENT_FILE_NAME = "student.dat";
const std::string CLASS_FILE_NAME = "class.dat";
const std::string GRADE_FILE_NAME = "grade.dat";
const std::string COURSE_FILE_NAME = "course.dat";
const std::string TEST_SUBJECT_FILE_NAME = "testsubject.dat";
const std::string SCORE_FILE_NAME = "score.dat";

namespace zhu
{
	class CFileHelper
	{
	public:
		template<class T>
		static bool Save(std::string strFileName, std::list<T>& lst);					//保存信息
		template<class T>
		static bool Append(std::string strFileName, const T& obj);						//追加信息
		template<class T>
		static std::list<T>* ReadAll(std::string strFileName);							//读取所有信息

		static bool SaveClass(std::list<CClass>& lst);
		static bool AppendClass(CClass& obj);
		static std::list<CClass>* ReadClassAll();

		static bool SaveGrade(std::list<CGrade>& lst);
		static bool AppendGrade(CGrade& obj);
		static std::list<CGrade>* ReadGradeAll();
	};
	//模板实现
	template<class T>
	inline bool CFileHelper::Save(std::string strFileName, std::list<T>& lst)
	{
		//打开文件
		std::ofstream file(strFileName, std::ios::out | std::ios::binary);
		if (!file) {
			return false;
		}

		//写数据
		for (std::list<T>::iterator it = lst.begin(); it != lst.end(); it++)
		{
			T& item = *it;
			file.write((char *)&item, sizeof(T));
		}

		//关闭
		file.close();
		return true;
	}

	template<class T>
	inline bool CFileHelper::Append(std::string strFileName, const T & obj)
	{
		//打开文件
		std::fstream file(strFileName, std::ios::app | std::ios::binary);
		if (!file)
		{
			return false;
		}

		//写数据
		file.write((char *)&obj, sizeof(T));

		//关闭
		file.close();
		return true;
	}

	template<class T>
	inline std::list<T>* CFileHelper::ReadAll(std::string strFileName)
	{
		if (GRADE_FILE_NAME == strFileName)						//读取年级的数据
			return reinterpret_cast<std::list<T>*>(ReadGradeAll());
		else if (CLASS_FILE_NAME == strFileName)				//读取班级的数据
			return reinterpret_cast<std::list<T>*>(ReadClassAll());

		std::list<T>* list = new std::list<T>();

		//打开文件
		std::ifstream file(strFileName, std::ios::in | std::ios::binary);
		if (!file)
		{
			return list;
		}

		//读数据
		T item;
		while (file.read((char *)&item, sizeof(T)))
		{
			list->push_back(item);
		}

		//关闭
		file.close();
		return list;
	}
}

#endif // !_ZHU_FILE_HELPER_H
