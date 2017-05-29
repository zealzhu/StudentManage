///////////////////////////////////////
// ѧ���ɼ�������
//////////////////////////////////////
#include "Manager.h"

//	���ҷ��� - ͨ��ѧ�źͰ༶����
bool zhu::CScoreManager::Search(int nNo, const char * szClassName,
	typename COMPARE_BY_INT_AND_CHAR compare, typename OnSearch<CScore>::SEARCH_SUCCESS callback)
{
	bool bFind = false;

	//��ȡ��Ϣ
	std::list<CScore>* list = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//����
	std::list<CScore>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		if (compare(nNo, szClassName, *it))
		{
			bFind = true;
			if (!callback(*list, it))
				break;
		}
	}
	delete list;

	return bFind;
}
//	���ҷ��� - ͨ�������Ͱ༶����
bool zhu::CScoreManager::Search(const char * szStudentName, const char * szClassName,
	typename COMPARE_BY_CHAR_AND_CHAR compare, typename OnSearch<CScore>::SEARCH_SUCCESS callback)
{
	bool bFind = false;

	//��ȡ��Ϣ
	std::list<CScore>* list = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//����
	std::list<CScore>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		if (compare(szStudentName, szClassName, *it))
		{
			bFind = true;
			if (!callback(*list, it))
				break;
		}
	}
	delete list;

	return bFind;
}

//	ɾ���ص�
bool zhu::CScoreManager::OnDelete(std::list<zhu::CScore>& lstScore, 
	std::list<zhu::CScore>::iterator& itFind)
{
	lstScore.erase(itFind);
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, lstScore);
	return false;
}

//	���»ص�
bool zhu::CScoreManager::OnUpdate(std::list<zhu::CScore>& lstScore, 
	std::list<zhu::CScore>::iterator& itFind)
{
	int nStudentNo;
	int nTestSubjectNo;
	float fScore;
	std::string strClassName;
	std::string strStuentName;
	std::string strCourseName;

	std::cout << "�����¿��Ա��:";
	std::cin >> nTestSubjectNo;
	std::cout << "������ѧ��:";
	std::cin >> nStudentNo;
	std::cout << "����������:";
	std::cin >> strStuentName;
	std::cout << "�����°༶:";
	std::cin >> strClassName;
	std::cout << "�����¿γ���:";
	std::cin >> strCourseName;
	std::cout << "�����³ɼ�:";
	std::cin >> fScore;

	itFind->m_nTestSubjectNo = nTestSubjectNo;
	itFind->m_nStudentNo = nStudentNo;
	strcpy(itFind->m_szStudentName, strStuentName.c_str());
	strcpy(itFind->m_szClassName, strClassName.c_str());
	strcpy(itFind->m_szCourseName, strCourseName.c_str());
	itFind->m_fScore = fScore;

	CFileHelper::Save<CScore>(SCORE_FILE_NAME, lstScore);
	return false;
}

//	���һص�
bool zhu::CScoreManager::OnSearchByNoAndCourseName(std::list<zhu::CScore>& lstScore
	, std::list<zhu::CScore>::iterator& itFind)
{
	std::list<zhu::CScore> lstTemp(1, *itFind);
	Print(&lstTemp);
	return false;
}
bool zhu::CScoreManager::OnSearchByNameAndCourseName(std::list<zhu::CScore>& lstScore,
	std::list<zhu::CScore>::iterator& itFind)
{
	std::list<zhu::CScore> lstTemp(1, *itFind);
	Print(&lstTemp);
	return false;
}

//	��ӡ
void zhu::CScoreManager::Print(std::list<zhu::CScore>* list)
{
	std::cout << std::left
		<< std::setw(10) << "���Ա��"
		<< std::setw(10) << "ѧ��"
		<< std::setw(10) << "����"
		<< std::setw(10) << "�༶"
		<< std::setw(10) << "�γ���"
		<< std::setw(10) << "�ɼ�"
		<< std::endl;
	
	std::list<zhu::CScore>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		std::cout << std::left
			<< std::setw(10) << it->m_nTestSubjectNo
			<< std::setw(10) << it->m_nStudentNo
			<< std::setw(10) << it->m_szStudentName
			<< std::setw(10) << it->m_szClassName
			<< std::setw(10) << it->m_szCourseName
			<< std::setw(10) << it->m_fScore
			<< std::endl;
	}
}
void zhu::CScoreManager::Statistics()
{
	std::cout << "ͳ�ƹ���" << std::endl;
}

//	��д
void zhu::CScoreManager::Add()
{
	int nStudentNo;
	int nTestSubjectNo;
	float fScore;
	std::string strClassName;
	std::string strStuentName;
	std::string strCourseName;

	std::cout << "���뿼�Ա��:";
	std::cin >> nTestSubjectNo;
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;
	std::cout << "��������:";
	std::cin >> strStuentName;
	std::cout << "����༶:";
	std::cin >> strClassName;
	std::cout << "����γ���:";
	std::cin >> strCourseName;
	std::cout << "����ɼ�:";
	std::cin >> fScore;
	
	CScore objScore(nTestSubjectNo, nStudentNo, strStuentName.c_str(),
		strCourseName.c_str(), strClassName.c_str(), fScore);
	CFileHelper::Append<CScore>(SCORE_FILE_NAME, objScore);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CScoreManager::Del()
{
	DeleteMenu();
}
void zhu::CScoreManager::Update()
{
	UpdateMenu();
}
void zhu::CScoreManager::Search()
{
	SearchMenu();
}

//	˽�з���
void zhu::CScoreManager::UpdateMenu()
{
	int nChoose;
	std::cout << ">�޸�ѧ���ɼ��������밴�������������" << std::endl;
	std::cout << "	  1.ͨ��ѧ�źͿγ̺��޸�" << std::endl;
	std::cout << "	  2.ͨ�������Ϳγ̺��޸�" << std::endl;

	std::cin >> nChoose;
	system("cls");		//����
	switch (nChoose)
	{
	case 1:
		UpdateByNoAndCourseName();
		break;
	case 2:
		UpdateByNameAndCourseName();
		break;
	default:
		break;
	}
}
void zhu::CScoreManager::UpdateByNoAndCourseName()
{
	int nStuentNo;
	std::string strCourseName;
	std::cout << "����ѧ��:";
	std::cin >> nStuentNo;
	std::cout << "����γ���:";
	std::cin >> strCourseName;

	if (Search(nStuentNo, strCourseName.c_str(),
		CScore::compareStudentNoAndCourseName, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CScoreManager::UpdateByNameAndCourseName()
{
	std::string strStudentName;
	std::string strCourseName;
	std::cout << "��������:";
	std::cin >> strStudentName;
	std::cout << "����γ���:";
	std::cin >> strCourseName;

	if (Search(strStudentName.c_str(), strCourseName.c_str(),
		CScore::compareStudentNameAndCourseName, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}

void zhu::CScoreManager::DeleteMenu()
{
	int nChoose;
	std::cout << ">ɾ��ѧ���ɼ��������밴�������������" << std::endl;
	std::cout << "	  1.ͨ��ѧ�źͿγ̺�ɾ��" << std::endl;
	std::cout << "	  2.ͨ�������Ϳγ̺�ɾ��" << std::endl;

	std::cin >> nChoose;
	system("cls");		//����
	switch (nChoose)
	{
	case 1:
		DeleteByNoAndCourseName();
		break;
	case 2:
		DeleteByNameAndCourseName();
		break;
	default:
		break;
	}
}
void zhu::CScoreManager::DeleteByNoAndCourseName()
{
	int nStuentNo;
	std::string strCourseName;
	std::cout << "����ѧ��:";
	std::cin >> nStuentNo;
	std::cout << "����γ���:";
	std::cin >> strCourseName;

	if (Search(nStuentNo, strCourseName.c_str(),
		CScore::compareStudentNoAndCourseName, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CScoreManager::DeleteByNameAndCourseName()
{
	std::string strStudentName;
	std::string strCourseName;
	std::cout << "��������:";
	std::cin >> strStudentName;
	std::cout << "����γ���:";
	std::cin >> strCourseName;

	if (Search(strStudentName.c_str(), strCourseName.c_str(),
		CScore::compareStudentNameAndCourseName, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}

void zhu::CScoreManager::SearchAll()
{
	std::list<CScore>* list = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);
	Print(list);
	delete list;
}
void zhu::CScoreManager::SearchMenu()
{
	int nChoose;
	std::cout << ">��ѯѧ���ɼ��������밴�������������" << std::endl;
	std::cout << "	  1.ͨ��ѧ�źͿγ̺Ų���" << std::endl;
	std::cout << "	  2.ͨ�������Ϳγ̺Ų���" << std::endl;
	std::cout << "	  3.��ѯ����" << std::endl;

	std::cin >> nChoose;
	system("cls");		//����

	switch (nChoose)
	{
	case 1:
		SearchByNoAndCourseName();
		break;
	case 2:
		SearchByNameAndCourseName();
		break;
	case 3:
		SearchAll();
	default:
		break;
	}
}
void zhu::CScoreManager::SearchByNameAndCourseName()
{
	std::string strStudentName;
	std::string strCourseName;
	std::cout << "��������:";
	std::cin >> strStudentName;
	std::cout << "����γ���:";
	std::cin >> strCourseName;

	if (!Search(strStudentName.c_str(), strCourseName.c_str(),
		CScore::compareStudentNameAndCourseName, OnSearchByNameAndCourseName))
		std::cout << "�޼�¼" << std::endl;
}
void zhu::CScoreManager::SearchByNoAndCourseName()
{
	int nStudentNo;
	std::string strCourseName;
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;
	std::cout << "����γ���:";
	std::cin >> strCourseName;

	if (!Search(nStudentNo, strCourseName.c_str(),
		CScore::compareStudentNoAndCourseName, OnSearchByNoAndCourseName))
		std::cout << "�޼�¼" << std::endl;
}
