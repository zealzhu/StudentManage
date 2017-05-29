///////////////////////////////////////
// 班级管理方法
//////////////////////////////////////
#include "Manager.h"

void zhu::CClassManager::Print(std::vector<zhu::CClass>* vector)
{
	std::cout << std::left
		<< std::setw(10) << "班级号"
		<< std::setw(10) << "班级名"
		<< std::endl;

	std::vector<zhu::CClass>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		std::cout << std::left
			<< std::setw(10) << it->m_nClassNo
			<< std::setw(10) << it->m_szClassName
			<< std::endl;
	}
}

// 回调方法
bool zhu::CClassManager::OnDelete(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	vecClass.erase(itFind);															//移除		
	CFileHelper<CClass>::SaveHasVector(CLASS_FILE_NAME, vecClass);					//保存
	return false;
}
bool zhu::CClassManager::OnUpdate(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	std::string strClassName;

	std::cout << "输入新班级名:";
	std::cin >> strClassName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	strcpy(itFind->m_szClassName, strClassName.c_str());
	CFileHelper<CClass>::SaveHasVector(CLASS_FILE_NAME, vecClass);					//保存

	return false;
}

// 重写方法
void zhu::CClassManager::Add()
{
	int nClassNo;
	std::string strClassName;

	std::cout << "输入班级号:";
	std::cin >> nClassNo;
	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, NULL))
		throw KeyUniqueException("班级号");
	std::cout << "输入班级名:";
	std::cin >> strClassName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CClass objClass(nClassNo, strClassName.c_str());
	CFileHelper<CClass>::AppendHasVector(CLASS_FILE_NAME, objClass);
	std::cout << "添加成功" << std::endl;
}
void zhu::CClassManager::Del()
{
	int nStudentNo;
	std::cout << "输入班级号:";
	std::cin >> nStudentNo;

	if (IManager::Search<CClass>(nStudentNo, CLASS_FILE_NAME, CClass::compareClassNo, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
}
void zhu::CClassManager::Update()
{
	int nStudentNo;
	std::cout << "输入班级号:";
	std::cin >> nStudentNo;

	if (IManager::Search<CClass>(nStudentNo, CLASS_FILE_NAME, CClass::compareClassNo, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}
void zhu::CClassManager::Search()
{
	std::vector<CClass>* vector = CFileHelper<CClass>::ReadHasVectorAll(CLASS_FILE_NAME);
	Print(vector);
	delete vector;
}