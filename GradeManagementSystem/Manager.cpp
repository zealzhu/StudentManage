#include "Manager.h"

// 管理菜单
int zhu::IManager::Menu()
{
	int nChoose;

	std::cout << "*****************************" << std::endl;
	std::cout << "*         1.添加            *" << std::endl;
	std::cout << "*         2.删除            *" << std::endl;
	std::cout << "*         3.修改            *" << std::endl;
	std::cout << "*         4.查询            *" << std::endl;
	std::cout << "*         0.退出            *" << std::endl;
	std::cout << "*****************************" << std::endl;

	std::cin >> nChoose;
	return nChoose;
}
