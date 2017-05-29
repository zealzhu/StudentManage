#pragma once
//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: ������Ϣ�Ĺ�����
//////////////////////////////////////////////////

#ifndef _ZHU_MANAGER_H
#define _ZHU_MANAGER_H

#include "FileHelper.h"
#include "Exception.h"
#include "Info.h"

namespace zhu
{
	/*
		����ָ���������
	*/
	template<class T>
	struct OnSearch
	{
		typedef bool(*SEARCH_SUCCESS)(std::list<T>&, typename std::list<T>::iterator&);			//��ѯ�ص�����
		typedef bool(*COMPARE_BY_NO)(int, T&);													//int�ȽϺ���
		typedef bool(*COMPARE_BY_CHAR)(const char*, T&);										//�ַ��ȽϺ���
	};
	
	/*
		���������
	*/
	class IManager
	{
		
	public:
		IManager() {};
		virtual ~IManager() = 0 {};					//��������Ϊ���ܹ������������������

	public:
		int Menu();									//�˵�
		virtual void Add() = 0;						//���
		virtual void Del() = 0;						//ɾ��
		virtual void Update() = 0;					//�޸�
		virtual void Search() = 0;					//����

	protected:
		/*	ͨ��no����
		 *	param1: ���ҵ�no
		 *	param2: ���ҵ��ļ���
		 *	param3: ���ҵ�����
		 *	param3: ���ҳɹ��Ļص�
		 *	return: �����Ƿ���ҵ�
		 */
		template<class T>
		static bool Search(int, std::string,
			typename OnSearch<T>::COMPARE_BY_NO, typename OnSearch<T>::SEARCH_SUCCESS);
	
		/*	ͨ���ַ�������
		*	param1: ���ҵ��ַ���
		*	param2: ���ҵ��ļ���
		*	param3: ���ҵ�����
		*	param3: ���ҳɹ��Ļص�
		*	return: �����Ƿ���ҵ�
		*/
		template<class T>
		static bool Search(const char*, std::string,
			typename OnSearch<T>::COMPARE_BY_CHAR, typename OnSearch<T>::SEARCH_SUCCESS);	//ͨ��char*����
	};
	template<class T>
	inline bool IManager::Search(int nNo, 
		std::string strFileName,
		typename OnSearch<T>::COMPARE_BY_NO compare,
		typename OnSearch<T>::SEARCH_SUCCESS callback)
	{
		bool bFind = false;

		//��ȡ��Ϣ
		std::list<T>* list = CFileHelper::ReadAll<T>(strFileName);

		//����
		std::list<T>::iterator it;
		for (it = list->begin(); it != list->end(); it++)
		{
			if (compare(nNo, *it))
			{
				bFind = true;
				if (callback != NULL) {
					//	�лص�ִ�лص�
					if (!callback(*list, it))
						break;
				}
				else
				{
					break;
				}			
			}
		}
		delete list;

		return bFind;
	}
	template<class T>
	inline bool zhu::IManager::Search(const char* szName, 
		std::string strFileName,
		typename OnSearch<T>::COMPARE_BY_CHAR compare,
		typename OnSearch<T>::SEARCH_SUCCESS callback)
	{
		bool bFind = false;

		//��ȡ��Ϣ
		std::list<T>* list = CFileHelper::ReadAll<T>(strFileName);

		//����
		std::list<T>::iterator it;
		for (it = list->begin(); it != list->end(); it++)
		{
			if (compare(szName, *it))
			{
				bFind = true;
				if (callback != NULL) {
					//	�лص�ִ�лص�
					if (!callback(*list, it))
						break;
				}
				else
				{
					break;
				}
			}
		}
		delete list;

		return bFind;
	}
	/*
		ѧ��������
	*/
	class CStudentManager : public IManager
	{
	public:
		static void Print(CStudent& objStudent);													//��ӡ������¼
		static void Print(std::list<zhu::CStudent>* list);											//��ӡ����

	public:
		void Add();																					//���
		void Del();																					//ɾ��
		void Update();																				//�޸�
		void Search();																				//����

	private:
		void SearchMenu();																			//���Ҳ˵�
		void SearchAll();																			//��������
		void SearchByNo();																			//ͨ��ѧ�Ų���
		void SearchByName();																		//ͨ����������
		void SearchByClass();																		//ͨ���༶����

	private:
		static bool OnDelete(std::list<zhu::CStudent>&, std::list<zhu::CStudent>::iterator&);		//ɾ���ص�
		static bool OnUpdate(std::list<zhu::CStudent>&, std::list<zhu::CStudent>::iterator&);		//���»ص�
		static bool OnSearchByNo(std::list<zhu::CStudent>&, std::list<zhu::CStudent>::iterator&);	//ͨ��ѧ�Ų��һص�
		static bool OnSearchByChar(std::list<zhu::CStudent>&, std::list<zhu::CStudent>::iterator&); //ͨ��char���һص�
	};

	/*
		�༶������
	*/
	class CClassManager : public IManager
	{
	public:
		static void Print(std::list<zhu::CClass>* list);					//��ӡ

	public:
		void Add();															//���
		void Del();															//ɾ��
		void Update();														//�޸�
		void Search();														//����

	private:
		static bool OnDelete(std::list<zhu::CClass>&, std::list<zhu::CClass>::iterator&);
		static bool OnUpdate(std::list<zhu::CClass>&, std::list<zhu::CClass>::iterator&);
	};

	/*
		��ι�����
	*/
	class CGradeManager : public IManager
	{
	public:
		static void Print(std::list<zhu::CGrade>* list);									//��ӡ

	public:
		void Add();																			//���
		void Del();																			//ɾ��
		void Update();																		//�޸�
		void Search();																		//����

	private:
		static bool OnDelete(std::list<zhu::CGrade>&, std::list<zhu::CGrade>::iterator&);
		static bool OnUpdate(std::list<zhu::CGrade>&, std::list<zhu::CGrade>::iterator&);
	};

	/*
		�γ̹�����
	*/
	class CCourseManager : public IManager
	{
	public:
		static void Print(std::list<zhu::CCourse>* list);									//��ӡ

	public:
		void Add();																			//���
		void Del();																			//ɾ��
		void Update();																		//�޸�
		void Search();																		//����

	private:
		static bool OnDelete(std::list<zhu::CCourse>&, std::list<zhu::CCourse>::iterator&);
		static bool OnUpdate(std::list<zhu::CCourse>&, std::list<zhu::CCourse>::iterator&);
	};

	/*
		���Կ�Ŀ������
	*/
	class CTestSubjectManager : public IManager
	{
	public:
		static void Print(std::list<zhu::CTestSubject>* list);		//��ӡ

	public:
		void Add();			//���
		void Del();			//ɾ��
		void Update();		//�޸�
		void Search();		//����

	private:
		static bool OnDelete(std::list<zhu::CTestSubject>&, std::list<zhu::CTestSubject>::iterator&);
		static bool OnUpdate(std::list<zhu::CTestSubject>&, std::list<zhu::CTestSubject>::iterator&);
	};

	/*
		ѧ���ɼ�������
	*/
	class CScoreManager : public IManager
	{
		typedef bool(*COMPARE_BY_INT_AND_CHAR)(int, const char*, CScore&);
		typedef bool(*COMPARE_BY_CHAR_AND_CHAR)(const char*, const char*, CScore&);
	public:
		static void Print(std::list<zhu::CScore>*);											//��ӡ
	public:
		void Add();																			//���
		void Del();																			//ɾ��
		void Update();																		//�޸�
		void Search();																		//����

	public:
		void Statistics();																	//ͳ����Ϣ

	private:
		void UpdateMenu();
		void UpdateByNoAndCourseName();														//ͨ��ѧ�źͿγ���ɾ��
		void UpdateByNameAndCourseName();													//ͨ�������Ϳγ���ɾ��

		void DeleteMenu();																	//ɾ���˵�
		void DeleteByNoAndCourseName();														//ͨ��ѧ�źͿγ���ɾ��
		void DeleteByNameAndCourseName();													//ͨ�������Ϳγ���ɾ��

		void SearchAll();																	//��������
		void SearchMenu();																	//���Ҳ˵�
		void SearchByNoAndCourseName();														//ͨ��ѧ�źͿγ�������
		void SearchByNameAndCourseName();													//ͨ�������Ϳγ�������

		bool Search(int nNo, const char* szClassName,
			typename COMPARE_BY_INT_AND_CHAR compare,
			typename OnSearch<CScore>::SEARCH_SUCCESS callback);
		bool Search(const char* szStudentName, const char* szClassName,
			typename COMPARE_BY_CHAR_AND_CHAR compare,
			typename OnSearch<CScore>::SEARCH_SUCCESS callback);

	private:
		static bool OnDelete(std::list<zhu::CScore>&, 
			std::list<zhu::CScore>::iterator&);												//ͨ��ѧ��ɾ���ص�

		static bool OnUpdate(std::list<zhu::CScore>&, 
			std::list<zhu::CScore>::iterator&);												//ͨ��ѧ�Ÿ��»ص�

		static bool OnSearchByNoAndCourseName(std::list<zhu::CScore>&, 
			std::list<zhu::CScore>::iterator&);												//ͨ��ѧ�Ų��һص�
		static bool OnSearchByNameAndCourseName(std::list<zhu::CScore>&, 
			std::list<zhu::CScore>::iterator&);												//ͨ��char���һص�
	};
	
}

#endif // !_ZHU_MANAGER_H