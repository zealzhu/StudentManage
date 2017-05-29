#pragma once
//////////////////////////////////////////////////
// Author:	朱鹏程
// Created:	2017/05/24
// Describe: 管理工厂类，简单工厂+单例模式。用来获取管理类
//////////////////////////////////////////////////

#ifndef _ZHU_MANAGER_FACTORY_H
#define _ZHU_MANAGER_FACTORY_H

#include "Manager.h"

namespace zhu
{
	class CFactoryManager
	{
	private:
		//静态实例
		static CFactoryManager* s_pInstance;

	public:
		//获取实例
		static CFactoryManager* GetInstance();

	private:
		CFactoryManager();

	private:
		//用于自动释放实例的回收类
		class CReleaseInstance
		{
		public:
			~CReleaseInstance();
		};
		//程序结束时会调用静态成员的析构函数
		static CReleaseInstance s_releastInstance;
	public:
		IManager* GetManager(int nChoose);
	};
}

#endif // !_ZHU_MANAGER_FACTORY_H
