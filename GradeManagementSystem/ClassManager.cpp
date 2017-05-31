///////////////////////////////////////
// 班级管理方法
//////////////////////////////////////
#include "Manager.h"

void zhu::CClassManager::Print(std::vector<zhu::CClass>* vector)
{
	std::cout << std::left
		<< std::setw(10) << "班级号"
		<< std::setw(10) << "班级名"
		<< std::setw(10) << "学号集合"
		<< std::endl;

	std::vector<zhu::CClass>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		std::cout << std::left
			<< std::setw(10) << it->m_nClassNo
			<< std::setw(10) << it->m_szClassName
			<< "{ ";
		for (int i = 0; i < it->m_vecStudentNo.size(); i++) 
		{
			std::cout << it->m_vecStudentNo[i] << " ";
		}
		std::cout << "}" << std::endl;
	}
}

// 回调方法
bool zhu::CClassManager::OnDelete(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	for (int i = 0; i < itFind->m_vecStudentNo.size(); i++) 
	{
		//遍历删除所有学生
		IManager::Search<CStudent>(itFind->m_vecStudentNo[i], STUDENT_FILE_NAME, 
			CStudent::compareStudentNo, OnRemoveStudent);
	}
	vecClass.erase(itFind);															//移除		
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);					//保存
	return false;
}
bool zhu::CClassManager::OnUpdate(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	std::string strClassName;

	std::cout << "输入新班级名:";
	std::cin >> strClassName;
	CheckInput();

	SetAndCheckCharParam(itFind->m_szClassName, strClassName.c_str(), sizeof(itFind->m_szClassName));
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);					//保存

	return false;
}

bool zhu::CClassManager::OnRemoveStudent(std::vector<zhu::CStudent>& vecStudent, 
	std::vector<zhu::CStudent>::iterator& itFind)
{
	//删除学生
	vecStudent.erase(itFind);
	zhu::CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);
	return false;
}

// 重写方法
void zhu::CClassManager::Add()
{
	int nClassNo;
	std::string strClassName;

	std::cout << "输入班级号:";
	std::cin >> nClassNo;
	CheckInput();
	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, NULL))
		throw KeyUniqueException("班级号");
	std::cout << "输入班级名:";
	std::cin >> strClassName;
	SetAndCheckCharParam(NULL, strClassName.c_str(), sizeof(CClass::m_szClassName));

	CClass objClass(nClassNo, strClassName.c_str());
	CFileHelper::AppendHasVector<CClass>(CLASS_FILE_NAME, objClass);
	std::cout << "添加成功" << std::endl;
}
void zhu::CClassManager::Del()
{
	int nClassNo;
	std::cout << "输入班级号:";
	std::cin >> nClassNo;
	CheckInput();

	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
}
void zhu::CClassManager::Update()
{
	int nClassNo;
	std::cout << "输入班级号:";
	std::cin >> nClassNo;
	CheckInput();

	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}
void zhu::CClassManager::Search()
{
	std::vector<CClass>* vector = CFileHelper::ReadHasVectorAll<CClass>(CLASS_FILE_NAME);
	Print(vector);
	delete vector;
}