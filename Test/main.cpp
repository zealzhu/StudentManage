#include "FileHelper.h"

using namespace zhu;
using namespace std;
template<class T>
struct OnSearch
{
	typedef bool(*SEARCH_SUCCESS)(std::vector<T>&, typename std::vector<T>::iterator&, int nNo);		//��ѯ�ص�����
	typedef bool(*COMPARE_BY_NO)(int, T&);													//int�ȽϺ���
	typedef bool(*COMPARE_BY_CHAR)(const char*, T&);										//�ַ��ȽϺ���
};
template<class T>
bool Search(const char* szName,
	std::string strFileName,
	typename OnSearch<T>::COMPARE_BY_CHAR compare,
	typename OnSearch<T>::SEARCH_SUCCESS callback,
	int nNo)
{
	bool bFind = false;

	//��ȡ��Ϣ
	std::vector<T>* vector = CFileHelper::ReadAll<T>(strFileName);

	//����
	std::vector<T>::iterator it;
	for (it = vector->begin(); it != vector->end(); it++)
	{
		if (compare(szName, *it))
		{
			bFind = true;
			if (callback != NULL) {
				//	�лص�ִ�лص�
				if (!callback(*vector, it, nNo))
					break;
			}
			else
			{
				break;
			}
		}
	}
	delete vector;

	return bFind;
}
bool OnAddSearchClass(std::vector<zhu::CClass>& vecClass,
	std::vector<zhu::CClass>::iterator& itFind,
	int nNo)
{
	//����ѧ����ӵ��༶��
	itFind->m_vecStudentNo.push_back(nNo);
	//����
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);
	return false;
}
void ReadScore()
{
	ifstream file("����ɼ�.txt", ios::in);
	if (!file)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	int nStudentNo;
	int nTestSubjectNo;
	std::string strStuentName;
	std::string strClassName;
	std::string strCourseName;
	float fScore;
	vector<CScore> vecScore;
	while (!file.eof())
	{
		file >> nTestSubjectNo >> nStudentNo >> strStuentName
			>> strClassName >> strCourseName >> fScore;
		CScore objScore(nTestSubjectNo, nStudentNo, strStuentName.c_str(),
			strCourseName.c_str(), strClassName.c_str(), fScore);
		vecScore.push_back(objScore);
	}
	CFileHelper::Save<CScore>(SCORE_FILE_NAME, vecScore);
	file.close();
}

void ReadClassFromFile()
{
	ifstream file("����༶.txt", ios::in);
	if (!file)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	int nClassNo;
	std::string strClassName;
	vector<CClass> vecClass;
	while (!file.eof())
	{
		file >> nClassNo >> strClassName;
		CClass objClass(nClassNo, strClassName.c_str());
		vecClass.push_back(objClass);
	}
	CFileHelper::SaveHasVector<CClass>(CLASS_FILE_NAME, vecClass);
	file.close();
}
void ReadStudentFromFile()
{
	ifstream file("����ѧ��.txt", ios::in);
	if (!file)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	int nStudentNo;
	char strSex[20];
	char strClassName[20];
	char strStuentName[20];
	char strNation[20];
	char strNativePlace[20];
	char strEntranceDate[20];
	char strBornDate[20];
	char strAddress[20];
	char strPhone[20];
	vector<CStudent> vecStudent;
	while (!file.eof())
	{
		file >> nStudentNo >> strStuentName >> strSex >> strClassName
			>> strNation >> strNativePlace
			>> strEntranceDate >> strBornDate >> strAddress
			>> strPhone;
		CStudent objStudent(nStudentNo, (strcmp(strSex,"��") == 0 ? Sex::MAN : Sex::WOMAN), strClassName, strStuentName,
			strNation, strNativePlace, strEntranceDate, strBornDate, strAddress, strPhone);
		vecStudent.push_back(objStudent);
		Search<CClass>(strClassName, CLASS_FILE_NAME, CClass::compareClassName, OnAddSearchClass, nStudentNo);
	}
	CFileHelper::Save<CStudent>(STUDENT_FILE_NAME, vecStudent);

	file.close();
}
void ReadCourseFromFile()
{
	ifstream file("����γ�.txt", ios::in);
	if (!file)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	int nCourseNo;
	std::string strCourseName;
	int nCourseType;
	std::string strDescription;
	vector<CCourse> vecCourse;
	while (!file.eof())
	{
		file >> nCourseNo >> strCourseName >> nCourseType >> strDescription;
		CCourse objCourse(nCourseNo, strCourseName.c_str(), strDescription.c_str(), CourseType(nCourseType));
		vecCourse.push_back(objCourse);
	}
	CFileHelper::Save<CCourse>(COURSE_FILE_NAME, vecCourse);
	file.close();
}
void ReadTestSubject()
{
	ifstream file("���뿼�Կ�Ŀ.txt", ios::in);
	if (!file)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	int nTestSubjectNo;
	std::string strTestSubjectName;
	std::string strCourseName;
	vector<CTestSubject> vecTestSubject;
	while (!file.eof())
	{
		file >> nTestSubjectNo >> strTestSubjectName >> strCourseName;
		CTestSubject objTestSubject(nTestSubjectNo, strTestSubjectName.c_str(), strCourseName.c_str());
		vecTestSubject.push_back(objTestSubject);
	}
	CFileHelper::Save<CTestSubject>(TEST_SUBJECT_FILE_NAME, vecTestSubject);
	file.close();
}

void main()
{
	ReadClassFromFile();
	ReadStudentFromFile();
	ReadCourseFromFile();
	ReadTestSubject();
	ReadScore();
}