#include "Menu.h"

bool zhu::CMenu::SecondMenu(int nFirstChoose)
{
	//	统计成绩
	if (nFirstChoose == 7) {
		CScoreManager scoreManager;
		scoreManager.Statistics();
		return false;
	}	
	
	int nManagerChoose;													//二级菜单选择
	
	CFactoryManager* pFactory = CFactoryManager::GetInstance();			//单例获取管理类工厂
	
	IManager* pManager = pFactory->GetManager(nFirstChoose);			//根据选择获取管理类
	
	nManagerChoose = pManager->Menu();									//管理类显示菜单，并获取选择

	system("cls");														//清屏

	if (0 == nManagerChoose) 
	{		
		delete pManager;												//退出二级菜单释放管理类
		return false;
	}
	
	try {
		switch (nManagerChoose)												//根据选择执行操作
		{
		case 1:
			pManager->Add();
			break;
		case 2:
			pManager->Del();
			break;
		case 3:
			pManager->Update();
			break;
		case 4:
			pManager->Search();
			break;
		default:
			break;
		}
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	
	return true;
}

bool zhu::CMenu::FirstMenu()
{
	int nFirstMenuChoose;	//一级菜单选择

	std::cout << "*    1.学生信息管理      *" << std::endl;
	std::cout << "*    2.班级信息管理      *" << std::endl;
	std::cout << "*    3.年段信息管理      *" << std::endl;
	std::cout << "*    4.课程信息管理      *" << std::endl;
	std::cout << "*    5.考试科目管理      *" << std::endl;
	std::cout << "*    6.学生成绩管理      *" << std::endl;
	std::cout << "*    7.统计信息          *" << std::endl;
	std::cout << "*    0.退出系统          *" << std::endl;
	std::cout << ":";
	std::cin >> nFirstMenuChoose;
	system("cls");		//清屏

	if (0 == nFirstMenuChoose) 
	{
		//退出系统
		return false;
	}

	//根据选择进入进入二级菜单
	while (SecondMenu(nFirstMenuChoose));
	
	return true;
}
