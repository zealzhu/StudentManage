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
	std::vector<CScore>* vector = CFileHelper<CScore>::ReadAll(SCORE_FILE_NAME);

	//����
	std::vector<CScore>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		if (compare(nNo, szClassName, *it))
		{
			bFind = true;
			if (callback != NULL) {
				if (!callback(*vector, it))
					break;
			}
			else
			{
				break;
			}
			
		}
	}
	delete vector;

	return bFind;
}
//	���ҷ��� - ͨ�������Ͱ༶����
bool zhu::CScoreManager::Search(const char * szStudentName, const char * szClassName,
	typename COMPARE_BY_CHAR_AND_CHAR compare, typename OnSearch<CScore>::SEARCH_SUCCESS callback)
{
	bool bFind = false;

	//��ȡ��Ϣ
	std::vector<CScore>* vector = CFileHelper<CScore>::ReadAll(SCORE_FILE_NAME);

	//����
	std::vector<CScore>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		if (compare(szStudentName, szClassName, *it))
		{
			bFind = true;
			if (callback != NULL) {
				if (!callback(*vector, it))
					break;
			}
			else
			{
				break;
			}
		}
	}
	delete vector;

	return bFind;
}

//	ɾ���ص�
bool zhu::CScoreManager::OnDelete(std::vector<zhu::CScore>& vecScore, 
	std::vector<zhu::CScore>::iterator& itFind)
{
	vecScore.erase(itFind);
	CFileHelper<CScore>::Save(SCORE_FILE_NAME, vecScore);
	return false;
}

//	���»ص�
bool zhu::CScoreManager::OnUpdate(std::vector<zhu::CScore>& vecScore, 
	std::vector<zhu::CScore>::iterator& itFind)
{
	int nStudentNo;
	int nTestSubjectNo;
	float fScore;
	std::string strClassName;
	std::string strStuentName;
	std::string strCourseName;

	std::cout << "�����¿��Ա��:";
	std::cin >> nTestSubjectNo;
	if (!IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw NotFoundException("���Ա��");
	std::cout << "������ѧ��:";
	std::cin >> nStudentNo;
	if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw NotFoundException("ѧ��");
	std::cout << "����������:";
	std::cin >> strStuentName;
	std::cout << "�����°༶:";
	std::cin >> strClassName;
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, NULL))
		throw NotFoundException("�༶");
	std::cout << "�����¿γ���:";
	std::cin >> strCourseName;
	if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
		throw NotFoundException("�γ�");
	std::cout << "�����³ɼ�:";
	std::cin >> fScore;

	itFind->m_nTestSubjectNo = nTestSubjectNo;
	itFind->m_nStudentNo = nStudentNo;
	strcpy(itFind->m_szStudentName, strStuentName.c_str());
	strcpy(itFind->m_szClassName, strClassName.c_str());
	strcpy(itFind->m_szCourseName, strCourseName.c_str());
	itFind->m_fScore = fScore;

	CFileHelper<CScore>::Save(SCORE_FILE_NAME, vecScore);
	return false;
}

//	���һص�
bool zhu::CScoreManager::OnSearchByNoAndCourseName(std::vector<zhu::CScore>& vecScore
	, std::vector<zhu::CScore>::iterator& itFind)
{
	std::vector<zhu::CScore> vecTemp(1, *itFind);
	Print(&vecTemp);
	return false;
}
bool zhu::CScoreManager::OnSearchByNameAndCourseName(std::vector<zhu::CScore>& vecScore,
	std::vector<zhu::CScore>::iterator& itFind)
{
	std::vector<zhu::CScore> vecTemp(1, *itFind);
	Print(&vecTemp);
	return false;
}

//	��ӡ
void zhu::CScoreManager::Print(std::vector<zhu::CScore>* vector)
{
	std::cout << std::left
		<< std::setw(10) << "���Ա��"
		<< std::setw(10) << "ѧ��"
		<< std::setw(10) << "����"
		<< std::setw(10) << "�༶"
		<< std::setw(10) << "�γ���"
		<< std::setw(10) << "�ɼ�"
		<< std::endl;
	
	std::vector<zhu::CScore>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
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

//	ͳ��
void zhu::CScoreManager::Statistics()
{
	int nChoose;
	std::cout << "       ͳ����Ϣ			" << std::endl;
	std::cout << "	  1.ͳ�������Ϣ         " << std::endl;
	std::cout << "	  2.ͳ�ư༶��Ϣ         " << std::endl;
	std::cout << "	  3.ͳ�ƿ�Ŀ��Ϣ         " << std::endl;
	std::cout << "	  4.ͳ�����ǰ��         " << std::endl;
	std::cout << "	  5.ͳ�ư༶ǰ��         " << std::endl;

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
	if (!IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw NotFoundException("���Ա��");
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;
	if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw NotFoundException("ѧ��");
	std::cout << "��������:";
	std::cin >> strStuentName;
	std::cout << "����༶:";
	std::cin >> strClassName;
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, NULL))
		throw NotFoundException("�༶");
	std::cout << "����γ���:";
	std::cin >> strCourseName;
	if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
		throw NotFoundException("�γ�");
	std::cout << "����ɼ�:";
	std::cin >> fScore;
	
	CScore objScore(nTestSubjectNo, nStudentNo, strStuentName.c_str(),
		strCourseName.c_str(), strClassName.c_str(), fScore);
	CFileHelper<CScore>::Append(SCORE_FILE_NAME, objScore);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CScoreManager::Del()
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
void zhu::CScoreManager::Update()
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
void zhu::CScoreManager::Search()
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

//	����
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

//	ɾ��
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

//	����
void zhu::CScoreManager::SearchAll()
{
	std::vector<CScore>* vector = CFileHelper<CScore>::ReadAll(SCORE_FILE_NAME);
	Print(vector);
	delete vector;
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
