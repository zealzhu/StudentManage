///////////////////////////////////////
// �γ̹�����
//////////////////////////////////////
#include "Manager.h"

void zhu::CCourseManager::Print(std::list<zhu::CCourse>* list)
{	
	std::list<zhu::CCourse>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
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
bool zhu::CCourseManager::OnDelete(std::list<zhu::CCourse>& lstCourse, std::list<zhu::CCourse>::iterator& itFind)
{
	lstCourse.erase(itFind);																	//�Ƴ�		
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, lstCourse);									//����
	return false;
}
bool zhu::CCourseManager::OnUpdate(std::list<zhu::CCourse>& lstCourse, std::list<zhu::CCourse>::iterator& itFind)
{
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "�����¿γ̺�:";
	std::cin >> nCourseNo;
	std::cout << "�����¿γ���:";
	std::cin >> strCourseName;
	std::cout << "�����¿γ����ͣ�1.ѡ�� 2.���ޣ�:";
	std::cin >> nCourseType;
	std::cout << "�����¿γ�����:";
	std::cin >> strDescription;

	itFind->m_nCourseNo = nCourseNo;
	itFind->m_emCourseType = CourseType(nCourseType);
	strcpy(itFind->m_szCourseName, strCourseName.c_str());
	strcpy(itFind->m_szDescription, strDescription.c_str());

	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, lstCourse);									//����

	return false;
}

void zhu::CCourseManager::Add()
{
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "����γ̺�:";
	std::cin >> nCourseNo;
	std::cout << "����γ���:";
	std::cin >> strCourseName;
	std::cout << "����γ����ͣ�1.ѡ�� 2.���ޣ�:";
	std::cin >> nCourseType;
	std::cout << "����γ�����:";
	std::cin >> strDescription;

	CCourse objCourse(nCourseNo, strCourseName.c_str(), strDescription.c_str(), CourseType(nCourseType));
	if (CFileHelper::Append<CCourse>(COURSE_FILE_NAME, objCourse))
		std::cout << "��ӳɹ�" << std::endl;
	else
		std::cout << "���ʧ��" << std::endl;
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

	std::list<CCourse>* list = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	Print(list);
	delete list;
}