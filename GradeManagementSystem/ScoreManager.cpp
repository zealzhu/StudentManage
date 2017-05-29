///////////////////////////////////////
// 学生成绩管理方法
//////////////////////////////////////
#include "Manager.h"

//	查找方法 - 通过学号和班级查找
bool zhu::CScoreManager::Search(int nNo, const char * szClassName,
	typename COMPARE_BY_INT_AND_CHAR compare, typename OnSearch<CScore>::SEARCH_SUCCESS callback)
{
	bool bFind = false;

	//读取信息
	std::list<CScore>* list = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//遍历
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
//	查找方法 - 通过姓名和班级查找
bool zhu::CScoreManager::Search(const char * szStudentName, const char * szClassName,
	typename COMPARE_BY_CHAR_AND_CHAR compare, typename OnSearch<CScore>::SEARCH_SUCCESS callback)
{
	bool bFind = false;

	//读取信息
	std::list<CScore>* list = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//遍历
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

//	删除回调
bool zhu::CScoreManager::OnDelete(std::list<zhu::CScore>& lstScore, 
	std::list<zhu::CScore>::iterator& itFind)
{
	lstScore.erase(itFind);
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, lstScore);
	return false;
}

//	更新回调
bool zhu::CScoreManager::OnUpdate(std::list<zhu::CScore>& lstScore, 
	std::list<zhu::CScore>::iterator& itFind)
{
	int nStudentNo;
	int nTestSubjectNo;
	float fScore;
	std::string strClassName;
	std::string strStuentName;
	std::string strCourseName;

	std::cout << "输入新考试编号:";
	std::cin >> nTestSubjectNo;
	std::cout << "输入新学号:";
	std::cin >> nStudentNo;
	std::cout << "输入新姓名:";
	std::cin >> strStuentName;
	std::cout << "输入新班级:";
	std::cin >> strClassName;
	std::cout << "输入新课程名:";
	std::cin >> strCourseName;
	std::cout << "输入新成绩:";
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

//	查找回调
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

//	打印
void zhu::CScoreManager::Print(std::list<zhu::CScore>* list)
{
	std::cout << std::left
		<< std::setw(10) << "考试编号"
		<< std::setw(10) << "学号"
		<< std::setw(10) << "姓名"
		<< std::setw(10) << "班级"
		<< std::setw(10) << "课程名"
		<< std::setw(10) << "成绩"
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
	std::cout << "统计功能" << std::endl;
}

//	重写
void zhu::CScoreManager::Add()
{
	int nStudentNo;
	int nTestSubjectNo;
	float fScore;
	std::string strClassName;
	std::string strStuentName;
	std::string strCourseName;

	std::cout << "输入考试编号:";
	std::cin >> nTestSubjectNo;
	std::cout << "输入学号:";
	std::cin >> nStudentNo;
	std::cout << "输入姓名:";
	std::cin >> strStuentName;
	std::cout << "输入班级:";
	std::cin >> strClassName;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;
	std::cout << "输入成绩:";
	std::cin >> fScore;
	
	CScore objScore(nTestSubjectNo, nStudentNo, strStuentName.c_str(),
		strCourseName.c_str(), strClassName.c_str(), fScore);
	CFileHelper::Append<CScore>(SCORE_FILE_NAME, objScore);
	std::cout << "添加成功" << std::endl;
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

//	私有方法
void zhu::CScoreManager::UpdateMenu()
{
	int nChoose;
	std::cout << ">修改学生成绩（返回请按其他任意键）：" << std::endl;
	std::cout << "	  1.通过学号和课程号修改" << std::endl;
	std::cout << "	  2.通过姓名和课程号修改" << std::endl;

	std::cin >> nChoose;
	system("cls");		//清屏
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
	std::cout << "输入学号:";
	std::cin >> nStuentNo;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;

	if (Search(nStuentNo, strCourseName.c_str(),
		CScore::compareStudentNoAndCourseName, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}
void zhu::CScoreManager::UpdateByNameAndCourseName()
{
	std::string strStudentName;
	std::string strCourseName;
	std::cout << "输入姓名:";
	std::cin >> strStudentName;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;

	if (Search(strStudentName.c_str(), strCourseName.c_str(),
		CScore::compareStudentNameAndCourseName, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}

void zhu::CScoreManager::DeleteMenu()
{
	int nChoose;
	std::cout << ">删除学生成绩（返回请按其他任意键）：" << std::endl;
	std::cout << "	  1.通过学号和课程号删除" << std::endl;
	std::cout << "	  2.通过姓名和课程号删除" << std::endl;

	std::cin >> nChoose;
	system("cls");		//清屏
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
	std::cout << "输入学号:";
	std::cin >> nStuentNo;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;

	if (Search(nStuentNo, strCourseName.c_str(),
		CScore::compareStudentNoAndCourseName, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
}
void zhu::CScoreManager::DeleteByNameAndCourseName()
{
	std::string strStudentName;
	std::string strCourseName;
	std::cout << "输入姓名:";
	std::cin >> strStudentName;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;

	if (Search(strStudentName.c_str(), strCourseName.c_str(),
		CScore::compareStudentNameAndCourseName, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
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
	std::cout << ">查询学生成绩（返回请按其他任意键）：" << std::endl;
	std::cout << "	  1.通过学号和课程号查找" << std::endl;
	std::cout << "	  2.通过姓名和课程号查找" << std::endl;
	std::cout << "	  3.查询所有" << std::endl;

	std::cin >> nChoose;
	system("cls");		//清屏

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
	std::cout << "输入姓名:";
	std::cin >> strStudentName;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;

	if (!Search(strStudentName.c_str(), strCourseName.c_str(),
		CScore::compareStudentNameAndCourseName, OnSearchByNameAndCourseName))
		std::cout << "无记录" << std::endl;
}
void zhu::CScoreManager::SearchByNoAndCourseName()
{
	int nStudentNo;
	std::string strCourseName;
	std::cout << "输入学号:";
	std::cin >> nStudentNo;
	std::cout << "输入课程名:";
	std::cin >> strCourseName;

	if (!Search(nStudentNo, strCourseName.c_str(),
		CScore::compareStudentNoAndCourseName, OnSearchByNoAndCourseName))
		std::cout << "无记录" << std::endl;
}
