///////////////////////////////////////
// 学生管理方法
//////////////////////////////////////
#include "Manager.h"

//	临时记录学号
int nTempNo = 0;

//  打印
void zhu::CStudentManager::Print(CStudent& objStudent)
{
	std::cout << std::left
		<< std::setw(5) << objStudent.m_nStudentNo
		<< std::setw(10) << objStudent.m_szStuentName
		<< std::setw(10) << (objStudent.m_emSex == Sex::MAN ? "男" : "女")
		<< std::setw(10) << objStudent.m_szClassName
		<< std::setw(10) << objStudent.m_szNation
		<< std::setw(10) << objStudent.m_szNativePlace
		<< std::setw(13) << objStudent.m_szBornDate
		<< std::setw(13) << objStudent.m_szEntranceDate
		<< std::setw(18) << objStudent.m_szAddress
		<< std::setw(10) << objStudent.m_szPhone
		<< std::endl;
}
void zhu::CStudentManager::Print(std::vector<zhu::CStudent>* vector)
{
	std::cout << std::left
		<< std::setw(5) << "学号"
		<< std::setw(10) << "姓名"
		<< std::setw(10) << "性别"
		<< std::setw(10) << "班级"
		<< std::setw(10) << "名族"
		<< std::setw(10) << "籍贯"
		<< std::setw(13) << "出生日期"
		<< std::setw(13) << "入学日期"
		<< std::setw(18) << "家庭住址"
		<< std::setw(10) << "联系电话"
		<< std::endl;

	std::vector<zhu::CStudent>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		std::cout << std::left
			<< std::setw(5) << it->m_nStudentNo
			<< std::setw(10) << it->m_szStuentName
			<< std::setw(10) << (it->m_emSex == Sex::MAN ? "男" : "女")
			<< std::setw(10) << it->m_szClassName
			<< std::setw(10) << it->m_szNation
			<< std::setw(10) << it->m_szNativePlace
			<< std::setw(13) << it->m_szBornDate
			<< std::setw(13) << it->m_szEntranceDate
			<< std::setw(18) << it->m_szAddress
			<< std::setw(10) << it->m_szPhone
			<< std::endl;
	}
}

//	回调方法
bool zhu::CStudentManager::OnDelete(std::vector<CStudent>& vecStudent,  std::vector<CStudent>::iterator& itFind)
{
	//删除对应班级中的号数
	IManager::Search<CClass>(itFind->m_szClassName, CLASS_FILE_NAME, CClass::compareClassName, OnDelSearchClass);
	//删除学生
	vecStudent.erase(itFind);
	zhu::CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);	
	return false;
}
bool zhu::CStudentManager::OnUpdate(std::vector<CStudent>& vecStudent, std::vector<CStudent>::iterator& itFind)
{
	std::string strSex;
	std::string strClassName;
	std::string strStuentName;
	std::string strNation;
	std::string strNativePlace;
	std::string strEntranceDate;
	std::string strBornDate;
	std::string strAddress;
	std::string strPhone;

	std::string strUpdateField;
	std::cout << "输入要修改的项（姓名，性别，班级，民族，籍贯，入学日期，出生日期，家庭地址，手机）:";
	std::cin >> strUpdateField;

	if (strUpdateField == "姓名") 
	{
		std::cout << "输入新姓名:";
		std::cin >> strStuentName;
		SetAndCheckCharParam(itFind->m_szStuentName, strStuentName.c_str(), sizeof(itFind->m_szStuentName));
	}
	else if (strUpdateField == "性别")
	{
		std::cout << "输入新性别:";
		std::cin >> strSex;
		itFind->m_emSex = (strSex == "男") ? Sex::MAN : Sex::WOMAN;
	}
	else if (strUpdateField == "班级")
	{
		std::cout << "输入新班级:";
		std::cin >> strClassName;
		//判断是否新的班级
		if ((strcmp(itFind->m_szClassName, strClassName.c_str())) != 0)			
		{
			//是新班级查找该班级并添加学号信息
			if (!IManager::Search<CClass>(strClassName.c_str(),					
				CLASS_FILE_NAME, CClass::compareClassName, OnAddSearchClass))
			{
				//没有找到该班级
				throw NotFoundException("班级");
			}
			else
			{
				//并且删除旧班级中的记录
				IManager::Search<CClass>(itFind->m_szClassName, CLASS_FILE_NAME,
					CClass::compareClassName, OnDelSearchClass);
			}
		}
		SetAndCheckCharParam(itFind->m_szClassName, strClassName.c_str(), sizeof(itFind->m_szClassName));
	}
	else if (strUpdateField == "民族")
	{
		std::cout << "输入新名族:";
		std::cin >> strNation;
		SetAndCheckCharParam(itFind->m_szNation, strNation.c_str(), sizeof(itFind->m_szNation));
	}
	else if (strUpdateField == "籍贯")
	{
		std::cout << "输入新籍贯:";
		std::cin >> strNativePlace;
		SetAndCheckCharParam(itFind->m_szNativePlace, strNativePlace.c_str(), sizeof(itFind->m_szNativePlace));
	}
	else if (strUpdateField == "入学日期")
	{
		std::cout << "输入新入学日期:";
		std::cin >> strEntranceDate;
		SetAndCheckCharParam(itFind->m_szEntranceDate, strEntranceDate.c_str(), sizeof(itFind->m_szEntranceDate));
	}
	else if (strUpdateField == "出生日期")
	{
		std::cout << "输入新出生日期:";
		std::cin >> strBornDate;
		SetAndCheckCharParam(itFind->m_szBornDate, strBornDate.c_str(), sizeof(itFind->m_szBornDate));
	}
	else if (strUpdateField == "家庭地址")
	{
		std::cout << "输入新家庭地址:";
		std::cin >> strAddress;
		SetAndCheckCharParam(itFind->m_szAddress, strAddress.c_str(), sizeof(itFind->m_szAddress));
	}
	else if (strUpdateField == "手机")
	{
		std::cout << "输入新手机:";
		std::cin >> strPhone;
		SetAndCheckCharParam(itFind->m_szPhone, strPhone.c_str(), sizeof(itFind->m_szPhone));
	}
	else {
		throw std::exception("输入错误：无此项");
	}

	//检测输入流是否有错误
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}
	//保存到文件中
	CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);				
	
	return false;
}
bool zhu::CStudentManager::OnSearchByNo(std::vector<CStudent>& vecStudent, std::vector<CStudent>::iterator& itFind)
{
	zhu::CStudentManager::Print(*itFind);
	return false;
}
bool zhu::CStudentManager::OnSearchByChar(std::vector<CStudent>& vecStudent, std::vector<CStudent>::iterator& itFind)
{
	zhu::CStudentManager::Print(*itFind);
	//姓名和班级可能相同继续查找
	return true;
}
bool zhu::CStudentManager::OnAddSearchClass(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	//将该学号添加到班级中
	itFind->m_vecStudentNo.push_back(nTempNo);
	//保存
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);
	return false;
}
bool zhu::CStudentManager::OnDelSearchClass(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	std::vector<int>& vecNo = itFind->m_vecStudentNo;
	//删除该学号
	for (std::vector<int>::iterator it = vecNo.begin(); it != vecNo.end(); it++) {
		if (*it == nTempNo) {
			//擦除该学号
			vecNo.erase(it);
			break;
		}
	}
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);
	return false;
}

//	重写方法
void zhu::CStudentManager::Add()
{
	// 输入
	int nStudentNo;
	std::string strSex;
	std::string strClassName;
	std::string strStuentName;
	std::string strNation;
	std::string strNativePlace;
	std::string strEntranceDate;
	std::string strBornDate;
	std::string strAddress;
	std::string strPhone;

	std::cout << "输入学号:";
	std::cin >> nStudentNo;
	nTempNo = nStudentNo;
	CheckInput();
	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw KeyUniqueException("学号");
	std::cout << "输入姓名:";
	std::cin >> strStuentName;
	SetAndCheckCharParam(NULL, strStuentName.c_str(), sizeof(CStudent::m_szStuentName));
	std::cout << "输入性别:";
	std::cin >> strSex;
	std::cout << "输入班级:";
	std::cin >> strClassName;
	SetAndCheckCharParam(NULL, strClassName.c_str(), sizeof(CStudent::m_szClassName));
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, OnAddSearchClass))
		throw NotFoundException("班级");
	std::cout << "输入名族:";
	std::cin >> strNation;
	SetAndCheckCharParam(NULL, strNation.c_str(), sizeof(CStudent::m_szNation));
	std::cout << "输入籍贯:";
	std::cin >> strNativePlace;
	SetAndCheckCharParam(NULL, strNativePlace.c_str(), sizeof(CStudent::m_szNativePlace));
	std::cout << "输入入学日期:";
	std::cin >> strEntranceDate;
	SetAndCheckCharParam(NULL, strEntranceDate.c_str(), sizeof(CStudent::m_szEntranceDate));
	std::cout << "输入出生日期:";
	std::cin >> strBornDate;
	SetAndCheckCharParam(NULL, strBornDate.c_str(), sizeof(CStudent::m_szBornDate));
	std::cout << "输入家庭地址:";
	std::cin >> strAddress;
	SetAndCheckCharParam(NULL, strAddress.c_str(), sizeof(CStudent::m_szAddress));
	std::cout << "输入手机:";
	std::cin >> strPhone;
	SetAndCheckCharParam(NULL, strPhone.c_str(), sizeof(CStudent::m_szPhone));

	//创建对象
	CStudent objStudent(nStudentNo, (strSex == "男" ? Sex::MAN : Sex::WOMAN), strClassName.c_str(), strStuentName.c_str(),
		strNation.c_str(), strNativePlace.c_str(), strEntranceDate.c_str(), strBornDate.c_str(), strAddress.c_str(), strPhone.c_str());	
	//添加
	CFileHelper::Append<CStudent>(STUDENT_FILE_NAME, objStudent);
	std::cout << "添加成功" << std::endl;
}
void zhu::CStudentManager::Del()
{
	int nStudentNo;
	std::cout << "输入学号:";
	std::cin >> nStudentNo;

	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, OnDelete))
		std::cout << "删除成功" << std::endl;
	else
		std::cout << "删除失败" << std::endl;
}
void zhu::CStudentManager::Update()
{
	int nStudentNo;
	std::cout << "输入学号:";
	std::cin >> nStudentNo;

	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, OnUpdate))
		std::cout << "修改成功" << std::endl;
	else
		std::cout << "修改失败" << std::endl;
}
void zhu::CStudentManager::Search()
{
	SearchMenu();	//进入查找菜单
}

//	私有方法
void zhu::CStudentManager::SearchMenu()
{
	int nChoose;
	std::cout << ">查询学生信息（返回请按其他任意键）：" << std::endl;
	std::cout << "	  1.通过姓名查找" << std::endl;
	std::cout << "	  2.通过学号查找" << std::endl;
	std::cout << "	  3.通过班级查找" << std::endl;
	std::cout << "	  4.查询所有" << std::endl;

	std::cin >> nChoose;
	system("cls");		//清屏

	switch (nChoose)
	{
	case 1:
		SearchByName();
		break;
	case 2:
		SearchByNo();
		break;
	case 3:
		SearchByClass();
		break;
	case 4:
		SearchAll();
		break;
	default:
		break;
	}
}
void zhu::CStudentManager::SearchByNo()
{
	int nStudentNo;
	std::cout << "输入学号:";
	std::cin >> nStudentNo;

	if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, OnSearchByNo))
		std::cout << "无记录" << std::endl;
}
void zhu::CStudentManager::SearchByName()
{
	std::string nStudentName;

	std::cout << "输入姓名:";
	std::cin >> nStudentName;

	if (!IManager::Search<CStudent>(nStudentName.c_str(), STUDENT_FILE_NAME, CStudent::compareStudentName, OnSearchByChar))
		std::cout << "无记录" << std::endl;
}
void zhu::CStudentManager::SearchByClass()
{
	std::string nClassName;
	bool bFind = false;

	std::cout << "输入班级:";
	std::cin >> nClassName;

	if (!IManager::Search<CStudent>(nClassName.c_str(), STUDENT_FILE_NAME, CStudent::compareClassName, OnSearchByChar))
		std::cout << "无记录" << std::endl;
}
void zhu::CStudentManager::SearchAll()
{
	std::vector<CStudent>* vector = CFileHelper::ReadAll<CStudent>(STUDENT_FILE_NAME);
	Print(vector);
	delete vector;
}
