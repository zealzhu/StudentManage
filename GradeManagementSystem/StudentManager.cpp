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

	std::cout << "����������:";
	std::cin >> strStuentName;
	std::cout << "�������Ա�:";
	std::cin >> strSex;
	std::cout << "�����°༶:";
	std::cin >> strClassName;
	if ((strcmp(itFind->m_szClassName, strClassName.c_str())) != 0)			//�ж��Ƿ��µİ༶
	{
		if (!IManager::Search<CClass>(strClassName.c_str(),					//���°༶���Ҹð༶�����ѧ����Ϣ
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
		
	std::cout << "����������:";
	std::cin >> strNation;
	std::cout << "�����¼���:";
	std::cin >> strNativePlace;
	std::cout << "��������ѧ����:";
	std::cin >> strEntranceDate;
	std::cout << "�����³�������:";
	std::cin >> strBornDate;
	std::cout << "�����¼�ͥ��ַ:";
	std::cin >> strAddress;
	std::cout << "�������ֻ�:";
	std::cin >> strPhone;

	//��������Ƿ��д���
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

	strcpy(itFind->m_szStuentName, strStuentName.c_str());
	itFind->m_emSex = (strSex == "��") ? Sex::MAN : Sex::WOMAN;
	strcpy(itFind->m_szClassName, strClassName.c_str());
	strcpy(itFind->m_szNation, strNation.c_str());
	strcpy(itFind->m_szNativePlace, strNativePlace.c_str());
	strcpy(itFind->m_szEntranceDate, strEntranceDate.c_str());
	strcpy(itFind->m_szBornDate, strBornDate.c_str());
	strcpy(itFind->m_szAddress, strAddress.c_str());
	strcpy(itFind->m_szPhone, strPhone.c_str());

	CFileHelper::Save(STUDENT_FILE_NAME, vecStudent);				//���浽�ļ���
	
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
	if (IManager::Search<CStudent>(nStudentNo, STUDENT_FILE_NAME, CStudent::compareStudentNo, NULL))
		throw KeyUniqueException("ѧ��");
	std::cout << "��������:";
	std::cin >> strStuentName;
	std::cout << "�����Ա�:";
	std::cin >> strSex;
	std::cout << "����༶:";
	std::cin >> strClassName;
	if (!IManager::Search<CClass>(strClassName.c_str(), CLASS_FILE_NAME, CClass::compareClassName, OnAddSearchClass))
		throw NotFoundException("�༶");
	std::cout << "��������:";
	std::cin >> strNation;
	std::cout << "���뼮��:";
	std::cin >> strNativePlace;
	std::cout << "������ѧ����:";
	std::cin >> strEntranceDate;
	std::cout << "�����������:";
	std::cin >> strBornDate;
	std::cout << "�����ͥ��ַ:";
	std::cin >> strAddress;
	std::cout << "�����ֻ�:";
	std::cin >> strPhone;
	
	if (std::cin.fail()) {
		std::cin.clear(std::istream::goodbit);
		std::cin.ignore(1024, '\n');
		system("cls");
		throw InputException();
	}

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


