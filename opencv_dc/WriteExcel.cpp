#include <iostream>
#include <fstream>//fstream供给了三个类，用来实现c++对文件的操纵
#include <iomanip>

using namespace std;

int WriteExcel()
{
	ofstream File;//ofstream类实现向文件写内容
	File.open("H:\\test\\test.xls", ios::_Noreplace);//ios::_Noreplace 打开一个文件时，如果文件不存在，创建该文件
	char chy[4] = { 'x' ,'a' ,'h','w' };
	int data[4] = { 1 , 3 , 6 ,9 };
	for (int i=0;i<=3;i++)//将26个数字及英文字母写入文件
	{
		File <<chy[i]<<"\t"<<data[i]<<"\n";
	}
	File.close();//关闭文件
	return 0;
}