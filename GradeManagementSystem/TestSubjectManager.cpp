///////////////////////////////////////
// ¿¼ÊÔ¿ÆÄ¿¹ÜÀí·½·¨
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
	lstTestSubject.erase(itFind);																	//ÒÆ³ý		
	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, lstTestSubject);						//±£´æ
	return false;
}
bool zhu::CTestSubjectManager::OnUpdate(std::list<zhu::CTestSubject>& lstTestSubject,
	std::list<zhu::CTestSubject>::iterator& itFind)
{
	int nTestSubjectNo;
	std::string strTestSubjectName;
	std::string strCourseName;

	std::cout << "ÊäÈë¿¼ÊÔ±àºÅ:";
	std::cin >> nTestSubjectNo;
	std::cout << "ÊäÈë¿¼ÊÔÃû³Æ:";
	std::cin >> strTestSubjectName;
	std::cout << "ÊäÈë¿¼ÊÔ¿ÆÄ¿:";
	std::cin >> strCourseName;

	itFind->m_nTestSubjectNo = nTestSubjectNo;
	strcpy(itFind->m_szTestSubjectName, strTestSubjectName.c_str());
	strcpy(itFind->m_szCourseName, strCourseName.c_str());

	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, lstTestSubject);						//±£´æ

	return false;
}


void zhu::CTestSubjectManager::Add()
{
	int nTestSubjectNo;
	std::string strTestSubjectName;
	std::string strCourseName;

	std::cout << "ÊäÈë¿¼ÊÔ±àºÅ:";
	std::cin >> nTestSubjectNo;
	std::cout << "ÊäÈë¿¼ÊÔÃû³Æ:";
	std::cin >> strTestSubjectName;
	std::cout << "ÊäÈë¿¼ÊÔ¿ÆÄ¿";
	std::cin >> strCourseName;

	CTestSubject objTestSubject(nTestSubjectNo, strTestSubjectName.c_str(), strCourseName.c_str());
	if (CFileHelper::Append<CTestSubject>(TEST_SUBJECT_FILE_NAME, objTestSubject))
		std::cout << "Ìí¼Ó³É¹¦" << std::endl;
	else
		std::cout << "Ìí¼ÓÊ§°Ü" << std::endl;
}
void zhu::CTestSubjectManager::Del()
{
	int nTestSubjectNo;
	std::cout << "ÊäÈë¿¼ÊÔ±àºÅ:";
	std::cin >> nTestSubjectNo;

	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, OnDelete))
		std::cout << "É¾³ý³É¹¦" << std::endl;
	else
		std::cout << "É¾³ýÊ§°Ü" << std::endl;
}
void zhu::CTestSubjectManager::Update()
{
	int nTestSubjectNo;
	std::cout << "ÊäÈë¿¼ÊÔ±àºÅ:";
	std::cin >> nTestSubjectNo;

	if (IManager::Search<CTestSubject>(nTestSubjectNo, TEST_SUBJECT_FILE_NAME, CTestSubject::compareTestSubjectNo, OnUpdate))
		std::cout << "ÐÞ¸Ä³É¹¦" << std::endl;
	else
		std::cout << "ÐÞ¸ÄÊ§°Ü" << std::endl;
}
void zhu::CTestSubjectManager::Search()
{
	std::cout << std::left
		<< std::setw(10) << "¿¼ÊÔ±àºÅ"
		<< std::setw(10) << "¿¼ÊÔÃû³Æ"
		<< std::setw(10) << "¿¼ÊÔ¿ÆÄ¿"
		<< std::endl;

	std::list<CTestSubject>* list = CFileHelper::ReadAll<CTestSubject>(TEST_SUBJECT_FILE_NAME);
	Print(list);
	delete list;
}



