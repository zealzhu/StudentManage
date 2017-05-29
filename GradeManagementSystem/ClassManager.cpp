///////////////////////////////////////
// �༶������
//////////////////////////////////////
#include "Manager.h"

void zhu::CClassManager::Print(std::vector<zhu::CClass>* vector)
{
	std::cout << std::left
		<< std::setw(10) << "�༶��"
		<< std::setw(10) << "�༶��"
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

// �ص�����
bool zhu::CClassManager::OnDelete(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	vecClass.erase(itFind);															//�Ƴ�		
	CFileHelper<CClass>::SaveHasVector(CLASS_FILE_NAME, vecClass);					//����
	return false;
}
bool zhu::CClassManager::OnUpdate(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	std::string strClassName;

	std::cout << "�����°༶��:";
	std::cin >> strClassName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	strcpy(itFind->m_szClassName, strClassName.c_str());
	CFileHelper<CClass>::SaveHasVector(CLASS_FILE_NAME, vecClass);					//����

	return false;
}

// ��д����
void zhu::CClassManager::Add()
{
	int nClassNo;
	std::string strClassName;

	std::cout << "����༶��:";
	std::cin >> nClassNo;
	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, NULL))
		throw KeyUniqueException("�༶��");
	std::cout << "����༶��:";
	std::cin >> strClassName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CClass objClass(nClassNo, strClassName.c_str());
	CFileHelper<CClass>::AppendHasVector(CLASS_FILE_NAME, objClass);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CClassManager::Del()
{
	int nStudentNo;
	std::cout << "����༶��:";
	std::cin >> nStudentNo;

	if (IManager::Search<CClass>(nStudentNo, CLASS_FILE_NAME, CClass::compareClassNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CClassManager::Update()
{
	int nStudentNo;
	std::cout << "����༶��:";
	std::cin >> nStudentNo;

	if (IManager::Search<CClass>(nStudentNo, CLASS_FILE_NAME, CClass::compareClassNo, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CClassManager::Search()
{
	std::vector<CClass>* vector = CFileHelper<CClass>::ReadHasVectorAll(CLASS_FILE_NAME);
	Print(vector);
	delete vector;
}