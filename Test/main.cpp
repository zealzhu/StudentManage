#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

template<class T>
void Save(string strFileName, vector<T>& vec)
{
	//���ļ�
	std::ofstream file(strFileName, std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	int size = vec.size();
	file.write((char *)&size, sizeof(int));
	int writeSize = size * sizeof(T);
	file.write((char *)&vec[0], writeSize);

	//�ر�
	file.close();
}

template<class T>
vector<T>* ReadAll(std::string strFileName)
{
	//���ļ�
	std::ifstream file(strFileName, std::ios::in | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	//������
	int size;
	file.read((char *)&size, sizeof(int));
	vector<T>* vec = new vector<T>(size);
	int readSize = size * sizeof(T);
	file.read((char *)&((*vec)[0]), readSize);

	//�ر�
	file.close();
	return vec;
}

template<class T>
void Append(std::string strFileName, const T & obj)
{
	//���ļ�
	std::fstream file(strFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	//��ȡ����
	int nSize = 0;
	file.read((char *)&nSize, sizeof(int));
	//д����
	nSize++;
	file.seekp(0, std::ios::beg);
	file.write((char *)&nSize, sizeof(int));
	//д����
	file.seekp(0, std::ios::end);
	file.write((char *)&obj, sizeof(T));

	//�ر�
	file.close();
}

class A {
public:
	A() {}
	A(int a, const char* b)
	{
		this->a = a;
		strcpy(this->b, b);
	}
	int a;
	char b[15];
	vector<int> c;
};

void main()
{
	//���ļ�
	std::fstream file("ab.data", std::ios::out | std::ios::binary);
	if (!file) {
		std::cout << "�ļ���ʧ��" << endl;
		return;
	}
		
	int rp = 0;
	int wp = 0;
	//��ȡ����
	int nSize = 0;
	file.seekp(0, ios::end);
	wp = file.tellp();
	if (wp != 0) {
		file.read((char *)&nSize, sizeof(int));
	}
	
	rp = file.tellg();
	wp = file.tellg();
	//д����
	nSize++;
	file.seekp(0, std::ios::beg);												//��λ��ͷ
	file.write((char *)&nSize, sizeof(int));
	nSize = 0;
	file.seekg(0, std::ios::beg);
	file.read((char *)&nSize, sizeof(int));
	
	file.close();
	system("pause");
}