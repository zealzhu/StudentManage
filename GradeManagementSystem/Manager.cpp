#include "Manager.h"

//  ����˵�
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

//	����ַ�����
void zhu::SetAndCheckCharParam(char* szDestination, const char* szSource, int nSize)
{
	if (strlen(szSource) >= nSize)
		if (szSource[nSize - 1] != '\0')
			throw std::exception("����������볤�ȳ�������");	
	if(szDestination != NULL)
		strcpy(szDestination, szSource);
}

//	���int����
void zhu::CheckInput()
{
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}
}