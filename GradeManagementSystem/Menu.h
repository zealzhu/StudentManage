#pragma once
//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: �˵���
//////////////////////////////////////////////////

#ifndef _ZHU_MENU_H
#define _ZHU_MENU_H

#include "Manager.h"
#include "ManagerFactory.h"

namespace zhu
{
	class CMenu
	{
	private:
		bool SecondMenu(int nFirstChoose);		//�����˵�
	public:
		bool FirstMenu();						//һ���˵�
	};
}

#endif // !_ZHU_MENU_H
