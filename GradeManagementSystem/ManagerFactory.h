#pragma once
//////////////////////////////////////////////////
// Author:	������
// Created:	2017/05/24
// Describe: �������࣬�򵥹���+����ģʽ��������ȡ������
//////////////////////////////////////////////////

#ifndef _ZHU_MANAGER_FACTORY_H
#define _ZHU_MANAGER_FACTORY_H

#include "Manager.h"

namespace zhu
{
	class CFactoryManager
	{
	private:
		//��̬ʵ��
		static CFactoryManager* s_pInstance;

	public:
		//��ȡʵ��
		static CFactoryManager* GetInstance();

	private:
		CFactoryManager();

	private:
		//�����Զ��ͷ�ʵ���Ļ�����
		class CReleaseInstance
		{
		public:
			~CReleaseInstance();
		};
		//�������ʱ����þ�̬��Ա����������
		static CReleaseInstance s_releastInstance;
	public:
		IManager* GetManager(int nChoose);
	};
}

#endif // !_ZHU_MANAGER_FACTORY_H
