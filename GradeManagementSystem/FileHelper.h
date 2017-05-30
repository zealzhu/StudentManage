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
	class CFileHelper
	{
	public:
		template<class T>
		static void Save(std::string strFileName, std::vector<T>& vec);					//������Ϣ
		template<class T>
		static void Append(std::string strFileName, const T& obj);						//׷����Ϣ
		template<class T>
		static std::vector<T>* ReadAll(std::string strFileName);						//��ȡ������Ϣ

		template<class T>
		static void SaveHasVector(std::string strFileName, std::vector<T>& vec);		//������Ϣ
		template<class T>
		static void AppendHasVector(std::string strFileName, const T& obj);				//׷����Ϣ
		template<class T>
		static std::vector<T>* ReadHasVectorAll(std::string strFileName);				//��ȡ������Ϣ

	};
	//ģ��ʵ��
	template<class T>
	inline void CFileHelper::Save(std::string strFileName, std::vector<T>& vec)
	{
		//���ļ�
		std::ofstream file(strFileName, std::ios::out | std::ios::binary);
		if (!file)
			throw std::exception("�ļ���ʧ��");

		int nSize = vec.size();
		file.write((char *)&nSize, sizeof(int));
		if(nSize != 0)
			file.write((char *)&vec[0], vec.size() * sizeof(T));

		//�ر�
		file.close();
	}
	template<class T>
	inline void CFileHelper::Append(std::string strFileName, const T & obj)
	{
		//���ļ�
		std::fstream file(strFileName, std::ios::in|std::ios::out|std::ios::binary);
		if (!file)
			throw std::exception("�ļ���ʧ��");

		//��ȡ����
		int nSize = 0;
		file.seekp(0, std::ios::end);
		int nFileLength = file.tellp();
		if (nFileLength != 0) {
			file.seekg(0, std::ios::beg);
			file.read((char *)&nSize, sizeof(int));
		}
			
		//д����
		nSize++;
		file.seekp(0, std::ios::beg);
		file.write((char *)&nSize, sizeof(int));
		//д����
		file.seekp(0, std::ios::end);
		file.write((char *)&obj, sizeof(T));

		//�ر�
		file.close();
	}
	template<class T>
	inline std::vector<T>* CFileHelper::ReadAll(std::string strFileName)
	{
		if (GRADE_FILE_NAME == strFileName || CLASS_FILE_NAME == strFileName)
			return ReadHasVectorAll<T>(strFileName);

		//���ļ�
		std::ifstream file(strFileName, std::ios::in | std::ios::binary);
		if (!file)
		{
			//	û���ļ�����һ���ļ�
			std::ofstream of(strFileName, std::ios::out | std::ios::binary);
			if (!of)
				throw std::exception("�ļ�����ʧ��");
			of.close();

			return ReadAll<T>(strFileName);
		}

		//������
		int size = 0;
		file.read((char *)&size, sizeof(int));
		std::vector<T>* vector = new std::vector<T>(size);
		if (size != 0) 
		{
			file.read((char *)&((*vector)[0]), size * sizeof(T));
		}
		
		//�ر�
		file.close();
		return vector;
	}
	
	template<class T>
	inline void CFileHelper::SaveHasVector(std::string strFileName, std::vector<T>& vec)
	{
		//���ļ�
		std::ofstream file(strFileName, std::ios::out | std::ios::binary);
		if (!file)
			throw std::exception("�ļ���ʧ��");

		//д����
		int nSize = vec.size();
		file.write((char *)&nSize, sizeof(int));
		for (std::vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			//д������Ϣ
			file.write((char *)&(*it), sizeof(T) - sizeof(std::vector<int>));
			//��ȡvectorԪ��
			char* bfAddress = (char*)&(*it);											//��ȡ��Ԫ�ص�ַ
			char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);	//����Ԫ����vector��ַ
			std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);			//ת��Ϊvectorָ��
			//д��vectorԪ������
			int nTempSize = vecTemp->size();
			file.write((char *)&nTempSize, sizeof(int));
			//д������ֵ
			if(nTempSize != 0)
				file.write((char *)&((*vecTemp)[0]), sizeof(int) * nTempSize);		
		}
		//�ر�
		file.close();
	}
	template<class T>
	inline void CFileHelper::AppendHasVector(std::string strFileName, const T & obj)
	{
		//���ļ�
		std::fstream file(strFileName, std::ios::in | std::ios::out | std::ios::binary);
		if (!file)
			throw std::exception("�ļ���ʧ��");

		//��ȡ����
		int nSize = 0;
		file.seekp(0, std::ios::end);
		int nFileLength = file.tellp();
		if (nFileLength != 0) {
			file.seekg(0, std::ios::beg);
			file.read((char *)&nSize, sizeof(int));
		}
		//д����
		nSize++;
		file.seekp(0, std::ios::beg);												//��λ��ͷ
		file.write((char *)&nSize, sizeof(int));
		//д����
		file.seekp(0, std::ios::end);												//��λ��β��
		//д������Ϣ
		file.write((char *)&obj, sizeof(T) - sizeof(std::vector<int>));
		//��ȡvectorԪ��
		char* bfAddress = (char*)&obj;												//��ȡ��Ԫ�ص�ַ
		char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);		//����Ԫ����vector��ַ
		std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);				//ת��Ϊvectorָ��
		//д��vectorԪ������
		int nTempSize = vecTemp->size();
		file.write((char *)&nTempSize, sizeof(int));
		if (nTempSize != 0) {
			//д������ֵ
			file.write((char *)&((*vecTemp)[0]), sizeof(int) * nTempSize);
		}
	
		//�ر�
		file.close();
	}
	template<class T>
	inline std::vector<T>* CFileHelper::ReadHasVectorAll(std::string strFileName)
	{
		//���ļ�
		std::ifstream file(strFileName, std::ios::in | std::ios::binary);
		if (!file) 
		{
			//	û���ļ�����һ���ļ�
			std::ofstream of(strFileName, std::ios::out | std::ios::binary);
			if (!of) 
				throw std::exception("�ļ�����ʧ��");
			of.close();

			return ReadHasVectorAll<T>(strFileName);
		}
			
		//������
		int nSize = 0;
		file.read((char *)&nSize, sizeof(int));
		//������
		std::vector<T>* vecData = new std::vector<T>(nSize);
		if (nSize != 0)
		{
			for (std::vector<T>::iterator it = vecData->begin(); it != vecData->end(); it++)
			{
				//��������Ϣ
				file.read((char *)&(*it), sizeof(T) - sizeof(std::vector<int>));
				//������
				int nTempSize = 0;
				file.read((char *)&nTempSize, sizeof(int));
				//��ȡvector��ַ
				char* bfAddress = (char*)&(*it);											//��ȡ��Ԫ�ص�ַ
				char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);		//����Ԫ����vector��ַ
				std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);				//ת��Ϊvectorָ��
				if (nTempSize != 0) 
				{
					for (int i = 0; i < nTempSize; i++) 
					{
						//����������С
						vecTemp->push_back(0);
					}
					//������Ԫ��
					file.read((char *)&((*vecTemp)[0]), sizeof(int) * nTempSize);
				}
				
			}
		}
		
		//�ر�
		file.close();
		return vecData;
	}
}

#endif // !_ZHU_FILE_HELPER_H
