///////////////////////////////////////
// �γ̹�����
//////////////////////////////////////
#include "Manager.h"

void zhu::CCourseManager::Print(std::vector<zhu::CCourse>* vector)
{	
	std::vector<zhu::CCourse>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		CCourse objCourse = *it;
		std::cout << std::left << std::setw(10)
			<< std::setw(10) << objCourse.m_nCourseNo
			<< std::setw(10) << objCourse.m_szCourseName
			<< std::setw(10) << (objCourse.m_emCourseType == CourseType::TYPE_OPTIONAL_COURSE ? "���޿�" : "ѡ�޿�")
			<< std::setw(10) << objCourse.m_szDescription
			<< std::endl;
	}
}
bool zhu::CCourseManager::OnDelete(std::vector<zhu::CCourse>& vecCourse, std::vector<zhu::CCourse>::iterator& itFind)
{
	vecCourse.erase(itFind);																	//�Ƴ�		
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, vecCourse);									//����
	return false;
}
bool zhu::CCourseManager::OnUpdate(std::vector<zhu::CCourse>& vecCourse, std::vector<zhu::CCourse>::iterator& itFind)
{
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "�����¿γ���:";
	std::cin >> strCourseName;
	SetAndCheckCharParam(itFind->m_szCourseName, strCourseName.c_str(), sizeof(itFind->m_szCourseName));
	std::cout << "�����¿γ����ͣ�1.ѡ�� 2.���ޣ�:";
	std::cin >> nCourseType;
	std::cout << "�����¿γ�����:";
	std::cin >> strDescription;
	SetAndCheckCharParam(itFind->m_szDescription, strDescription.c_str(), sizeof(itFind->m_szDescription));

	CheckInput();
	itFind->m_emCourseType = CourseType(nCourseType);
	//����
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, vecCourse);									

	return false;
}

void zhu::CCourseManager::Add()
{
	//���
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "����γ̺�:";
	std::cin >> nCourseNo;
	//�ж��Ƿ��пγ̺�
	if (IManager::Search<CCourse>(nCourseNo, COURSE_FILE_NAME, CCourse::compareCourseNo, NULL))
		throw KeyUniqueException("�γ̺�");
	std::cout << "����γ���:";
	std::cin >> strCourseName;
	SetAndCheckCharParam(NULL, strCourseName.c_str(), sizeof(CCourse::m_szCourseName));
	std::cout << "����γ����ͣ�1.ѡ�� 2.���ޣ�:";
	std::cin >> nCourseType;
	std::cout << "����γ�����:";
	std::cin >> strDescription;
	SetAndCheckCharParam(NULL, strDescription.c_str(), sizeof(CCourse::m_szDescription));

	//����������Ƿ��д���
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CCourse objCourse(nCourseNo, strCourseName.c_str(), strDescription.c_str(), CourseType(nCourseType));
	CFileHelper::Append<CCourse>(COURSE_FILE_NAME, objCourse);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CCourseManager::Del()
{
	int nCourseNo;
	std::cout << "����γ̺�:";
	std::cin >> nCourseNo;

	if (IManager::Search<CCourse>(nCourseNo, COURSE_FILE_NAME, CCourse::compareCourseNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CCourseManager::Update()
{
	int nCourseNo;
	std::cout << "����γ̺�:";
	std::cin >> nCourseNo;

	if (IManager::Search<CCourse>(nCourseNo, COURSE_FILE_NAME, CCourse::compareCourseNo, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CCourseManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "�γ̱��"
		<< std::setw(10) << "�γ�����"
		<< std::setw(10) << "�γ�����"
		<< std::setw(10) << "�γ�����"
		<< std::endl;

	std::vector<CCourse>* vector = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	Print(vector);
	delete vector;
}