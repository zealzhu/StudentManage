#include "Manager.h"

// ����˵�
int zhu::IManager::Menu()
{
	int nChoose;

	std::cout << "*****************************" << std::endl;
	std::cout << "*         1.���            *" << std::endl;
	std::cout << "*         2.ɾ��            *" << std::endl;
	std::cout << "*         3.�޸�            *" << std::endl;
	std::cout << "*         4.��ѯ            *" << std::endl;
	std::cout << "*         0.�˳�            *" << std::endl;
	std::cout << "*****************************" << std::endl;

	std::cin >> nChoose;
	return nChoose;
}
