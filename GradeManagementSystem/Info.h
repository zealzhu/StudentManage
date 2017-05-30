#pragma once
//////////////////////////////////////////////////
// Author:	朱鹏程
// Created:	2017/05/24
// Describe: 各种信息类
//////////////////////////////////////////////////

#ifndef _ZHU_INFO_H
#define _ZHU_INFO_H

#include <string>
#include <vector>

namespace zhu
{
	/*
		性别枚举
	*/
	enum Sex
	{
		MAN,								//男
		WOMAN								//女
	};

	/*
		学生信息
	 */
	class CStudent
	{
		friend class CFileHelper;
		friend class CStudentManager;
	public:
		CStudent();															 					//构造函数
		CStudent(int nStudentNo,				
			Sex emSex, 
			const char* szClassName,
			const char* szStuentName,
			const char* szNation,
			const char* szNativePlace,
			const char* szEntranceDate,
			const char* szBornDate,
			const char* szAddress,
			const char* szPhone);

	public:
		static bool compareStudentNo(int nNo, CStudent& objStudent);							//对比学号
		static bool compareClassName(const char* szClassName, CStudent& objStudent);			//对比班级名
		static bool compareStudentName(const char* szStudentName, CStudent& objStudent);		//对比姓名

	private:
		int m_nStudentNo;																		//学号
		Sex m_emSex;																			//性别
		char m_szClassName[15];																	//班级
		char m_szStuentName[15];																//姓名
		char m_szNation[10];																	//民族
		char m_szNativePlace[10];																//籍贯
		char m_szEntranceDate[15];																//入学日期
		char m_szBornDate[15];																	//出生日期
		char m_szAddress[20];																	//家庭住址
		char m_szPhone[12];																		//联系电话
	};

	/*
		班级信息
	*/
	class CClass
	{
		friend class CFileHelper;
		friend class CClassManager;
		friend class CStudentManager;
	public:
		static bool compareClassNo(int nNo, CClass& objClass);									//对比班级号
		static bool compareClassName(const char*, CClass& objClass);							//对比班级名

	public:
		CClass();
		CClass(int nClassNo, const char* szClassName);
		CClass(int nClassNo, const char* szClassName, std::vector<int> vecStudentNo);
	private:
		int m_nClassNo;																			//班级号
		char m_szClassName[15];																	//班级名
		std::vector<int> m_vecStudentNo;														//学号集合
	};

	/*
		年段信息
	*/
	class CGrade
	{
		friend class CFileHelper;
		friend class CGradeManager;
	public:
		static bool compareGradeNo(int nNo, CGrade& objGrade);									//对比年段号
	public:
		CGrade();
		CGrade(int nGradeNo, const char* szGradeName);
		CGrade(int nGradeNo, const char* szGradeName, std::vector<int> vecClassNo);

	private:
		int m_nGradeNo;																			//班级号
		char m_szGradeName[15];																	//年段名
		std::vector<int> m_vecClassNo;															//班级号集合
	};

	/*
		课程信息中课程类型枚举
	*/
	enum CourseType
	{
		TYPE_REQUIRED_COURSE = 1,		//选修课
		TYPE_OPTIONAL_COURSE = 2		//必修课
	};

	/*
		课程信息
	*/
	class CCourse
	{
		friend class CFileHelper;
		friend class CCourseManager;
	public:
		static bool compareCourseNo(int nNo, CCourse& objCourse);									//对比课程号
		static bool compareCourseName(const char* szCourseName, CCourse& objCourse);					//对比课程名
	public:
		CCourse();
		CCourse(int nCourseNo, const char* szCourseName, 
			const char* szDescription, CourseType emCourseType);

	private:
		int m_nCourseNo;																			//课程号
		char m_szCourseName[15];																	//课程名		
		char m_szDescription[20];																	//课程描述
		CourseType m_emCourseType;																	//课程类型
	};

	/*
		考试科目信息
	*/
	class CTestSubject
	{
		friend class CFileHelper;
		friend class CTestSubjectManager;
	public:
		static bool compareTestSubjectNo(int nNo, CTestSubject& objTestSubject);					//对比考试号
		static bool compareTestSubjectName(const char* szName, CTestSubject& objTestSubject);		//对比考试名

	public:
		CTestSubject();
		CTestSubject(int nTestSubjectNo, const char* szTestSubjectName, const char* szCourseName);

	private:
		int m_nTestSubjectNo;																		//考试编号
		char m_szTestSubjectName[15];																//考试名称
		char m_szCourseName[15];																	//考试科目
	};

	/*
		学生成绩
	*/
	class CScore
	{
		friend class CFileHelper;
		friend class CScoreManager;
	public:
		CScore();
		CScore(int nTestSubjectNo, int nStudentNo, const char* szStudentName, 
			const char* szCourseName, const char* szClassName, float fScore);
	public:
		static bool compareStudentNoAndCourseName(int nNo, 											//对比学号+课程号
			const char* szCourseName, CScore& objScore);
		static bool compareStudentNameAndCourseName(const char* szStudentName,						//对比姓名+课程号
			const char* szCourseName, CScore& objScore);

	private:
		int m_nTestSubjectNo;																		//考试编号
		int m_nStudentNo;																			//学号
		char m_szStudentName[15];																	//姓名
		char m_szCourseName[15];																	//课程名
		char m_szClassName[15];																		//班级
		float m_fScore;																				//成绩
	};
}

#endif // !_ZHU_INFO_H