#include "FileHelper.h"

//ģ��ʵ��
template<class T>
void zhu::CFileHelper<T>::Save(std::string strFileName, std::vector<T>& vec)
{
	//���ļ�
	std::ofstream file(strFileName, std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	int nSize = vec.size();
	file.write((char *)&nSize, sizeof(int));
	if (nSize != 0)
		file.write((char *)&vec[0], vec.size() * sizeof(T));

	//�ر�
	file.close();
}
template<class T>
void zhu::CFileHelper<T>::Append(std::string strFileName, const T & obj)
{
	//���ļ�
	std::fstream file(strFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	//��ȡ����
	int nSize = 0;
	file.seekp(0, std::ios::end);
	int nFileLength = file.tellp();
	if (nFileLength != 0) {
		file.seekg(0, std::ios::beg);
		file.read((char *)&nSize, sizeof(int));
	}

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
template<class T>
std::vector<T>* zhu::CFileHelper<T>::ReadAll(std::string strFileName)
{
	if (GRADE_FILE_NAME == strFileName || CLASS_FILE_NAME == strFileName)
		return ReadHasVectorAll<T>(strFileName);

	//���ļ�
	std::ifstream file(strFileName, std::ios::in | std::ios::binary);
	if (!file)
	{
		//	û���ļ�����һ���ļ�
		std::ofstream of(strFileName, std::ios::out | std::ios::binary);
		if (!of)
			throw std::exception("�ļ�����ʧ��");
		of.close();

		return ReadAll<T>(strFileName);
	}

	//������
	int size = 0;
	file.read((char *)&size, sizeof(int));
	std::vector<T>* vector = new std::vector<T>(size);
	if (size != 0)
	{
		file.read((char *)&((*vector)[0]), size * sizeof(T));
	}

	//�ر�
	file.close();
	return vector;
}

template<class T>
void zhu::CFileHelper<T>::SaveHasVector(std::string strFileName, std::vector<T>& vec)
{
	//���ļ�
	std::ofstream file(strFileName, std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	//д����
	int nSize = vec.size();
	file.write((char *)&nSize, sizeof(int));
	for (std::vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		//д������Ϣ
		file.write((char *)&(*it), sizeof(T) - sizeof(std::vector<int>));
		//��ȡvectorԪ��
		char* bfAddress = (char*)&(*it);											//��ȡ��Ԫ�ص�ַ
		char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);	//����Ԫ����vector��ַ
		std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);			//ת��Ϊvectorָ��
																				//д��vectorԪ������
		int nTempSize = vecTemp->size();
		file.write((char *)&nTempSize, sizeof(int));
		//д������ֵ
		if (nTempSize != 0)
			file.write((char *)((*vecTemp)[0]), sizeof(int) * nTempSize);
	}
	//�ر�
	file.close();
}
template<class T>
void zhu::CFileHelper<T>::AppendHasVector(std::string strFileName, const T & obj)
{
	//���ļ�
	std::fstream file(strFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("�ļ���ʧ��");

	//��ȡ����
	int nSize = 0;
	file.seekp(0, std::ios::end);
	int nFileLength = file.tellp();
	if (nFileLength != 0) {
		file.seekg(0, std::ios::beg);
		file.read((char *)&nSize, sizeof(int));
	}
	//д����
	nSize++;
	file.seekp(0, std::ios::beg);												//��λ��ͷ
	file.write((char *)&nSize, sizeof(int));
	//д����
	file.seekp(0, std::ios::end);												//��λ��β��
																				//д������Ϣ
	file.write((char *)&obj, sizeof(T) - sizeof(std::vector<int>));
	//��ȡvectorԪ��
	char* bfAddress = (char*)&obj;												//��ȡ��Ԫ�ص�ַ
	char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);		//����Ԫ����vector��ַ
	std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);				//ת��Ϊvectorָ��
																				//д��vectorԪ������
	int nTempSize = vecTemp->size();
	file.write((char *)&nTempSize, sizeof(int));
	if (nTempSize != 0) {
		//д������ֵ
		file.write((char *)((*vecTemp)[0]), sizeof(int) * nTempSize);
	}

	//�ر�
	file.close();
}
template<class T>
std::vector<T>* zhu::CFileHelper<T>::ReadHasVectorAll(std::string strFileName)
{
	//���ļ�
	std::ifstream file(strFileName, std::ios::in | std::ios::binary);
	if (!file)
	{
		//	û���ļ�����һ���ļ�
		std::ofstream of(strFileName, std::ios::out | std::ios::binary);
		if (!of)
			throw std::exception("�ļ�����ʧ��");
		of.close();

		return ReadHasVectorAll<T>(strFileName);
	}

	//������
	int nSize = 0;
	file.read((char *)&nSize, sizeof(int));
	//������
	std::vector<T>* vecData = new std::vector<T>(nSize);
	if (nSize != 0)
	{
		for (std::vector<T>::iterator it = vecData->begin(); it != vecData->end(); it++)
		{
			//��������Ϣ
			file.read((char *)&(*it), sizeof(T) - sizeof(std::vector<int>));
			//������
			int nTempSize = 0;
			file.read((char *)&nTempSize, sizeof(int));
			//��ȡvector��ַ
			char* bfAddress = (char*)&(*it);											//��ȡ��Ԫ�ص�ַ
			char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);		//����Ԫ����vector��ַ
			std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);				//ת��Ϊvectorָ��
			if (nTempSize != 0)
			{
				//������Ԫ��
				file.read((char *)((*vecTemp)[0]), sizeof(int) * nTempSize);
			}

		}
	}

	//�ر�
	file.close();
	return vecData;
}