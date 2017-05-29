#include "FileHelper.h"



// 保存
bool zhu::CFileHelper::SaveClass(std::list<CClass>& lst)
{
	//打开文件
	std::ofstream file(CLASS_FILE_NAME, std::ios::out | std::ios::binary);
	if (!file) {
		return false;
	}

	//写数据
	for (std::list<CClass>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		CClass& item = *it;
		file.write((char *)&(item.m_nClassNo), sizeof(int));							//写出班级号
		file.write((char *)&(item.m_szClassName), sizeof(item.m_szClassName));		//写出班级名

		int nSize = item.m_lstStudentNo.size();
		file.write((char *)&nSize, sizeof(int));					//写出学号数
		for (std::list<int>::iterator itStudentNo = item.m_lstStudentNo.begin();	//遍历写出所有学号
			itStudentNo != item.m_lstStudentNo.end(); 
			itStudentNo++)
		{
			file.write((char *)&(*itStudentNo), sizeof(int));	
		}	
	}

	//关闭
	file.close();
	return true;
}
bool zhu::CFileHelper::SaveGrade(std::list<CGrade>& lst)
{
	//打开文件
	std::ofstream file(GRADE_FILE_NAME, std::ios::out | std::ios::binary);
	if (!file) {
		return false;
	}

	//写数据
	for (std::list<CGrade>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		CGrade& item = *it;
		file.write((char *)&(item.m_nGradeNo), sizeof(int));							//写出班级号
		file.write((char *)&(item.m_szGradeName), sizeof(item.m_szGradeName));			//写出班级名

		int nSize = item.m_lstClassNo.size();
		file.write((char *)&nSize, sizeof(int));										//写出学号数
		for (std::list<int>::iterator itClassNo = item.m_lstClassNo.begin();			//遍历写出所有学号
			itClassNo != item.m_lstClassNo.end();
			itClassNo++)
		{
			file.write((char *)&(*itClassNo), sizeof(int));
		}
	}

	//关闭
	file.close();
	return true;
}

// 追加
bool zhu::CFileHelper::AppendClass(CClass & obj)
{
	//打开文件
	std::fstream file(CLASS_FILE_NAME, std::ios::app | std::ios::binary);
	if (!file)
	{
		return false;
	}

	//写数据
	file.write((char *)&(obj.m_nClassNo), sizeof(int));								//写出班级号
	file.write((char *)&(obj.m_szClassName), sizeof(obj.m_szClassName));			//写出班级名
	int nSize = obj.m_lstStudentNo.size();
	file.write((char *)&nSize, sizeof(int));										//写出学号数
	for (std::list<int>::iterator itStudentNo = obj.m_lstStudentNo.begin();			//遍历写出所有学号
		itStudentNo != obj.m_lstStudentNo.end();
		itStudentNo++)
	{
		file.write((char *)&(*itStudentNo), sizeof(int));
	}

	//关闭
	file.close();
	return true;
}
bool zhu::CFileHelper::AppendGrade(CGrade & obj)
{
	//打开文件
	std::fstream file(GRADE_FILE_NAME, std::ios::app | std::ios::binary);
	if (!file)
	{
		return false;
	}

	//写数据
	file.write((char *)&(obj.m_nGradeNo), sizeof(int));								//写出年段号
	file.write((char *)&(obj.m_szGradeName), sizeof(obj.m_szGradeName));			//写出年段名
	int nSize = obj.m_lstClassNo.size();
	file.write((char *)&nSize, sizeof(int));										//写出班级数
	for (std::list<int>::iterator itClassNo = obj.m_lstClassNo.begin();			//遍历写出所有班级
		itClassNo != obj.m_lstClassNo.end();
		itClassNo++)
	{
		file.write((char *)&(*itClassNo), sizeof(int));
	}

	//关闭
	file.close();
	return true;
}

// 读取
std::list<zhu::CClass>* zhu::CFileHelper::ReadClassAll()
{
	std::list<CClass>* list = new std::list<CClass>();

	//打开文件
	std::ifstream file(CLASS_FILE_NAME, std::ios::in | std::ios::binary);
	if (!file)
	{
		return list;
	}

	//读数据
	CClass item;
	int nSize;
	int nNo;
	
	while (file.read((char *)&(item.m_nClassNo), sizeof(int)))							//读出班级号
	{		
		file.read((char *)&(item.m_szClassName), sizeof(item.m_szClassName));			//读出班级名
		file.read((char *)&nSize, sizeof(int));											//读出学号数
		for (int i = 0; i < nSize; i++)
		{
			file.read((char *)&nNo, sizeof(int));
			item.m_lstStudentNo.push_back(nNo);
		}
		list->push_back(item);
	}

	//关闭
	file.close();
	return list;
}
std::list<zhu::CGrade>* zhu::CFileHelper::ReadGradeAll()
{
	std::list<CGrade>* list = new std::list<CGrade>();

	//打开文件
	std::ifstream file(GRADE_FILE_NAME, std::ios::in | std::ios::binary);
	if (!file)
	{
		return list;
	}

	//读数据
	CGrade item;
	int nSize;
	int nNo;

	while (file.read((char *)&(item.m_nGradeNo), sizeof(int)))							//读出班级号
	{
		file.read((char *)&(item.m_szGradeName), sizeof(item.m_szGradeName));			//读出班级名
		file.read((char *)&nSize, sizeof(int));											//读出学号数
		for (int i = 0; i < nSize; i++)
		{
			file.read((char *)&nNo, sizeof(int));
			item.m_lstClassNo.push_back(nNo);
		}
		list->push_back(item);
	}

	//关闭
	file.close();
	return list;
}





