#include "Manager.h"

//  管理菜单
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

//	检测字符参数
void zhu::SetAndCheckCharParam(char* szDestination, const char* szSource, int nSize)
{
	if (strlen(szSource) >= nSize)
		if (szSource[nSize - 1] != '\0')
			throw std::exception("输入错误：输入长度超出限制");	
	if(szDestination != NULL)
		strcpy(szDestination, szSource);
}

//	检测int参数
void zhu::CheckInput()
{
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}
}