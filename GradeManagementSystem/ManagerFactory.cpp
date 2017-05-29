#include "ManagerFactory.h"

zhu::CFactoryManager * zhu::CFactoryManager::s_pInstance = nullptr;

zhu::CFactoryManager * zhu::CFactoryManager::GetInstance()
{
	if (s_pInstance == nullptr) {
		s_pInstance = new CFactoryManager();
	}

	return s_pInstance;
}
zhu::CFactoryManager::CFactoryManager() {}


zhu::IManager * zhu::CFactoryManager::GetManager(int nChoose)
{
	IManager* manager;
	switch (nChoose)
	{
	case 1:
		manager = new CStudentManager();
		break;
	case 2:
		manager = new CClassManager();
		break;
	case 3:
		manager = new CGradeManager();
		break;
	case 4:
		manager = new CCourseManager();
		break;
	case 5:
		manager = new CTestSubjectManager();
		break;
	case 6:
		manager = new CScoreManager();
		break;
	default:
		break;
	}
	return manager;
}

zhu::CFactoryManager::CReleaseInstance::~CReleaseInstance()
{
	//ÊÍ·ÅÊµÀý
	if (zhu::CFactoryManager::s_pInstance)
		delete zhu::CFactoryManager::s_pInstance;
}
