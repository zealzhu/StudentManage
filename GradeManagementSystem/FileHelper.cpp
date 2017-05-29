#include "FileHelper.h"



// ����
bool zhu::CFileHelper::SaveClass(std::list<CClass>& lst)
{
	//���ļ�
	std::ofstream file(CLASS_FILE_NAME, std::ios::out | std::ios::binary);
	if (!file) {
		return false;
	}

	//д����
	for (std::list<CClass>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		CClass& item = *it;
		file.write((char *)&(item.m_nClassNo), sizeof(int));							//д���༶��
		file.write((char *)&(item.m_szClassName), sizeof(item.m_szClassName));		//д���༶��

		int nSize = item.m_lstStudentNo.size();
		file.write((char *)&nSize, sizeof(int));					//д��ѧ����
		for (std::list<int>::iterator itStudentNo = item.m_lstStudentNo.begin();	//����д������ѧ��
			itStudentNo != item.m_lstStudentNo.end(); 
			itStudentNo++)
		{
			file.write((char *)&(*itStudentNo), sizeof(int));	
		}	
	}

	//�ر�
	file.close();
	return true;
}
bool zhu::CFileHelper::SaveGrade(std::list<CGrade>& lst)
{
	//���ļ�
	std::ofstream file(GRADE_FILE_NAME, std::ios::out | std::ios::binary);
	if (!file) {
		return false;
	}

	//д����
	for (std::list<CGrade>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		CGrade& item = *it;
		file.write((char *)&(item.m_nGradeNo), sizeof(int));							//д���༶��
		file.write((char *)&(item.m_szGradeName), sizeof(item.m_szGradeName));			//д���༶��

		int nSize = item.m_lstClassNo.size();
		file.write((char *)&nSize, sizeof(int));										//д��ѧ����
		for (std::list<int>::iterator itClassNo = item.m_lstClassNo.begin();			//����д������ѧ��
			itClassNo != item.m_lstClassNo.end();
			itClassNo++)
		{
			file.write((char *)&(*itClassNo), sizeof(int));
		}
	}

	//�ر�
	file.close();
	return true;
}

// ׷��
bool zhu::CFileHelper::AppendClass(CClass & obj)
{
	//���ļ�
	std::fstream file(CLASS_FILE_NAME, std::ios::app | std::ios::binary);
	if (!file)
	{
		return false;
	}

	//д����
	file.write((char *)&(obj.m_nClassNo), sizeof(int));								//д���༶��
	file.write((char *)&(obj.m_szClassName), sizeof(obj.m_szClassName));			//д���༶��
	int nSize = obj.m_lstStudentNo.size();
	file.write((char *)&nSize, sizeof(int));										//д��ѧ����
	for (std::list<int>::iterator itStudentNo = obj.m_lstStudentNo.begin();			//����д������ѧ��
		itStudentNo != obj.m_lstStudentNo.end();
		itStudentNo++)
	{
		file.write((char *)&(*itStudentNo), sizeof(int));
	}

	//�ر�
	file.close();
	return true;
}
bool zhu::CFileHelper::AppendGrade(CGrade & obj)
{
	//���ļ�
	std::fstream file(GRADE_FILE_NAME, std::ios::app | std::ios::binary);
	if (!file)
	{
		return false;
	}

	//д����
	file.write((char *)&(obj.m_nGradeNo), sizeof(int));								//д����κ�
	file.write((char *)&(obj.m_szGradeName), sizeof(obj.m_szGradeName));			//д�������
	int nSize = obj.m_lstClassNo.size();
	file.write((char *)&nSize, sizeof(int));										//д���༶��
	for (std::list<int>::iterator itClassNo = obj.m_lstClassNo.begin();			//����д�����а༶
		itClassNo != obj.m_lstClassNo.end();
		itClassNo++)
	{
		file.write((char *)&(*itClassNo), sizeof(int));
	}

	//�ر�
	file.close();
	return true;
}

// ��ȡ
std::list<zhu::CClass>* zhu::CFileHelper::ReadClassAll()
{
	std::list<CClass>* list = new std::list<CClass>();

	//���ļ�
	std::ifstream file(CLASS_FILE_NAME, std::ios::in | std::ios::binary);
	if (!file)
	{
		return list;
	}

	//������
	CClass item;
	int nSize;
	int nNo;
	
	while (file.read((char *)&(item.m_nClassNo), sizeof(int)))							//�����༶��
	{		
		file.read((char *)&(item.m_szClassName), sizeof(item.m_szClassName));			//�����༶��
		file.read((char *)&nSize, sizeof(int));											//����ѧ����
		for (int i = 0; i < nSize; i++)
		{
			file.read((char *)&nNo, sizeof(int));
			item.m_lstStudentNo.push_back(nNo);
		}
		list->push_back(item);
	}

	//�ر�
	file.close();
	return list;
}
std::list<zhu::CGrade>* zhu::CFileHelper::ReadGradeAll()
{
	std::list<CGrade>* list = new std::list<CGrade>();

	//���ļ�
	std::ifstream file(GRADE_FILE_NAME, std::ios::in | std::ios::binary);
	if (!file)
	{
		return list;
	}

	//������
	CGrade item;
	int nSize;
	int nNo;

	while (file.read((char *)&(item.m_nGradeNo), sizeof(int)))							//�����༶��
	{
		file.read((char *)&(item.m_szGradeName), sizeof(item.m_szGradeName));			//�����༶��
		file.read((char *)&nSize, sizeof(int));											//����ѧ����
		for (int i = 0; i < nSize; i++)
		{
			file.read((char *)&nNo, sizeof(int));
			item.m_lstClassNo.push_back(nNo);
		}
		list->push_back(item);
	}

	//�ر�
	file.close();
	return list;
}





