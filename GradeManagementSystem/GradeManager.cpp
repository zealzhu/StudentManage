///////////////////////////////////////
// 年级管理方法
//////////////////////////////////////
#include "Manager.h"

void zhu::CGradeManager::Print(std::vector<zhu::CGrade>* vector)
{	
	std::vector<zhu::CGrade>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		std::cout << std::left
			<< std::setw(10) << it->m_nGradeNo
			<< std::setw(10) << it->m_szGradeName
			<< std::endl;
	}
}

bool zhu::CGradeManager::OnDelete(std::vector<zhu::CGrade>& vecGrade, std::vector<zhu::CGrade>::iterator& itFind)
{
	vecGrade.erase(itFind);												//移除		
	CFileHelper<CGrade>::SaveHasVector(GRADE_FILE_NAME, vecGrade);									//保存
	return false;
}
bool zhu::CGradeManager::OnUpdate(std::vector<zhu::CGrade>& vecGrade, std::vector<zhu::CGrade>::iterator& itFind)
{
	std::string strGradeName;

	std::cout << "输入新年段名:";
	std::cin >> strGradeName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	strcpy(itFind->m_szGradeName, strGradeName.c_str());
	CFileHelper<CGrade>::SaveHasVector(GRADE_FILE_NAME, vecGrade);

	return false;
}

void zhu::CGradeManager::Add()
{
	int nGradeNo;
	std::string strGradeName;

	std::cout << "输入年段号:";
	std::cin >> nGradeNo;
	if (IManager::Search<CGrade>(nGradeNo, GRADE_FILE_NAME, CGrade::compareGradeNo, NULL))
		throw KeyUniqueException("年段号");
	std::cout << "输入年段名:";
	std::cin >> strGradeName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CGrade objGrade(nGradeNo, strGradeName.c_str());
	CFileHelper<CGrade>::AppendHasVector(GRADE_FILE_NAME, objGrade);
	std::cout << "添加成功" << std::endl;
}
void zhu::CGradeManager::Del()
{
	int nStudentNo;
	std::cout << "输入班级号:";
	std::cin >> nStudentNo;

	if (IManager::Search<CGrade>(nStudentNo, GRADE_FILE_NAME, CGrade::compareGradeNo, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
}
void zhu::CGradeManager::Update()
{
	int nStudentNo;
	std::cout << "输入班级号:";
	std::cin >> nStudentNo;

	if (IManager::Search<CGrade>(nStudentNo, GRADE_FILE_NAME, CGrade::compareGradeNo, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}
void zhu::CGradeManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "年段号"
		<< std::setw(10) << "年段名"
		<< std::endl;

	std::vector<CGrade>* vector = CFileHelper<CGrade>::ReadHasVectorAll(GRADE_FILE_NAME);
	Print(vector);
	delete vector;
}

