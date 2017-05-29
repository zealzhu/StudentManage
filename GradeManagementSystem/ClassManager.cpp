///////////////////////////////////////
// �༶������
//////////////////////////////////////
#include "Manager.h"

void zhu::CClassManager::Print(std::list<zhu::CClass>* list)
{
	std::cout << std::left
		<< std::setw(10) << "�༶��"
		<< std::setw(10) << "�༶��"
		<< std::endl;

	std::list<zhu::CClass>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		std::cout << std::left
			<< std::setw(10) << it->m_nClassNo
			<< std::setw(10) << it->m_szClassName
			<< std::endl;
	}
}

// �ص�����
bool zhu::CClassManager::OnDelete(std::list<zhu::CClass>& lstClass, std::list<zhu::CClass>::iterator& itFind)
{
	lstClass.erase(itFind);												//�Ƴ�		
	CFileHelper::SaveClass(lstClass);									//����
	return false;
}
bool zhu::CClassManager::OnUpdate(std::list<zhu::CClass>& lstClass, std::list<zhu::CClass>::iterator& itFind)
{
	int nClassNo;
	std::string strClassName;

	std::cout << "�����°༶��:";
	std::cin >> nClassNo;
	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, NULL))
		throw KeyUniqueException("�༶��");
	std::cout << "�����°༶��:";
	std::cin >> strClassName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	itFind->m_nClassNo = nClassNo;
	strcpy(itFind->m_szClassName, strClassName.c_str());
	CFileHelper::SaveClass(lstClass);					//����

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
	CFileHelper::AppendClass(objClass);
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
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CClassManager::Search()
{
	std::list<CClass>* list = CFileHelper::ReadClassAll();
	Print(list);
	delete list;
}