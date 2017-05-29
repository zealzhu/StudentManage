#pragma once
#pragma once
//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: �ļ�������
//////////////////////////////////////////////////
#ifndef _ZHU_FILE_HELPER_H
#define _ZHU_FILE_HELPER_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

#include "Info.h"

const std::string STUDENT_FILE_NAME = "student.dat";
const std::string CLASS_FILE_NAME = "class.dat";
const std::string GRADE_FILE_NAME = "grade.dat";
const std::string COURSE_FILE_NAME = "course.dat";
const std::string TEST_SUBJECT_FILE_NAME = "testsubject.dat";
const std::string SCORE_FILE_NAME = "score.dat";

namespace zhu
{
	template<class T>
	class CFileHelper
	{
	public:		
		static void Save(std::string strFileName, std::vector<T>& vec);					//������Ϣ
		static void Append(std::string strFileName, const T& obj);						//׷����Ϣ
		static std::vector<T>* ReadAll(std::string strFileName);						//��ȡ������Ϣ

		static void SaveHasVector(std::string strFileName, std::vector<T>& vec);		//������Ϣ
		static void AppendHasVector(std::string strFileName, const T& obj);				//׷����Ϣ
		static std::vector<T>* ReadHasVectorAll(std::string strFileName);				//��ȡ������Ϣ
	};
}

#endif // !_ZHU_FILE_HELPER_H
