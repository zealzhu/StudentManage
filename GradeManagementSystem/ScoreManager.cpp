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
	std::vector<CScore>* vector = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

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
	std::vector<CScore>* vector = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

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
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, vecScore);
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

	std::string strUpdateField;
	std::cout << "����Ҫ�޸ĵ�����Ա�ţ�ѧ�ţ��������γ������ɼ���:";
	std::cin >> strUpdateField;

	if (strUpdateField == "���Ա��")
	{
		std::cout << "�����¿��Ա��:";
		std::cin >> nTestSubjectNo;
		CheckInput();
		//����Ƿ��иÿ��Ա��
		if (!IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
			throw NotFoundException("���Ա��");
		itFind->m_nTestSubjectNo = nTestSubjectNo;
	}
	else if (strUpdateField == "ѧ��")
	{
		std::cout << "������ѧ��:";
		std::cin >> nStudentNo;
		//����Ƿ��и�ѧ��
		if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
			throw NotFoundException("ѧ��");
		itFind->m_nStudentNo = nStudentNo;
	}
	else if (strUpdateField == "����")
	{
		std::cout << "����������:";
		std::cin >> strStuentName;
		SetAndCheckCharParam(itFind->m_szStudentName, strStuentName.c_str(), sizeof(itFind->m_szStudentName));
	}
	else if (strUpdateField == "�༶")
	{
		std::cout << "�����°༶:";
		std::cin >> strClassName;
		if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, NULL))
			throw NotFoundException("�༶");
		SetAndCheckCharParam(itFind->m_szClassName, strClassName.c_str(), sizeof(itFind->m_szClassName));
	}
	else if (strUpdateField == "�γ���")
	{
		std::cout << "�����¿γ���:";
		std::cin >> strCourseName;
		if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
			throw NotFoundException("�γ�");
		SetAndCheckCharParam(itFind->m_szCourseName, strCourseName.c_str(), sizeof(itFind->m_szCourseName));
	}
	else if (strUpdateField == "�ɼ�")
	{
		std::cout << "�����³ɼ�:";
		std::cin >> fScore;
		itFind->m_fScore = fScore;
	}
	else {
		throw std::exception("��������޴���");
	}

	//����
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, vecScore);
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
		std::cout << "���ͳ����༶ͳ������,��û���㹻ʱ������û��ʵ��" << std::endl;
		break;
	case 2:
		StatisticsClass();
		break;
	case 3:
		StatisticsCourse();
		break;
	case 4:
		std::cout << "ͳ�����ǰ����ͳ�ư༶ǰ������,��û���㹻ʱ������û��ʵ��" << std::endl;
		break;
	case 5:
		StatisticsClassTopThree();
		break;
	default:
		break;
	}
}

//	���ݰ༶ͳ�Ƴɼ�
void zhu::CScoreManager::StatisticsClass()
{
	std::cout << std::right
		<< std::setw(30) << "�ܳɼ�ƽ����"
		<< std::setw(20) << "�ܳɼ���߷�" 
		<< std::setw(20) << "�ܳɼ���ͷ�" << std::endl;
	//��ȡ���а༶��Ϣ
	std::vector<CClass>* vecClass = CFileHelper::ReadHasVectorAll<CClass>(CLASS_FILE_NAME);
	//��ȡ����ѧ���ɼ���Ϣ
	std::vector<CScore>* vecScore = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);
	//�����༶
	for (int i = 0; i < vecClass->size(); i++)
	{
		//�༶��ѧ��vector
		std::vector<int>& vecNo = (*vecClass)[i].m_vecStudentNo;
		//�༶����ѧ�����ܷ�
		float fClassTotal = 0;
		//ѧ���ܷ��е���߷�
		float fStudentTotalMax = 0;
		//ѧ���ܷ��е���ͷ�
		float fStudentTotalMin = 10000;
		//�����༶�е�ѧ��
		for (int j = 0; j < vecNo.size(); j++)
		{
			//ѧ���ܷ�
			float fStudentTotal = 0;
			//��������,�����ܷ�
			for (int k = 0; k < vecScore->size(); k++)
			{
				CScore& objScore = (*vecScore)[k];
				if (objScore.m_nStudentNo == vecNo[j])
				{
					//��������ӵ�ѧ�����ܷ���
					fStudentTotal += objScore.m_fScore;
				}
			}
			//�ж��Ƿ���߷�
			if (fStudentTotal > fStudentTotalMax)
				fStudentTotalMax = fStudentTotal;
			//�ж��Ƿ����
			if (fStudentTotal < fStudentTotalMin)
				fStudentTotalMin = fStudentTotal;
			//��ѧ���ܷ���ӵ��༶�ܷ���
			fClassTotal += fStudentTotal;
		}
		//��ӡ
		int fAvg = 0;
		if (vecNo.size() != 0) 
		{
			fAvg = fClassTotal / vecNo.size();
		}
		else
		{
			fStudentTotalMin = 0;
		}
		std::cout << (*vecClass)[i].m_szClassName
			<< std::right
			<< std::setw(20) << fAvg
			<< std::setw(20) << fStudentTotalMax
			<< std::setw(20) << fStudentTotalMin << std::endl;
	}
	std::cout << "*****************************************************************************" << std::endl;
	//�ͷ��ڴ�
	delete vecClass;
	delete vecScore;
}

//	���ݿγ�ͳ�Ƴɼ�
void zhu::CScoreManager::StatisticsCourse()
{
	std::cout << std::right
		<< std::setw(38) << "ƽ����"
		<< std::setw(20) << "��߷�"
		<< std::setw(20) << "��ͷ�" << std::endl;
	//��ȡ���пγ���Ϣ
	std::vector<CCourse>* vecCourse = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	//��ȡ����ѧ���ɼ���Ϣ
	std::vector<CScore>* vecScore = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//�������пγ�
	for (int i = 0; i < vecCourse->size(); i++)
	{
		float fTotal = 0;
		float fMax = 0;
		float fMin = 10000;
		int nNumber = 0;			//��¼�ҵ�course������
		CCourse& objCourse = (*vecCourse)[i];

		//��������
		for (int j = 0; j < vecScore->size(); j++)
		{
			CScore& objScore = (*vecScore)[j];
			if (strcmp(objScore.m_szCourseName, objCourse.m_szCourseName) == 0)
			{
				//��������ӵ��γ̵��ܷ���
				fTotal += objScore.m_fScore;
				//�ж��Ƿ���߷�
				if (objScore.m_fScore > fMax)
					fMax = objScore.m_fScore;
				//�ж��Ƿ���ͷ�
				if (objScore.m_fScore < fMin)
					fMin = objScore.m_fScore;
				nNumber++;
			}
		}
		//��ӡ
		int fAvg = 0;
		if (nNumber != 0)
			fAvg = fTotal / nNumber;
		else
			fMin = 0;
		std::cout << std::left
			<< std::setw(15) << objCourse.m_szCourseName
			<< std::right
			<< std::setw(20) << fAvg
			<< std::setw(20) << fMax
			<< std::setw(20) << fMin << std::endl;
	}
	std::cout << "*****************************************************************************" << std::endl;

	//�ͷ��ڴ�
	delete vecCourse;
	delete vecScore;
}

//	���ݰ༶ͳ��ǰ��������ǰ���ͺ��ܳɼ�ǰ����
void zhu::CScoreManager::StatisticsClassTopThree()
{
	//��ȡ���а༶��Ϣ
	std::vector<CClass>* vecClass = CFileHelper::ReadHasVectorAll<CClass>(CLASS_FILE_NAME);
	//��ȡ���пγ���Ϣ
	std::vector<CCourse>* vecCourse = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	//��ȡ����ѧ���ɼ���Ϣ
	std::vector<CScore>* vecScore = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);
	
	//����ÿ���༶
	for (int i = 0; i < vecClass->size(); i++)
	{
		//ÿ���༶�е�����ѧ���ĳɼ�����
		std::vector<CScore> vecScoreForClass;		
		float fTotalFirst = 0;	//�ܳɼ���һ��
		float fTotalSecond = 0;	//�ܳɼ��ڶ���
		float fTotalThird = 0;	//�ܳɼ�������

		CClass& objClass = (*vecClass)[i];

		//ѧ��vector
		std::vector<int>& vecNo = objClass.m_vecStudentNo;
		//�����༶�е�ѧ��
		for (int j = 0; j < vecNo.size(); j++)
		{
			float fStudentTotal = 0;
			//��������
			for (int k = 0; k < vecScore->size(); k++) 
			{
				CScore& objScore = (*vecScore)[k];

				if (objScore.m_nStudentNo == vecNo[j])
				{
					//����ѧ�źͰ༶�е�ѧ��ƥ��
					fStudentTotal += objScore.m_fScore;
					vecScoreForClass.push_back(objScore);
				}
			}
			//�ж�ǰ��
			if (fStudentTotal > fTotalFirst) 
			{
				fTotalThird = fTotalSecond;		//�ڶ������
				fTotalSecond = fTotalFirst;		//��һ��ڶ�
				fTotalFirst = fStudentTotal;
			}	
			else if (fStudentTotal > fTotalSecond)
			{
				fTotalThird = fTotalSecond;		//�ڶ������
				fTotalSecond = fStudentTotal;
			}	
			else if (fStudentTotal > fTotalThird)
			{
				fTotalThird = fStudentTotal;
			}
		}
		std::cout << objClass.m_szClassName << " top3��" << std::endl
			<< "-----------------------------------------------" << std::endl
			<< "\t"
			<< std::left << std::setw(20)
			<< "�ܳɼ���" << fTotalFirst
			<< "," << fTotalSecond
			<< "," << fTotalThird << std::endl;
		//�������пγ�
		for (int j = 0; i < vecCourse->size(); i++)
		{
			float fCourseFirst = 0;		//�ÿγ̵�һ��
			float fCourseSecond = 0;	//�ÿγ̵ڶ���
			float fCourseThird = 0;		//�ÿγ̵�����
			CCourse& objCourse = (*vecCourse)[i];
			//�����ð༶�����гɼ�
			for (int k = 0; k < vecScoreForClass.size(); k++)
			{
				CScore& objScore = vecScoreForClass[k];
				if (strcmp(objScore.m_szCourseName, objCourse.m_szCourseName) == 0)
				{
					//�ҵ��ð༶�ÿγ̶�Ӧ�ĳɼ�
					if (objScore.m_fScore > fCourseFirst)
					{
						fCourseThird = fCourseSecond;		//�ڶ������
						fCourseSecond = fCourseFirst;		//��һ��ڶ�
						fCourseFirst = objScore.m_fScore;
					}
					else if (objScore.m_fScore > fCourseSecond)
					{
						fCourseThird = fCourseSecond;		//�ڶ������
						fCourseSecond = objScore.m_fScore;
					}
					else if (objScore.m_fScore > fCourseThird)
					{
						fCourseThird = objScore.m_fScore;
					}
				}
			}
			std::cout << "\t"
				<< std::left << std::setw(20)
				<< objCourse.m_szCourseName
				<< fCourseFirst << "," << fCourseSecond << "," << fCourseThird	
				<< std::endl;
		}
		std::cout << std::endl;
	}

	//�ͷ��ڴ�
	delete vecClass;
	delete vecCourse;
	delete vecScore;
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
	//��⿼�Ա���Ƿ����
	if (!IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw NotFoundException("���Ա��");
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;
	//���ѧ���Ƿ����
	if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw NotFoundException("ѧ��");
	std::cout << "��������:";
	std::cin >> strStuentName;
	//����������볤��
	SetAndCheckCharParam(NULL, strStuentName.c_str(), sizeof(CScore::m_szStudentName));
	std::cout << "����༶:";
	std::cin >> strClassName;
	//���༶�Ƿ����
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, NULL))
		throw NotFoundException("�༶");
	std::cout << "����γ���:";
	std::cin >> strCourseName;
	//���γ����Ƿ����
	if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
		throw NotFoundException("�γ�");
	std::cout << "����ɼ�:";
	std::cin >> fScore;

	//����������Ƿ��д���
	CheckInput();
	
	//��ӵ��ļ���
	CScore objScore(nTestSubjectNo, nStudentNo, strStuentName.c_str(),
		strCourseName.c_str(), strClassName.c_str(), fScore);
	CFileHelper::Append<CScore>(SCORE_FILE_NAME, objScore);
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
	std::vector<CScore>* vector = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);
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
