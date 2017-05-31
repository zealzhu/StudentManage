///////////////////////////////////////
// �༶������
//////////////////////////////////////
#include "Manager.h"

void zhu::CClassManager::Print(std::vector<zhu::CClass>* vector)
{
	std::cout << std::left
		<< std::setw(10) << "�༶��"
		<< std::setw(10) << "�༶��"
		<< std::setw(10) << "ѧ�ż���"
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

// �ص�����
bool zhu::CClassManager::OnDelete(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	for (int i = 0; i < itFind->m_vecStudentNo.size(); i++) 
	{
		//����ɾ������ѧ��
		IManager::Search<CStudent>(itFind->m_vecStudentNo[i], STUDENT_FILE_NAME, 
			CStudent::compareStudentNo, OnRemoveStudent);
	}
	vecClass.erase(itFind);															//�Ƴ�		
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);					//����
	return false;
}
bool zhu::CClassManager::OnUpdate(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	std::string strClassName;

	std::cout << "�����°༶��:";
	std::cin >> strClassName;
	CheckInput();

	SetAndCheckCharParam(itFind->m_szClassName, strClassName.c_str(), sizeof(itFind->m_szClassName));
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);					//����

	return false;
}

bool zhu::CClassManager::OnRemoveStudent(std::vector<zhu::CStudent>& vecStudent, 
	std::vector<zhu::CStudent>::iterator& itFind)
{
	//ɾ��ѧ��
	vecStudent.erase(itFind);
	zhu::CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);
	return false;
}

// ��д����
void zhu::CClassManager::Add()
{
	int nClassNo;
	std::string strClassName;

	std::cout << "����༶��:";
	std::cin >> nClassNo;
	CheckInput();
	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, NULL))
		throw KeyUniqueException("�༶��");
	std::cout << "����༶��:";
	std::cin >> strClassName;
	SetAndCheckCharParam(NULL, strClassName.c_str(), sizeof(CClass::m_szClassName));

	CClass objClass(nClassNo, strClassName.c_str());
	CFileHelper::AppendHasVector<CClass>(CLASS_FILE_NAME, objClass);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CClassManager::Del()
{
	int nClassNo;
	std::cout << "����༶��:";
	std::cin >> nClassNo;
	CheckInput();

	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CClassManager::Update()
{
	int nClassNo;
	std::cout << "����༶��:";
	std::cin >> nClassNo;
	CheckInput();

	if (IManager::Search<CClass>(nClassNo, CLASS_FILE_NAME, CClass::compareClassNo, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CClassManager::Search()
{
	std::vector<CClass>* vector = CFileHelper::ReadHasVectorAll<CClass>(CLASS_FILE_NAME);
	Print(vector);
	delete vector;
}