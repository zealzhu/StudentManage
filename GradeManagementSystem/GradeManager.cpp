///////////////////////////////////////
// �꼶������
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
	vecGrade.erase(itFind);												//�Ƴ�		
	CFileHelper::SaveHasVector<CGrade>(GRADE_FILE_NAME, vecGrade);									//����
	return false;
}
bool zhu::CGradeManager::OnUpdate(std::vector<zhu::CGrade>& vecGrade, std::vector<zhu::CGrade>::iterator& itFind)
{
	std::string strGradeName;

	std::cout << "�����������:";
	std::cin >> strGradeName;
	SetAndCheckCharParam(itFind->m_szGradeName, strGradeName.c_str(), sizeof(itFind->m_szGradeName));
	
	CFileHelper::SaveHasVector<CGrade>(GRADE_FILE_NAME, vecGrade);

	return false;
}

void zhu::CGradeManager::Add()
{
	//���
	int nGradeNo;
	std::string strGradeName;

	std::cout << "������κ�:";
	std::cin >> nGradeNo;
	CheckInput();
	//����Ƿ����
	if (IManager::Search<CGrade>(nGradeNo, GRADE_FILE_NAME, CGrade::compareGradeNo, NULL))
		throw KeyUniqueException("��κ�");
	std::cout << "���������:";
	std::cin >> strGradeName;
	SetAndCheckCharParam(NULL, strGradeName.c_str(), sizeof(CGrade::m_szGradeName));

	CGrade objGrade(nGradeNo, strGradeName.c_str());
	CFileHelper::AppendHasVector<CGrade>(GRADE_FILE_NAME, objGrade);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CGradeManager::Del()
{
	int nGradeNo;
	std::cout << "������κ�:";
	std::cin >> nGradeNo;
	CheckInput();

	if (IManager::Search<CGrade>(nGradeNo, GRADE_FILE_NAME, CGrade::compareGradeNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CGradeManager::Update()
{
	int nGradeNo;
	std::cout << "������κ�:";
	std::cin >> nGradeNo;
	CheckInput();

	if (IManager::Search<CGrade>(nGradeNo, GRADE_FILE_NAME, CGrade::compareGradeNo, OnUpdate))
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

	std::vector<CGrade>* vector = CFileHelper::ReadHasVectorAll<CGrade>(GRADE_FILE_NAME);
	Print(vector);
	delete vector;
}

