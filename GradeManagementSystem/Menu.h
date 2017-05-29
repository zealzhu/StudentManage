#pragma once
//////////////////////////////////////////////////
// Author:	朱鹏程
// Created:	2017/05/24
// Describe: 菜单类
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
		bool SecondMenu(int nFirstChoose);		//二级菜单
	public:
		bool FirstMenu();						//一级菜单
	};
}

#endif // !_ZHU_MENU_H
