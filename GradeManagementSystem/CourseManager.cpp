///////////////////////////////////////
// 课程管理方法
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
			<< std::setw(10) << (objCourse.m_emCourseType == CourseType::TYPE_OPTIONAL_COURSE ? "必修课" : "选修课")
			<< std::setw(10) << objCourse.m_szDescription
			<< std::endl;
	}
}
bool zhu::CCourseManager::OnDelete(std::list<zhu::CCourse>& lstCourse, std::list<zhu::CCourse>::iterator& itFind)
{
	lstCourse.erase(itFind);																	//移除		
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, lstCourse);									//保存
	return false;
}
bool zhu::CCourseManager::OnUpdate(std::list<zhu::CCourse>& lstCourse, std::list<zhu::CCourse>::iterator& itFind)
{
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "输入新课程号:";
	std::cin >> nCourseNo;
	std::cout << "输入新课程名:";
	std::cin >> strCourseName;
	std::cout << "输入新课程类型（1.选修 2.必修）:";
	std::cin >> nCourseType;
	std::cout << "输入新课程描述:";
	std::cin >> strDescription;

	itFind->m_nCourseNo = nCourseNo;
	itFind->m_emCourseType = CourseType(nCourseType);
	strcpy(itFind->m_szCourseName, strCourseName.c_str());
	strcpy(itFind->m_szDescription, strDescription.c_str());

	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, lstCourse);									//保存

	return false;
}

void zhu::CCourseManager::Add()
{
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "输入课程号:";
	std::cin >> nCourseNo;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;
	std::cout << "输入课程类型（1.选修 2.必修）:";
	std::cin >> nCourseType;
	std::cout << "输入课程描述:";
	std::cin >> strDescription;

	CCourse objCourse(nCourseNo, strCourseName.c_str(), strDescription.c_str(), CourseType(nCourseType));
	if (CFileHelper::Append<CCourse>(COURSE_FILE_NAME, objCourse))
		std::cout << "添加成功" << std::endl;
	else
		std::cout << "添加失败" << std::endl;
}
void zhu::CCourseManager::Del()
{
	int nCourseNo;
	std::cout << "输入课程号:";
	std::cin >> nCourseNo;

	if (IManager::Search<CCourse>(nCourseNo, COURSE_FILE_NAME, CCourse::compareCourseNo, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
}
void zhu::CCourseManager::Update()
{
	int nCourseNo;
	std::cout << "输入课程号:";
	std::cin >> nCourseNo;

	if (IManager::Search<CCourse>(nCourseNo, COURSE_FILE_NAME, CCourse::compareCourseNo, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}
void zhu::CCourseManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "课程编号"
		<< std::setw(10) << "课程名称"
		<< std::setw(10) << "课程类型"
		<< std::setw(10) << "课程描述"
		<< std::endl;

	std::list<CCourse>* list = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	Print(list);
	delete list;
}