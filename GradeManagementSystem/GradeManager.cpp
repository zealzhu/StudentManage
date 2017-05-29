///////////////////////////////////////
// �꼶������
//////////////////////////////////////
#include "Manager.h"

void zhu::CGradeManager::Print(std::list<zhu::CGrade>* list)
{	
	std::list<zhu::CGrade>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		std::cout << std::left
			<< std::setw(10) << it->m_nGradeNo
			<< std::setw(10) << it->m_szGradeName
			<< std::endl;
	}
}

bool zhu::CGradeManager::OnDelete(std::list<zhu::CGrade>& lstGrade, std::list<zhu::CGrade>::iterator& itFind)
{
	lstGrade.erase(itFind);												//�Ƴ�		
	CFileHelper::SaveGrade(lstGrade);									//����
	return false;
}
bool zhu::CGradeManager::OnUpdate(std::list<zhu::CGrade>& lstGrade, std::list<zhu::CGrade>::iterator& itFind)
{
	int nGradeNo;
	std::string strGradeName;

	std::cout << "��������κ�:";
	std::cin >> nGradeNo;
	if (IManager::Search<CGrade>(nGradeNo, GRADE_FILE_NAME, CGrade::compareGradeNo, NULL))
		throw KeyUniqueException("��κ�");
	std::cout << "�����������:";
	std::cin >> strGradeName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	itFind->m_nGradeNo = nGradeNo;
	strcpy(itFind->m_szGradeName, strGradeName.c_str());
	CFileHelper::SaveGrade(lstGrade);

	return false;
}

void zhu::CGradeManager::Add()
{
	int nGradeNo;
	std::string strGradeName;

	std::cout << "������κ�:";
	std::cin >> nGradeNo;
	if (IManager::Search<CGrade>(nGradeNo, GRADE_FILE_NAME, CGrade::compareGradeNo, NULL))
		throw KeyUniqueException("��κ�");
	std::cout << "���������:";
	std::cin >> strGradeName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CGrade objGrade(nGradeNo, strGradeName.c_str());
	CFileHelper::AppendGrade(objGrade);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CGradeManager::Del()
{
	int nStudentNo;
	std::cout << "����༶��:";
	std::cin >> nStudentNo;

	if (IManager::Search<CGrade>(nStudentNo, GRADE_FILE_NAME, CGrade::compareGradeNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CGradeManager::Update()
{
	int nStudentNo;
	std::cout << "����༶��:";
	std::cin >> nStudentNo;

	if (IManager::Search<CGrade>(nStudentNo, GRADE_FILE_NAME, CGrade::compareGradeNo, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CGradeManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "��κ�"
		<< std::setw(10) << "�����"
		<< std::endl;

	std::list<CGrade>* list = CFileHelper::ReadGradeAll();
	Print(list);
	delete list;
}

