#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void function(int a) {
	std::cout << "参数开始地址:" << &a << endl;
}

void main()
{
	int nStudentNo;
	map<int, string> maps;
	maps.insert(map<int, string>::value_type(1, "32"));
	;
	pair<map<int, string>::iterator, bool > ret = maps.insert(map<int, string>::value_type(2, "342"));
	std::cout << ret.second << endl;
	system("pause");
}