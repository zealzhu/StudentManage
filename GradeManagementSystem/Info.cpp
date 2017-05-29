#include "Info.h"

//	CStudent
zhu::CStudent::CStudent(){}

zhu::CStudent::CStudent(int nStudentNo, Sex emSex, 
	const char * szClassName, const char * szStuentName, const char * szNation,
	const char * szNativePlace, const char * szEntranceDate, const char * szBornDate,
	const char * szAddress, const char * szPhone) : m_nStudentNo(nStudentNo), m_emSex(emSex)
{
	strcpy(m_szClassName, szClassName);
	strcpy(m_szStuentName, szStuentName);
	strcpy(m_szNation, szNation);
	strcpy(m_szNativePlace, szNativePlace);
	strcpy(m_szEntranceDate, szEntranceDate);
	strcpy(m_szBornDate, szBornDate);
	strcpy(m_szAddress, szAddress);
	strcpy(m_szPhone, szPhone);
}

bool zhu::CStudent::compareStudentNo(int nNo, CStudent& objStudent)
{
	return objStudent.m_nStudentNo == nNo;
}

bool zhu::CStudent::compareClassName(const char* szClassName, CStudent& objStudent)
{
	return strcmp(objStudent.m_szClassName, szClassName) == 0;
}

bool zhu::CStudent::compareStudentName(const char* szStudentName, CStudent& objStudent)
{
	return strcmp(objStudent.m_szStuentName, szStudentName) == 0;
}

//	CClass

bool zhu::CClass::compareClassNo(int nNo, CClass & objClass)
{
	return objClass.m_nClassNo == nNo;
}

bool zhu::CClass::compareClassName(const char* szClassName, CClass & objClass)
{
	return strcmp(objClass.m_szClassName, szClassName) == 0;
}

zhu::CClass::CClass()
{
}

zhu::CClass::CClass(int nClassNo, const char * szClassName)
	: m_nClassNo(nClassNo)
{
	strcpy(m_szClassName, szClassName);
}

zhu::CClass::CClass(int nClassNo, const char * szClassName, std::vector<int> vecStudentNo)
	: m_nClassNo(nClassNo), m_vecStudentNo(vecStudentNo)
{
	strcpy(m_szClassName, szClassName);
}

//	CGrade
bool zhu::CGrade::compareGradeNo(int nNo, CGrade & objGrade)
{
	return objGrade.m_nGradeNo == nNo;
}

zhu::CGrade::CGrade()
{
}

zhu::CGrade::CGrade(int nGradeNo, const char * szGradeName)
	: m_nGradeNo(nGradeNo)
{
	strcpy(m_szGradeName, szGradeName);
}

zhu::CGrade::CGrade(int nGradeNo, const char * szGradeName, std::vector<int> vecClassNo)
	: m_nGradeNo(nGradeNo), m_vecClassNo(vecClassNo)
{
	strcpy(m_szGradeName, szGradeName);
}


// CCourse
bool zhu::CCourse::compareCourseNo(int nNo, zhu::CCourse & objCourse)
{
	return objCourse.m_nCourseNo == nNo;
}

bool zhu::CCourse::compareCourseName(const char * szCourseName, CCourse & objCourse)
{
	return strcmp(objCourse.m_szCourseName, szCourseName) == 0;
}

zhu::CCourse::CCourse()
{
}

zhu::CCourse::CCourse(int nCourseNo, const char * szCourseName, const char * szDescription, CourseType emCourseType)
	: m_nCourseNo(nCourseNo), m_emCourseType(emCourseType)
{
	strcpy(m_szCourseName, szCourseName);
	strcpy(m_szDescription, szDescription);
}


//	TestSubject
bool zhu::CTestSubject::compareTestSubjectNo(int nNo, CTestSubject & objTestSubject)
{
	return objTestSubject.m_nTestSubjectNo == nNo;
}

bool zhu::CTestSubject::compareTestSubjectName(const char * szName, CTestSubject & objTestSubject)
{
	return strcmp(objTestSubject.m_szTestSubjectName, szName) == 0;
}

zhu::CTestSubject::CTestSubject()
{
}

zhu::CTestSubject::CTestSubject(int nTestSubjectNo, const char * szTestSubjectName, const char * szCourseName)
	:m_nTestSubjectNo(nTestSubjectNo)
{
	strcpy(m_szTestSubjectName, szTestSubjectName);
	strcpy(m_szCourseName, szCourseName);
}

//	CScore
zhu::CScore::CScore()
{
}

zhu::CScore::CScore(int nTestSubjectNo, int nStudentNo, 
	const char * szStudentName, const char * szCourseName, const char * szClassName, float fScore)
	: m_nTestSubjectNo(nTestSubjectNo), m_nStudentNo(nStudentNo), m_fScore(fScore)
{
	strcpy(m_szStudentName, szStudentName);
	strcpy(m_szCourseName, szCourseName);
	strcpy(m_szClassName, szClassName);
}

bool zhu::CScore::compareStudentNoAndCourseName(int nNo, const char * szCourseName, CScore & objScore)
{
	if(nNo == objScore.m_nStudentNo && !strcmp(szCourseName, objScore.m_szCourseName))
		return true;

	return false;
}

bool zhu::CScore::compareStudentNameAndCourseName(const char * szStudentName, 
	const char * szCourseName, CScore & objScore)
{
	if (!strcmp(szStudentName, objScore.m_szStudentName) && !strcmp(szCourseName, objScore.m_szCourseName))
		return true;
	return false;
}
