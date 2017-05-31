///////////////////////////////////////
// ѧ��������
//////////////////////////////////////
#include "Manager.h"

//	��ʱ��¼ѧ��
int nTempNo = 0;

//  ��ӡ
void zhu::CStudentManager::Print(CStudent& objStudent)
{
	std::cout << std::left
		<< std::setw(5) << objStudent.m_nStudentNo
		<< std::setw(10) << objStudent.m_szStuentName
		<< std::setw(10) << (objStudent.m_emSex == Sex::MAN ? "��" : "Ů")
		<< std::setw(10) << objStudent.m_szClassName
		<< std::setw(10) << objStudent.m_szNation
		<< std::setw(10) << objStudent.m_szNativePlace
		<< std::setw(13) << objStudent.m_szBornDate
		<< std::setw(13) << objStudent.m_szEntranceDate
		<< std::setw(18) << objStudent.m_szAddress
		<< std::setw(10) << objStudent.m_szPhone
		<< std::endl;
}
void zhu::CStudentManager::Print(std::vector<zhu::CStudent>* vector)
{
	std::cout << std::left
		<< std::setw(5) << "ѧ��"
		<< std::setw(10) << "����"
		<< std::setw(10) << "�Ա�"
		<< std::setw(10) << "�༶"
		<< std::setw(10) << "����"
		<< std::setw(10) << "����"
		<< std::setw(13) << "��������"
		<< std::setw(13) << "��ѧ����"
		<< std::setw(18) << "��ͥסַ"
		<< std::setw(10) << "��ϵ�绰"
		<< std::endl;

	std::vector<zhu::CStudent>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		std::cout << std::left
			<< std::setw(5) << it->m_nStudentNo
			<< std::setw(10) << it->m_szStuentName
			<< std::setw(10) << (it->m_emSex == Sex::MAN ? "��" : "Ů")
			<< std::setw(10) << it->m_szClassName
			<< std::setw(10) << it->m_szNation
			<< std::setw(10) << it->m_szNativePlace
			<< std::setw(13) << it->m_szBornDate
			<< std::setw(13) << it->m_szEntranceDate
			<< std::setw(18) << it->m_szAddress
			<< std::setw(10) << it->m_szPhone
			<< std::endl;
	}
}

//	�ص�����
bool zhu::CStudentManager::OnDelete(std::vector<CStudent>& vecStudent,  std::vector<CStudent>::iterator& itFind)
{
	//ɾ����Ӧ�༶�еĺ���
	IManager::Search<CClass>(itFind->m_szClassName, CLASS_FILE_NAME, CClass::compareClassName, OnDelSearchClass);
	//ɾ��ѧ��
	vecStudent.erase(itFind);
	zhu::CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);	
	return false;
}
bool zhu::CStudentManager::OnUpdate(std::vector<CStudent>& vecStudent, std::vector<CStudent>::iterator& itFind)
{
	std::string strSex;
	std::string strClassName;
	std::string strStuentName;
	std::string strNation;
	std::string strNativePlace;
	std::string strEntranceDate;
	std::string strBornDate;
	std::string strAddress;
	std::string strPhone;

	std::string strUpdateField;
	std::cout << "����Ҫ�޸ĵ���������Ա𣬰༶�����壬���ᣬ��ѧ���ڣ��������ڣ���ͥ��ַ���ֻ���:";
	std::cin >> strUpdateField;

	if (strUpdateField == "����") 
	{
		std::cout << "����������:";
		std::cin >> strStuentName;
		SetAndCheckCharParam(itFind->m_szStuentName, strStuentName.c_str(), sizeof(itFind->m_szStuentName));
	}
	else if (strUpdateField == "�Ա�")
	{
		std::cout << "�������Ա�:";
		std::cin >> strSex;
		itFind->m_emSex = (strSex == "��") ? Sex::MAN : Sex::WOMAN;
	}
	else if (strUpdateField == "�༶")
	{
		std::cout << "�����°༶:";
		std::cin >> strClassName;
		//�ж��Ƿ��µİ༶
		if ((strcmp(itFind->m_szClassName, strClassName.c_str())) != 0)			
		{
			//���°༶���Ҹð༶�����ѧ����Ϣ
			if (!IManager::Search<CClass>(strClassName.c_str(),					
				CLASS_FILE_NAME, CClass::compareClassName, OnAddSearchClass))
			{
				//û���ҵ��ð༶
				throw NotFoundException("�༶");
			}
			else
			{
				//����ɾ���ɰ༶�еļ�¼
				IManager::Search<CClass>(itFind->m_szClassName, CLASS_FILE_NAME,
					CClass::compareClassName, OnDelSearchClass);
			}
		}
		SetAndCheckCharParam(itFind->m_szClassName, strClassName.c_str(), sizeof(itFind->m_szClassName));
	}
	else if (strUpdateField == "����")
	{
		std::cout << "����������:";
		std::cin >> strNation;
		SetAndCheckCharParam(itFind->m_szNation, strNation.c_str(), sizeof(itFind->m_szNation));
	}
	else if (strUpdateField == "����")
	{
		std::cout << "�����¼���:";
		std::cin >> strNativePlace;
		SetAndCheckCharParam(itFind->m_szNativePlace, strNativePlace.c_str(), sizeof(itFind->m_szNativePlace));
	}
	else if (strUpdateField == "��ѧ����")
	{
		std::cout << "��������ѧ����:";
		std::cin >> strEntranceDate;
		SetAndCheckCharParam(itFind->m_szEntranceDate, strEntranceDate.c_str(), sizeof(itFind->m_szEntranceDate));
	}
	else if (strUpdateField == "��������")
	{
		std::cout << "�����³�������:";
		std::cin >> strBornDate;
		SetAndCheckCharParam(itFind->m_szBornDate, strBornDate.c_str(), sizeof(itFind->m_szBornDate));
	}
	else if (strUpdateField == "��ͥ��ַ")
	{
		std::cout << "�����¼�ͥ��ַ:";
		std::cin >> strAddress;
		SetAndCheckCharParam(itFind->m_szAddress, strAddress.c_str(), sizeof(itFind->m_szAddress));
	}
	else if (strUpdateField == "�ֻ�")
	{
		std::cout << "�������ֻ�:";
		std::cin >> strPhone;
		SetAndCheckCharParam(itFind->m_szPhone, strPhone.c_str(), sizeof(itFind->m_szPhone));
	}
	else {
		throw std::exception("��������޴���");
	}

	//����������Ƿ��д���
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}
	//���浽�ļ���
	CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);				
	
	return false;
}
bool zhu::CStudentManager::OnSearchByNo(std::vector<CStudent>& vecStudent, std::vector<CStudent>::iterator& itFind)
{
	zhu::CStudentManager::Print(*itFind);
	return false;
}
bool zhu::CStudentManager::OnSearchByChar(std::vector<CStudent>& vecStudent, std::vector<CStudent>::iterator& itFind)
{
	zhu::CStudentManager::Print(*itFind);
	//�����Ͱ༶������ͬ��������
	return true;
}
bool zhu::CStudentManager::OnAddSearchClass(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	//����ѧ����ӵ��༶��
	itFind->m_vecStudentNo.push_back(nTempNo);
	//����
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);
	return false;
}
bool zhu::CStudentManager::OnDelSearchClass(std::vector<zhu::CClass>& vecClass, std::vector<zhu::CClass>::iterator& itFind)
{
	std::vector<int>& vecNo = itFind->m_vecStudentNo;
	//ɾ����ѧ��
	for (std::vector<int>::iterator it = vecNo.begin(); it != vecNo.end(); it++) {
		if (*it == nTempNo) {
			//������ѧ��
			vecNo.erase(it);
			break;
		}
	}
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);
	return false;
}

//	��д����
void zhu::CStudentManager::Add()
{
	// ����
	int nStudentNo;
	std::string strSex;
	std::string strClassName;
	std::string strStuentName;
	std::string strNation;
	std::string strNativePlace;
	std::string strEntranceDate;
	std::string strBornDate;
	std::string strAddress;
	std::string strPhone;

	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;
	nTempNo = nStudentNo;
	CheckInput();
	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw KeyUniqueException("ѧ��");
	std::cout << "��������:";
	std::cin >> strStuentName;
	SetAndCheckCharParam(NULL, strStuentName.c_str(), sizeof(CStudent::m_szStuentName));
	std::cout << "�����Ա�:";
	std::cin >> strSex;
	std::cout << "����༶:";
	std::cin >> strClassName;
	SetAndCheckCharParam(NULL, strClassName.c_str(), sizeof(CStudent::m_szClassName));
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, OnAddSearchClass))
		throw NotFoundException("�༶");
	std::cout << "��������:";
	std::cin >> strNation;
	SetAndCheckCharParam(NULL, strNation.c_str(), sizeof(CStudent::m_szNation));
	std::cout << "���뼮��:";
	std::cin >> strNativePlace;
	SetAndCheckCharParam(NULL, strNativePlace.c_str(), sizeof(CStudent::m_szNativePlace));
	std::cout << "������ѧ����:";
	std::cin >> strEntranceDate;
	SetAndCheckCharParam(NULL, strEntranceDate.c_str(), sizeof(CStudent::m_szEntranceDate));
	std::cout << "�����������:";
	std::cin >> strBornDate;
	SetAndCheckCharParam(NULL, strBornDate.c_str(), sizeof(CStudent::m_szBornDate));
	std::cout << "�����ͥ��ַ:";
	std::cin >> strAddress;
	SetAndCheckCharParam(NULL, strAddress.c_str(), sizeof(CStudent::m_szAddress));
	std::cout << "�����ֻ�:";
	std::cin >> strPhone;
	SetAndCheckCharParam(NULL, strPhone.c_str(), sizeof(CStudent::m_szPhone));

	//��������
	CStudent objStudent(nStudentNo, (strSex == "��" ? Sex::MAN : Sex::WOMAN), strClassName.c_str(), strStuentName.c_str(),
		strNation.c_str(), strNativePlace.c_str(), strEntranceDate.c_str(), strBornDate.c_str(), strAddress.c_str(), strPhone.c_str());	
	//���
	CFileHelper::Append<CStudent>(STUDENT_FILE_NAME, objStudent);
	std::cout << "��ӳɹ�" << std::endl;
}
void zhu::CStudentManager::Del()
{
	int nStudentNo;
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;

	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, OnDelete))
		std::cout << "ɾ���ɹ�" << std::endl;
	else
		std::cout << "ɾ��ʧ��" << std::endl;
}
void zhu::CStudentManager::Update()
{
	int nStudentNo;
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;

	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, OnUpdate))
		std::cout << "�޸ĳɹ�" << std::endl;
	else
		std::cout << "�޸�ʧ��" << std::endl;
}
void zhu::CStudentManager::Search()
{
	SearchMenu();	//������Ҳ˵�
}

//	˽�з���
void zhu::CStudentManager::SearchMenu()
{
	int nChoose;
	std::cout << ">��ѯѧ����Ϣ�������밴�������������" << std::endl;
	std::cout << "	  1.ͨ����������" << std::endl;
	std::cout << "	  2.ͨ��ѧ�Ų���" << std::endl;
	std::cout << "	  3.ͨ���༶����" << std::endl;
	std::cout << "	  4.��ѯ����" << std::endl;

	std::cin >> nChoose;
	system("cls");		//����

	switch (nChoose)
	{
	case 1:
		SearchByName();
		break;
	case 2:
		SearchByNo();
		break;
	case 3:
		SearchByClass();
		break;
	case 4:
		SearchAll();
		break;
	default:
		break;
	}
}
void zhu::CStudentManager::SearchByNo()
{
	int nStudentNo;
	std::cout << "����ѧ��:";
	std::cin >> nStudentNo;

	if (!IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, OnSearchByNo))
		std::cout << "�޼�¼" << std::endl;
}
void zhu::CStudentManager::SearchByName()
{
	std::string nStudentName;

	std::cout << "��������:";
	std::cin >> nStudentName;

	if (!IManager::Search<CStudent>(nStudentName.c_str(), STUDENT_FILE_NAME, CStudent::compareStudentName, OnSearchByChar))
		std::cout << "�޼�¼" << std::endl;
}
void zhu::CStudentManager::SearchByClass()
{
	std::string nClassName;
	bool bFind = false;

	std::cout << "����༶:";
	std::cin >> nClassName;

	if (!IManager::Search<CStudent>(nClassName.c_str(), STUDENT_FILE_NAME, CStudent::compareClassName, OnSearchByChar))
		std::cout << "�޼�¼" << std::endl;
}
void zhu::CStudentManager::SearchAll()
{
	std::vector<CStudent>* vector = CFileHelper::ReadAll<CStudent>(STUDENT_FILE_NAME);
	Print(vector);
	delete vector;
}
