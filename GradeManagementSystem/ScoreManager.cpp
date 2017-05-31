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
	std::vector<CScore>* vector = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//遍历
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
//	查找方法 - 通过姓名和班级查找
bool zhu::CScoreManager::Search(const char * szStudentName, const char * szClassName,
	typename COMPARE_BY_CHAR_AND_CHAR compare, typename OnSearch<CScore>::SEARCH_SUCCESS callback)
{
	bool bFind = false;

	//读取信息
	std::vector<CScore>* vector = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//遍历
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

//	删除回调
bool zhu::CScoreManager::OnDelete(std::vector<zhu::CScore>& vecScore, 
	std::vector<zhu::CScore>::iterator& itFind)
{
	vecScore.erase(itFind);
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, vecScore);
	return false;
}

//	更新回调
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
	std::cout << "输入要修改的项（考试编号，学号，姓名，课程名，成绩）:";
	std::cin >> strUpdateField;

	if (strUpdateField == "考试编号")
	{
		std::cout << "输入新考试编号:";
		std::cin >> nTestSubjectNo;
		CheckInput();
		//检测是否有该考试编号
		if (!IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
			throw NotFoundException("考试编号");
		itFind->m_nTestSubjectNo = nTestSubjectNo;
	}
	else if (strUpdateField == "学号")
	{
		std::cout << "输入新学号:";
		std::cin >> nStudentNo;
		//检测是否有该学号
		if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
			throw NotFoundException("学号");
		itFind->m_nStudentNo = nStudentNo;
	}
	else if (strUpdateField == "姓名")
	{
		std::cout << "输入新姓名:";
		std::cin >> strStuentName;
		SetAndCheckCharParam(itFind->m_szStudentName, strStuentName.c_str(), sizeof(itFind->m_szStudentName));
	}
	else if (strUpdateField == "班级")
	{
		std::cout << "输入新班级:";
		std::cin >> strClassName;
		if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, NULL))
			throw NotFoundException("班级");
		SetAndCheckCharParam(itFind->m_szClassName, strClassName.c_str(), sizeof(itFind->m_szClassName));
	}
	else if (strUpdateField == "课程名")
	{
		std::cout << "输入新课程名:";
		std::cin >> strCourseName;
		if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
			throw NotFoundException("课程");
		SetAndCheckCharParam(itFind->m_szCourseName, strCourseName.c_str(), sizeof(itFind->m_szCourseName));
	}
	else if (strUpdateField == "成绩")
	{
		std::cout << "输入新成绩:";
		std::cin >> fScore;
		itFind->m_fScore = fScore;
	}
	else {
		throw std::exception("输入错误：无此项");
	}

	//保存
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, vecScore);
	return false;
}

//	查找回调
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

//	打印
void zhu::CScoreManager::Print(std::vector<zhu::CScore>* vector)
{
	std::cout << std::left
		<< std::setw(10) << "考试编号"
		<< std::setw(10) << "学号"
		<< std::setw(10) << "姓名"
		<< std::setw(10) << "班级"
		<< std::setw(10) << "课程名"
		<< std::setw(10) << "成绩"
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

//	统计
void zhu::CScoreManager::Statistics()
{
	int nChoose;
	std::cout << "       统计信息			" << std::endl;
	std::cout << "	  1.统计年段信息         " << std::endl;
	std::cout << "	  2.统计班级信息         " << std::endl;
	std::cout << "	  3.统计科目信息         " << std::endl;
	std::cout << "	  4.统计年段前三         " << std::endl;
	std::cout << "	  5.统计班级前三         " << std::endl;

	std::cin >> nChoose;
	system("cls");		//清屏
	switch (nChoose)
	{
	case 1:
		std::cout << "年段统计与班级统计类似,因没有足够时间所以没有实现" << std::endl;
		break;
	case 2:
		StatisticsClass();
		break;
	case 3:
		StatisticsCourse();
		break;
	case 4:
		std::cout << "统计年段前三与统计班级前三类似,因没有足够时间所以没有实现" << std::endl;
		break;
	case 5:
		StatisticsClassTopThree();
		break;
	default:
		break;
	}
}

//	根据班级统计成绩
void zhu::CScoreManager::StatisticsClass()
{
	std::cout << std::right
		<< std::setw(30) << "总成绩平均分"
		<< std::setw(20) << "总成绩最高分" 
		<< std::setw(20) << "总成绩最低分" << std::endl;
	//读取所有班级信息
	std::vector<CClass>* vecClass = CFileHelper::ReadHasVectorAll<CClass>(CLASS_FILE_NAME);
	//读取所有学生成绩信息
	std::vector<CScore>* vecScore = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);
	//遍历班级
	for (int i = 0; i < vecClass->size(); i++)
	{
		//班级中学号vector
		std::vector<int>& vecNo = (*vecClass)[i].m_vecStudentNo;
		//班级所有学生的总分
		float fClassTotal = 0;
		//学生总分中的最高分
		float fStudentTotalMax = 0;
		//学生总分中的最低分
		float fStudentTotalMin = 10000;
		//遍历班级中的学号
		for (int j = 0; j < vecNo.size(); j++)
		{
			//学生总分
			float fStudentTotal = 0;
			//遍历分数,计算总分
			for (int k = 0; k < vecScore->size(); k++)
			{
				CScore& objScore = (*vecScore)[k];
				if (objScore.m_nStudentNo == vecNo[j])
				{
					//将分数添加到学生的总分中
					fStudentTotal += objScore.m_fScore;
				}
			}
			//判断是否最高分
			if (fStudentTotal > fStudentTotalMax)
				fStudentTotalMax = fStudentTotal;
			//判断是否最低
			if (fStudentTotal < fStudentTotalMin)
				fStudentTotalMin = fStudentTotal;
			//将学生总分添加到班级总分中
			fClassTotal += fStudentTotal;
		}
		//打印
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
	//释放内存
	delete vecClass;
	delete vecScore;
}

//	根据课程统计成绩
void zhu::CScoreManager::StatisticsCourse()
{
	std::cout << std::right
		<< std::setw(38) << "平均分"
		<< std::setw(20) << "最高分"
		<< std::setw(20) << "最低分" << std::endl;
	//读取所有课程信息
	std::vector<CCourse>* vecCourse = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	//读取所有学生成绩信息
	std::vector<CScore>* vecScore = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);

	//遍历所有课程
	for (int i = 0; i < vecCourse->size(); i++)
	{
		float fTotal = 0;
		float fMax = 0;
		float fMin = 10000;
		int nNumber = 0;			//记录找到course的数量
		CCourse& objCourse = (*vecCourse)[i];

		//遍历分数
		for (int j = 0; j < vecScore->size(); j++)
		{
			CScore& objScore = (*vecScore)[j];
			if (strcmp(objScore.m_szCourseName, objCourse.m_szCourseName) == 0)
			{
				//将分数添加到课程的总分中
				fTotal += objScore.m_fScore;
				//判断是否最高分
				if (objScore.m_fScore > fMax)
					fMax = objScore.m_fScore;
				//判断是否最低分
				if (objScore.m_fScore < fMin)
					fMin = objScore.m_fScore;
				nNumber++;
			}
		}
		//打印
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

	//释放内存
	delete vecCourse;
	delete vecScore;
}

//	根据班级统计前三（单科前三和和总成绩前三）
void zhu::CScoreManager::StatisticsClassTopThree()
{
	//读取所有班级信息
	std::vector<CClass>* vecClass = CFileHelper::ReadHasVectorAll<CClass>(CLASS_FILE_NAME);
	//读取所有课程信息
	std::vector<CCourse>* vecCourse = CFileHelper::ReadAll<CCourse>(COURSE_FILE_NAME);
	//读取所有学生成绩信息
	std::vector<CScore>* vecScore = CFileHelper::ReadAll<CScore>(SCORE_FILE_NAME);
	
	//遍历每个班级
	for (int i = 0; i < vecClass->size(); i++)
	{
		//每个班级中的所有学生的成绩集合
		std::vector<CScore> vecScoreForClass;		
		float fTotalFirst = 0;	//总成绩第一名
		float fTotalSecond = 0;	//总成绩第二名
		float fTotalThird = 0;	//总成绩第三名

		CClass& objClass = (*vecClass)[i];

		//学号vector
		std::vector<int>& vecNo = objClass.m_vecStudentNo;
		//遍历班级中的学号
		for (int j = 0; j < vecNo.size(); j++)
		{
			float fStudentTotal = 0;
			//遍历分数
			for (int k = 0; k < vecScore->size(); k++) 
			{
				CScore& objScore = (*vecScore)[k];

				if (objScore.m_nStudentNo == vecNo[j])
				{
					//分数学号和班级中的学号匹配
					fStudentTotal += objScore.m_fScore;
					vecScoreForClass.push_back(objScore);
				}
			}
			//判断前三
			if (fStudentTotal > fTotalFirst) 
			{
				fTotalThird = fTotalSecond;		//第二变第三
				fTotalSecond = fTotalFirst;		//第一变第二
				fTotalFirst = fStudentTotal;
			}	
			else if (fStudentTotal > fTotalSecond)
			{
				fTotalThird = fTotalSecond;		//第二变第三
				fTotalSecond = fStudentTotal;
			}	
			else if (fStudentTotal > fTotalThird)
			{
				fTotalThird = fStudentTotal;
			}
		}
		std::cout << objClass.m_szClassName << " top3：" << std::endl
			<< "-----------------------------------------------" << std::endl
			<< "\t"
			<< std::left << std::setw(20)
			<< "总成绩：" << fTotalFirst
			<< "," << fTotalSecond
			<< "," << fTotalThird << std::endl;
		//遍历所有课程
		for (int j = 0; i < vecCourse->size(); i++)
		{
			float fCourseFirst = 0;		//该课程第一名
			float fCourseSecond = 0;	//该课程第二名
			float fCourseThird = 0;		//该课程第三名
			CCourse& objCourse = (*vecCourse)[i];
			//遍历该班级的所有成绩
			for (int k = 0; k < vecScoreForClass.size(); k++)
			{
				CScore& objScore = vecScoreForClass[k];
				if (strcmp(objScore.m_szCourseName, objCourse.m_szCourseName) == 0)
				{
					//找到该班级该课程对应的成绩
					if (objScore.m_fScore > fCourseFirst)
					{
						fCourseThird = fCourseSecond;		//第二变第三
						fCourseSecond = fCourseFirst;		//第一变第二
						fCourseFirst = objScore.m_fScore;
					}
					else if (objScore.m_fScore > fCourseSecond)
					{
						fCourseThird = fCourseSecond;		//第二变第三
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

	//释放内存
	delete vecClass;
	delete vecCourse;
	delete vecScore;
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
	//检测考试编号是否存在
	if (!IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw NotFoundException("考试编号");
	std::cout << "输入学号:";
	std::cin >> nStudentNo;
	//检测学号是否存在
	if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw NotFoundException("学号");
	std::cout << "输入姓名:";
	std::cin >> strStuentName;
	//检测名字输入长度
	SetAndCheckCharParam(NULL, strStuentName.c_str(), sizeof(CScore::m_szStudentName));
	std::cout << "输入班级:";
	std::cin >> strClassName;
	//检测班级是否存在
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, NULL))
		throw NotFoundException("班级");
	std::cout << "输入课程名:";
	std::cin >> strCourseName;
	//检测课程名是否存在
	if (!IManager::Search<CCourse>(strCourseName.c_str(), COURSE_FILE_NAME, CCourse::compareCourseName, NULL))
		throw NotFoundException("课程");
	std::cout << "输入成绩:";
	std::cin >> fScore;

	//检测输入流是否有错误
	CheckInput();
	
	//添加到文件中
	CScore objScore(nTestSubjectNo, nStudentNo, strStuentName.c_str(),
		strCourseName.c_str(), strClassName.c_str(), fScore);
	CFileHelper::Append<CScore>(SCORE_FILE_NAME, objScore);
	std::cout << "添加成功" << std::endl;
}
void zhu::CScoreManager::Del()
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
void zhu::CScoreManager::Update()
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
void zhu::CScoreManager::Search()
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

//	更新
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

//	删除
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

//	查找
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
