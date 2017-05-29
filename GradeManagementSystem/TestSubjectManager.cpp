///////////////////////////////////////
// øº ‘ø∆ƒøπ‹¿Ì∑Ω∑®
//////////////////////////////////////
#include "Manager.h"
void zhu::CTestSubjectManager::Print(std::list<zhu::CTestSubject>* list)
{
	std::list<zhu::CTestSubject>::iterator it;
	for (it = list->begin(); it != list->end(); it++)
	{
		std::cout << std::left << std::setw(10)
			<< std::setw(10) << it->m_nTestSubjectNo
			<< std::setw(10) << it->m_szTestSubjectName
			<< std::setw(10) << it->m_szCourseName
			<< std::endl;
	}
}
bool zhu::CTestSubjectManager::OnDelete(std::list<zhu::CTestSubject>& lstTestSubject, 
	std::list<zhu::CTestSubject>::iterator& itFind)
{
	lstTestSubject.erase(itFind);																	//“∆≥˝		
	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, lstTestSubject);						//±£¥Ê
	return false;
}
bool zhu::CTestSubjectManager::OnUpdate(std::list<zhu::CTestSubject>& lstTestSubject,
	std::list<zhu::CTestSubject>::iterator& itFind)
{
	int nTestSubjectNo;
	std::string strTestSubjectName;
	std::string strCourseName;

	std::cout << " ‰»Îøº ‘±‡∫≈:";
	std::cin >> nTestSubjectNo;
	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw KeyUniqueException("øº ‘±‡∫≈");
	std::cout << " ‰»Îøº ‘√˚≥∆:";
	std::cin >> strTestSubjectName;
	std::cout << " ‰»Îøº ‘ø∆ƒø:";
	std::cin >> strCourseName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	itFind->m_nTestSubjectNo = nTestSubjectNo;
	strcpy(itFind->m_szTestSubjectName, strTestSubjectName.c_str());
	strcpy(itFind->m_szCourseName, strCourseName.c_str());

	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, lstTestSubject);						//±£¥Ê

	return false;
}


void zhu::CTestSubjectManager::Add()
{
	int nTestSubjectNo;
	std::string strTestSubjectName;
	std::string strCourseName;

	std::cout << " ‰»Îøº ‘±‡∫≈:";
	std::cin >> nTestSubjectNo;
	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, NULL))
		throw KeyUniqueException("øº ‘±‡∫≈");
	std::cout << " ‰»Îøº ‘√˚≥∆:";
	std::cin >> strTestSubjectName;
	std::cout << " ‰»Îøº ‘ø∆ƒø";
	std::cin >> strCourseName;

	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	CTestSubject objTestSubject(nTestSubjectNo, strTestSubjectName.c_str(), strCourseName.c_str());
	CFileHelper::Append<CTestSubject>(TEST_SUBJECT_FILE_NAME, objTestSubject);
	std::cout << "ÃÌº”≥…π¶" << std::endl;
}
void zhu::CTestSubjectManager::Del()
{
	int nTestSubjectNo;
	std::cout << " ‰»Îøº ‘±‡∫≈:";
	std::cin >> nTestSubjectNo;

	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, OnDelete))
		std::cout << "…æ≥˝≥…π¶" << std::endl;
	else
		std::cout << "…æ≥˝ ß∞‹" << std::endl;
}
void zhu::CTestSubjectManager::Update()
{
	int nTestSubjectNo;
	std::cout << " ‰»Îøº ‘±‡∫≈:";
	std::cin >> nTestSubjectNo;

	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, OnUpdate))
		std::cout << "–ﬁ∏ƒ≥…π¶" << std::endl;
	else
		std::cout << "–ﬁ∏ƒ ß∞‹" << std::endl;
}
void zhu::CTestSubjectManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "øº ‘±‡∫≈"
		<< std::setw(10) << "øº ‘√˚≥∆"
		<< std::setw(10) << "øº ‘ø∆ƒø"
		<< std::endl;

	std::list<CTestSubject>* list = CFileHelper::ReadAll<CTestSubject>(TEST_SUBJECT_FILE_NAME);
	Print(list);
	delete list;
}



