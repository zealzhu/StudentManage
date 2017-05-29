#include "FileHelper.h"

//模板实现
template<class T>
void zhu::CFileHelper<T>::Save(std::string strFileName, std::vector<T>& vec)
{
	//打开文件
	std::ofstream file(strFileName, std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("文件打开失败");

	int nSize = vec.size();
	file.write((char *)&nSize, sizeof(int));
	if (nSize != 0)
		file.write((char *)&vec[0], vec.size() * sizeof(T));

	//关闭
	file.close();
}
template<class T>
void zhu::CFileHelper<T>::Append(std::string strFileName, const T & obj)
{
	//打开文件
	std::fstream file(strFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("文件打开失败");

	//读取数量
	int nSize = 0;
	file.seekp(0, std::ios::end);
	int nFileLength = file.tellp();
	if (nFileLength != 0) {
		file.seekg(0, std::ios::beg);
		file.read((char *)&nSize, sizeof(int));
	}

	//写数量
	nSize++;
	file.seekp(0, std::ios::beg);
	file.write((char *)&nSize, sizeof(int));
	//写数据
	file.seekp(0, std::ios::end);
	file.write((char *)&obj, sizeof(T));

	//关闭
	file.close();
}
template<class T>
std::vector<T>* zhu::CFileHelper<T>::ReadAll(std::string strFileName)
{
	if (GRADE_FILE_NAME == strFileName || CLASS_FILE_NAME == strFileName)
		return ReadHasVectorAll<T>(strFileName);

	//打开文件
	std::ifstream file(strFileName, std::ios::in | std::ios::binary);
	if (!file)
	{
		//	没有文件创建一个文件
		std::ofstream of(strFileName, std::ios::out | std::ios::binary);
		if (!of)
			throw std::exception("文件创建失败");
		of.close();

		return ReadAll<T>(strFileName);
	}

	//读数据
	int size = 0;
	file.read((char *)&size, sizeof(int));
	std::vector<T>* vector = new std::vector<T>(size);
	if (size != 0)
	{
		file.read((char *)&((*vector)[0]), size * sizeof(T));
	}

	//关闭
	file.close();
	return vector;
}

template<class T>
void zhu::CFileHelper<T>::SaveHasVector(std::string strFileName, std::vector<T>& vec)
{
	//打开文件
	std::ofstream file(strFileName, std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("文件打开失败");

	//写数量
	int nSize = vec.size();
	file.write((char *)&nSize, sizeof(int));
	for (std::vector<T>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		//写基本信息
		file.write((char *)&(*it), sizeof(T) - sizeof(std::vector<int>));
		//获取vector元素
		char* bfAddress = (char*)&(*it);											//获取该元素地址
		char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);	//计算元素中vector地址
		std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);			//转换为vector指针
																				//写出vector元素数量
		int nTempSize = vecTemp->size();
		file.write((char *)&nTempSize, sizeof(int));
		//写出具体值
		if (nTempSize != 0)
			file.write((char *)((*vecTemp)[0]), sizeof(int) * nTempSize);
	}
	//关闭
	file.close();
}
template<class T>
void zhu::CFileHelper<T>::AppendHasVector(std::string strFileName, const T & obj)
{
	//打开文件
	std::fstream file(strFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file)
		throw std::exception("文件打开失败");

	//读取数量
	int nSize = 0;
	file.seekp(0, std::ios::end);
	int nFileLength = file.tellp();
	if (nFileLength != 0) {
		file.seekg(0, std::ios::beg);
		file.read((char *)&nSize, sizeof(int));
	}
	//写数量
	nSize++;
	file.seekp(0, std::ios::beg);												//定位到头
	file.write((char *)&nSize, sizeof(int));
	//写数据
	file.seekp(0, std::ios::end);												//定位到尾部
																				//写基本信息
	file.write((char *)&obj, sizeof(T) - sizeof(std::vector<int>));
	//获取vector元素
	char* bfAddress = (char*)&obj;												//获取该元素地址
	char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);		//计算元素中vector地址
	std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);				//转换为vector指针
																				//写出vector元素数量
	int nTempSize = vecTemp->size();
	file.write((char *)&nTempSize, sizeof(int));
	if (nTempSize != 0) {
		//写出具体值
		file.write((char *)((*vecTemp)[0]), sizeof(int) * nTempSize);
	}

	//关闭
	file.close();
}
template<class T>
std::vector<T>* zhu::CFileHelper<T>::ReadHasVectorAll(std::string strFileName)
{
	//打开文件
	std::ifstream file(strFileName, std::ios::in | std::ios::binary);
	if (!file)
	{
		//	没有文件创建一个文件
		std::ofstream of(strFileName, std::ios::out | std::ios::binary);
		if (!of)
			throw std::exception("文件创建失败");
		of.close();

		return ReadHasVectorAll<T>(strFileName);
	}

	//读数量
	int nSize = 0;
	file.read((char *)&nSize, sizeof(int));
	//读数据
	std::vector<T>* vecData = new std::vector<T>(nSize);
	if (nSize != 0)
	{
		for (std::vector<T>::iterator it = vecData->begin(); it != vecData->end(); it++)
		{
			//读基本信息
			file.read((char *)&(*it), sizeof(T) - sizeof(std::vector<int>));
			//读数量
			int nTempSize = 0;
			file.read((char *)&nTempSize, sizeof(int));
			//获取vector地址
			char* bfAddress = (char*)&(*it);											//获取该元素地址
			char* bfVecAddress = bfAddress + sizeof(T) - sizeof(std::vector<int>);		//计算元素中vector地址
			std::vector<int>* vecTemp = (std::vector<int>*)(bfVecAddress);				//转换为vector指针
			if (nTempSize != 0)
			{
				//读具体元素
				file.read((char *)((*vecTemp)[0]), sizeof(int) * nTempSize);
			}

		}
	}

	//关闭
	file.close();
	return vecData;
}