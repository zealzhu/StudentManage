///////////////////////////////////////
// 课程管理方法
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
			<< std::setw(10) << (objCourse.m_emCourseType == CourseType::TYPE_OPTIONAL_COURSE ? "必修课" : "选修课")
			<< std::setw(10) << objCourse.m_szDescription
			<< std::endl;
	}
}
bool zhu::CCourseManager::OnDelete(std::vector<zhu::CCourse>& vecCourse, std::vector<zhu::CCourse>::iterator& itFind)
{
	vecCourse.erase(itFind);																	//移除		
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, vecCourse);									//保存
	return false;
}
bool zhu::CCourseManager::OnUpdate(std::vector<zhu::CCourse>& vecCourse, std::vector<zhu::CCourse>::iterator& itFind)
{
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "输入新课程名:";
	std::cin >> strCourseName;
	SetAndCheckCharParam(itFind->m_szCourseName, strCourseName.c_str(), sizeof(itFind->m_szCourseName));
	std::cout << "输入新课程类型（1.选修 2.必修）:";
	std::cin >> nCourseType;
	std::cout << "输入新课程描述:";
	std::cin >> strDescription;
	SetAndCheckCharParam(itFind->m_szDescription, strDescription.c_str(), sizeof(itFind->m_szDescription));

	CheckInput();
	itFind->m_emCourseType = CourseType(nCourseType);
	//保存
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, vecCourse);									

	return false;
}

void zhu::CCourseManager::Add()
{
	//添加
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;

	std::cout << "输入课程号:";
	std::cin >> nCourseNo;
	//判断是否有课程号
	if (IManager::Search<CCourse>(nCourseNo, COURSE_FILE_NAME, CCourse::compareCourseNo, NULL))
		throw KeyUniqueException("课程号");
	std::cout << "输入课程名:";
	std::cin >> strCourseName;
	SetAndCheckCharParam(NULL, strCourseName.c_str(), sizeof(CCourse::m_szCourseName));
	std::cout << "输入课程类型（1.选修 2.必修）:";
	std::cin >> nCourseType;
	std::cout << "输入课程描述:";
	std::cin >> strDescription;
	SetAndCheckCharParam(NULL, strDescription.c_str(), sizeof(CCourse::m_szDescription));

	//检测输入流是否有错误
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CCourse objCourse(nCourseNo, strCourseName.c_str(), strDescription.c_str(), CourseType(nCourseType));
	CFileHelper::Append<CCourse>(COURSE_FILE_NAME, objCourse);
	std::cout << "添加成功" << std::endl;
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

	std::vector<CCourse>* vector = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	Print(vector);
	delete vector;
}