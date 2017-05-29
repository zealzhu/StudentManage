#pragma once
//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: ������Ϣ��
//////////////////////////////////////////////////

#ifndef _ZHU_INFO_H
#define _ZHU_INFO_H

#include <string>
#include <list>

namespace zhu
{
	/*
		�Ա�ö��
	*/
	enum Sex
	{
		MAN,								//��
		WOMAN								//Ů
	};

	/*
		ѧ����Ϣ
	 */
	class CStudent
	{
		friend class CFileHelper;
		friend class CStudentManager;
	public:
		CStudent();															 					//���캯��
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
		static bool compareStudentNo(int nNo, CStudent& objStudent);							//�Ա�ѧ��
		static bool compareClassName(const char* szClassName, CStudent& objStudent);			//�ԱȰ༶��
		static bool compareStudentName(const char* szStudentName, CStudent& objStudent);		//�Ա�����

	private:
		int m_nStudentNo;																		//ѧ��
		Sex m_emSex;																			//�Ա�
		char m_szClassName[15];																	//�༶
		char m_szStuentName[15];																//����
		char m_szNation[10];																	//����
		char m_szNativePlace[10];																//����
		char m_szEntranceDate[15];																//��ѧ����
		char m_szBornDate[15];																	//��������
		char m_szAddress[20];																	//��ͥסַ
		char m_szPhone[12];																		//��ϵ�绰
	};

	/*
		�༶��Ϣ
	*/
	class CClass
	{
		friend class CFileHelper;
		friend class CClassManager;
	public:
		static bool compareClassNo(int nNo, CClass& objClass);									//�ԱȰ༶��
	public:
		CClass();
		CClass(int nClassNo, const char* szClassName);
		CClass(int nClassNo, const char* szClassName, std::list<int> lstStudentNo);
	private:
		int m_nClassNo;																			//�༶��
		char m_szClassName[15];																	//�༶��
		std::list<int> m_lstStudentNo;															//ѧ�ż���
	};

	/*
		�����Ϣ
	*/
	class CGrade
	{
		friend class CFileHelper;
		friend class CGradeManager;
	public:
		static bool compareGradeNo(int nNo, CGrade& objGrade);									//�Ա���κ�
	public:
		CGrade();
		CGrade(int nGradeNo, const char* szGradeName);
		CGrade(int nGradeNo, const char* szGradeName, std::list<int> lstClassNo);

	private:
		int m_nGradeNo;																			//�༶��
		char m_szGradeName[15];																	//�����
		std::list<int> m_lstClassNo;															//�༶�ż���
	};

	/*
		�γ���Ϣ�пγ�����ö��
	*/
	enum CourseType
	{
		TYPE_REQUIRED_COURSE = 1,		//ѡ�޿�
		TYPE_OPTIONAL_COURSE = 2		//���޿�
	};

	/*
		�γ���Ϣ
	*/
	class CCourse
	{
		friend class CFileHelper;
		friend class CCourseManager;
	public:
		static bool compareCourseNo(int nNo, CCourse& objGrade);									//�Աȿγ̺�
	public:
		CCourse();
		CCourse(int nCourseNo, const char* szCourseName, 
			const char* szDescription, CourseType emCourseType);

	private:
		int m_nCourseNo;																			//�γ̺�
		char m_szCourseName[15];																	//�γ���		
		char m_szDescription[20];																	//�γ�����
		CourseType m_emCourseType;																	//�γ�����
	};

	/*
		���Կ�Ŀ��Ϣ
	*/
	class CTestSubject
	{
		friend class CFileHelper;
		friend class CTestSubjectManager;
	public:
		static bool compareTestSubjectNo(int nNo, CTestSubject& objTestSubject);					//�Աȿ��Ժ�

	public:
		CTestSubject();
		CTestSubject(int nTestSubjectNo, const char* szTestSubjectName, const char* szCourseName);

	private:
		int m_nTestSubjectNo;																		//���Ա��
		char m_szTestSubjectName[15];																//��������
		char m_szCourseName[15];																	//���Կ�Ŀ
	};

	/*
		ѧ���ɼ�
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
		static bool compareStudentNoAndCourseName(int nNo, 											//�Ա�ѧ��+�γ̺�
			const char* szCourseName, CScore& objScore);
		static bool compareStudentNameAndCourseName(const char* szStudentName,						//�Ա�����+�γ̺�
			const char* szCourseName, CScore& objScore);

	private:
		int m_nTestSubjectNo;																		//���Ա��
		int m_nStudentNo;																			//ѧ��
		char m_szStudentName[15];																	//����
		char m_szCourseName[15];																	//�γ���
		char m_szClassName[15];																		//�༶
		float m_fScore;																				//�ɼ�
	};
}

#endif // !_ZHU_INFO_H