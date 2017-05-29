#pragma once
//////////////////////////////////////////////////
// Author:	朱鹏程
// Created:	2017/05/24
// Describe: 各种信息的管理类
//////////////////////////////////////////////////

#ifndef _ZHU_MANAGER_H
#define _ZHU_MANAGER_H

#include "FileHelper.h"
#include "Exception.h"
#include "Info.h"

namespace zhu
{
	/*
		函数指针的重命名
	*/
	template<class T>
	struct OnSearch
	{
		typedef bool(*SEARCH_SUCCESS)(std::vector<T>&, typename std::vector<T>::iterator&);			//查询回调函数
		typedef bool(*COMPARE_BY_NO)(int, T&);													//int比较函数
		typedef bool(*COMPARE_BY_CHAR)(const char*, T&);										//字符比较函数
	};
	
	/*
		管理抽象类
	*/
	class IManager
	{
		
	public:
		IManager() {};
		virtual ~IManager() = 0 {};					//虚析构，为了能够调用子类的析构函数

	public:
		int Menu();									//菜单
		virtual void Add() = 0;						//添加
		virtual void Del() = 0;						//删除
		virtual void Update() = 0;					//修改
		virtual void Search() = 0;					//查找

	protected:
		/*	通过no查找
		 *	param1: 查找的no
		 *	param2: 查找的文件名
		 *	param3: 查找的条件
		 *	param3: 查找成功的回调
		 *	return: 返回是否查找到
		 */
		template<class T>
		static bool Search(int, std::string,
			typename OnSearch<T>::COMPARE_BY_NO, typename OnSearch<T>::SEARCH_SUCCESS);
	
		/*	通过字符串查找
		*	param1: 查找的字符串
		*	param2: 查找的文件名
		*	param3: 查找的条件
		*	param3: 查找成功的回调
		*	return: 返回是否查找到
		*/
		template<class T>
		static bool Search(const char*, std::string,
			typename OnSearch<T>::COMPARE_BY_CHAR, typename OnSearch<T>::SEARCH_SUCCESS);	//通过char*查找
	};
	template<class T>
	inline bool IManager::Search(int nNo, 
		std::string strFileName,
		typename OnSearch<T>::COMPARE_BY_NO compare,
		typename OnSearch<T>::SEARCH_SUCCESS callback)
	{
		bool bFind = false;

		//读取信息
		std::vector<T>* vector = CFileHelper::ReadAll<T>(strFileName);

		//遍历
		std::vector<T>::iterator it;
		for (it = vector->begin(); it != vector->end(); it++)
		{
			if (compare(nNo, *it))
			{
				bFind = true;
				if (callback != NULL) {
					//	有回调执行回调
					if (!callback(*vector, it))
						break;
				}
				else
				{
					break;
				}			
			}
		}
		delete vector;

		return bFind;
	}
	template<class T>
	inline bool zhu::IManager::Search(const char* szName, 
		std::string strFileName,
		typename OnSearch<T>::COMPARE_BY_CHAR compare,
		typename OnSearch<T>::SEARCH_SUCCESS callback)
	{
		bool bFind = false;

		//读取信息
		std::vector<T>* vector = CFileHelper::ReadAll<T>(strFileName);

		//遍历
		std::vector<T>::iterator it;
		for (it = vector->begin(); it != vector->end(); it++)
		{
			if (compare(szName, *it))
			{
				bFind = true;
				if (callback != NULL) {
					//	有回调执行回调
					if (!callback(*vector, it))
						break;
				}
				else
				{
					break;
				}
			}
		}
		delete vector;

		return bFind;
	}
	/*
		学生管理类
	*/
	class CStudentManager : public IManager
	{
	public:
		static void Print(CStudent& objStudent);													//打印单条记录
		static void Print(std::vector<zhu::CStudent>* vector);											//打印集合

	public:
		void Add();																					//添加
		void Del();																					//删除
		void Update();																				//修改
		void Search();																				//查找

	private:
		void SearchMenu();																			//查找菜单
		void SearchAll();																			//查找所有
		void SearchByNo();																			//通过学号查找
		void SearchByName();																		//通过姓名查找
		void SearchByClass();																		//通过班级查找

	private:
		static bool OnDelete(std::vector<zhu::CStudent>&, std::vector<zhu::CStudent>::iterator&);		//删除回调
		static bool OnUpdate(std::vector<zhu::CStudent>&, std::vector<zhu::CStudent>::iterator&);		//更新回调
		static bool OnSearchByNo(std::vector<zhu::CStudent>&, std::vector<zhu::CStudent>::iterator&);	//通过学号查找回调
		static bool OnSearchByChar(std::vector<zhu::CStudent>&, std::vector<zhu::CStudent>::iterator&); //通过char查找回调
	};

	/*
		班级管理类
	*/
	class CClassManager : public IManager
	{
	public:
		static void Print(std::vector<zhu::CClass>* vector);					//打印

	public:
		void Add();															//添加
		void Del();															//删除
		void Update();														//修改
		void Search();														//查找

	private:
		static bool OnDelete(std::vector<zhu::CClass>&, std::vector<zhu::CClass>::iterator&);
		static bool OnUpdate(std::vector<zhu::CClass>&, std::vector<zhu::CClass>::iterator&);
	};

	/*
		年段管理类
	*/
	class CGradeManager : public IManager
	{
	public:
		static void Print(std::vector<zhu::CGrade>* vector);									//打印

	public:
		void Add();																			//添加
		void Del();																			//删除
		void Update();																		//修改
		void Search();																		//查找

	private:
		static bool OnDelete(std::vector<zhu::CGrade>&, std::vector<zhu::CGrade>::iterator&);
		static bool OnUpdate(std::vector<zhu::CGrade>&, std::vector<zhu::CGrade>::iterator&);
	};

	/*
		课程管理类
	*/
	class CCourseManager : public IManager
	{
	public:
		static void Print(std::vector<zhu::CCourse>* vector);									//打印

	public:
		void Add();																			//添加
		void Del();																			//删除
		void Update();																		//修改
		void Search();																		//查找

	private:
		static bool OnDelete(std::vector<zhu::CCourse>&, std::vector<zhu::CCourse>::iterator&);
		static bool OnUpdate(std::vector<zhu::CCourse>&, std::vector<zhu::CCourse>::iterator&);
	};

	/*
		考试科目管理类
	*/
	class CTestSubjectManager : public IManager
	{
	public:
		static void Print(std::vector<zhu::CTestSubject>* vector);		//打印

	public:
		void Add();			//添加
		void Del();			//删除
		void Update();		//修改
		void Search();		//查找

	private:
		static bool OnDelete(std::vector<zhu::CTestSubject>&, std::vector<zhu::CTestSubject>::iterator&);
		static bool OnUpdate(std::vector<zhu::CTestSubject>&, std::vector<zhu::CTestSubject>::iterator&);
	};

	/*
		学生成绩管理类
	*/
	class CScoreManager : public IManager
	{
		typedef bool(*COMPARE_BY_INT_AND_CHAR)(int, const char*, CScore&);
		typedef bool(*COMPARE_BY_CHAR_AND_CHAR)(const char*, const char*, CScore&);
	public:
		static void Print(std::vector<zhu::CScore>*);									//打印
	public:
		void Add();																	//添加
		void Del();																	//删除
		void Update();																//修改
		void Search();																//查找

	public:
		void Statistics();															//统计信息

	private:
		void UpdateByNoAndCourseName();												//通过学号和课程名删除
		void UpdateByNameAndCourseName();											//通过姓名和课程名删除

		void DeleteByNoAndCourseName();												//通过学号和课程名删除
		void DeleteByNameAndCourseName();											//通过姓名和课程名删除

		void SearchAll();															//查找所有
		void SearchByNoAndCourseName();												//通过学号和课程名查找
		void SearchByNameAndCourseName();											//通过姓名和课程名查找

		bool Search(int nNo, const char* szClassName,								//通过学号和课程名查找并执行回调
			typename COMPARE_BY_INT_AND_CHAR compare,
			typename OnSearch<CScore>::SEARCH_SUCCESS callback);
		bool Search(const char* szStudentName, const char* szClassName,				//通过姓名和课程名查找并执行回调
			typename COMPARE_BY_CHAR_AND_CHAR compare,
			typename OnSearch<CScore>::SEARCH_SUCCESS callback);

	private:
		static bool OnDelete(std::vector<zhu::CScore>&,
			std::vector<zhu::CScore>::iterator&);									//通过学号删除回调
		static bool OnUpdate(std::vector<zhu::CScore>&,
			std::vector<zhu::CScore>::iterator&);									//通过学号更新回调
		static bool OnSearchByNoAndCourseName(std::vector<zhu::CScore>&,
			std::vector<zhu::CScore>::iterator&);									//通过学号查找回调
		static bool OnSearchByNameAndCourseName(std::vector<zhu::CScore>&,
			std::vector<zhu::CScore>::iterator&);									//通过char查找回调
	};
	
}

#endif // !_ZHU_MANAGER_H