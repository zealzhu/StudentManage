#include "Menu.h"

bool zhu::CMenu::SecondMenu(int nFirstChoose)
{
	//	ͳ�Ƴɼ�
	if (nFirstChoose == 7) {
		CScoreManager scoreManager;
		scoreManager.Statistics();
		return false;
	}	
	
	int nManagerChoose;													//�����˵�ѡ��
	
	CFactoryManager* pFactory = CFactoryManager::GetInstance();			//������ȡ�����๤��
	
	IManager* pManager = pFactory->GetManager(nFirstChoose);			//����ѡ���ȡ������
	
	nManagerChoose = pManager->Menu();									//��������ʾ�˵�������ȡѡ��

	system("cls");														//����

	if (0 == nManagerChoose) 
	{		
		delete pManager;												//�˳������˵��ͷŹ�����
		return false;
	}
	
	try {
		switch (nManagerChoose)												//����ѡ��ִ�в���
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
	int nFirstMenuChoose;	//һ���˵�ѡ��

	std::cout << "*    1.ѧ����Ϣ����      *" << std::endl;
	std::cout << "*    2.�༶��Ϣ����      *" << std::endl;
	std::cout << "*    3.�����Ϣ����      *" << std::endl;
	std::cout << "*    4.�γ���Ϣ����      *" << std::endl;
	std::cout << "*    5.���Կ�Ŀ����      *" << std::endl;
	std::cout << "*    6.ѧ���ɼ�����      *" << std::endl;
	std::cout << "*    7.ͳ����Ϣ          *" << std::endl;
	std::cout << "*    0.�˳�ϵͳ          *" << std::endl;
	std::cout << ":";
	std::cin >> nFirstMenuChoose;
	system("cls");		//����

	if (0 == nFirstMenuChoose) 
	{
		//�˳�ϵͳ
		return false;
	}

	//����ѡ������������˵�
	while (SecondMenu(nFirstMenuChoose));
	
	return true;
}
