///////////////////////////////////////
// ���Կ�Ŀ������
//////////////////////////////////////
#include "Manager.h"
void zhu::CTestSubjectManager::Print(std::vector<zhu::CTestSubject>* vector)
{
	std::vector<zhu::CTestSubject>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		std::cout << std::left << std::setw(10)
			<< std::setw(10) << it->m_nTestSubjectNo
			<< std::setw(10) << it->m_szTestSubjectName
			<< std::setw(10) << it->m_szCourseName
			<< std::endl;
	}
}
bool zhu::CTestSubjectManager::OnDelete(std::vector<zhu::CTestSubject>& vecTestSubject, 
	std::vector<zhu::CTestSubject>::iterator& itFind)
{
	vecTestSubject.erase(itFind);																	//�Ƴ�		
	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, vecTestSubject);						//����
	return false;
}
bool zhu::CTestSubjectManager::OnUpdate(std::vector<zhu::CTestSubject>& vecTestSubject,
	std::vector<zhu::CTestSubject>::iterator& itFind)
{
	std::string strTestSubjectName;
	std::string strCourseName;

	std::cout << "���뿼������:";
	std::cin >> strTestSubjectName;
	std::cout << "���뿼�Կ�Ŀ:";
	std::cin >> strCourseName;
	if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
		throw NotFoundException("�γ�");

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	strcpy(itFind->m_szTestSubjectName, strTestSubjectName.c_str());
	strcpy(itFind->m_szCourseName, strCourseName.c_str());

	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, vecTestSubject);						//����

	return false;
}

void zhu::CTestSubjectManager::Add()
{
	int nTestSubjectNo;
	std::string strTestSubjectName;
	std::string strCourseName;

	std::cout << "���뿼�Ա��:";
	std::cin >> nTestSubjectNo;
	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw KeyUniqueException("���Ա��");
	std::cout << "���뿼������:";
	std::cin >> strTestSubjectName;
	std::cout << "���뿼�Կ�Ŀ:";
	std::cin >> strCourseName;
	if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
		throw NotFoundException("�γ�");

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CTestSubject objTestSubject(nTestSubjectNo, strTestSubjectName.c_str(), strCourseName.c_str());
	CFileHelper::Append<CTestSubject>(TEST_SUBJECT_FILE_NAME, objTestSubject);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CTestSubjectManager::Del()
{
	int nTestSubjectNo;
	std::cout << "���뿼�Ա��:";
	std::cin >> nTestSubjectNo;

	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CTestSubjectManager::Update()
{
	int nTestSubjectNo;
	std::cout << "���뿼�Ա��:";
	std::cin >> nTestSubjectNo;

	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CTestSubjectManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "���Ա��"
		<< std::setw(10) << "��������"
		<< std::setw(10) << "���Կ�Ŀ"
		<< std::endl;

	std::vector<CTestSubject>* vector = CFileHelper::ReadAll<CTestSubject>(TEST_SUBJECT_FILE_NAME);
	Print(vector);
	delete vector;
}



