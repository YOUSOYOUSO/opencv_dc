#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include<vector>
#include <fstream>//fstream供给了三个类，用来实现c++对文件的操纵
#include <iomanip>

using namespace std;
using namespace cv;

int testBJC()
{
	Mat test1 = imread("test1.png");//读入图片
	Mat background;//背景
	Mat temp;   
	Mat result;

	VideoCapture capture("7.mp4");
	long totalFrameNumber= capture.get(CV_CAP_PROP_FRAME_COUNT);//获取视频的总帧数
	int FrameCount = 0;//帧数
	if (!capture.isOpened())//判断是否打开视频
	{
		cout << "读取视频有误" << endl;
		return -1;
	}
	else
	{
		capture.read(background);
		resize(background, background, Size(300, 200));//resize为300*200的图像，原来是720*480
		cvtColor(background, background, CV_RGB2GRAY);//转为灰度图
	}
	ofstream File;//ofstream类实现向文件写内容
	File.open("H:\\test\\test.xls", ios::_Noreplace);//ios::_Noreplace 打开一个文件时，如果文件不存在，创建该文件
	vector<int>ivec(totalFrameNumber);//可变数组ivec，大小为总帧数
	vector<int>::iterator iter = ivec.begin();//迭代器指针指向ivec首元素
	while (capture.read(temp))//循环读取下一帧
	{
		FrameCount++;
		resize(temp, temp, Size(300, 200));//resize为300*200的图像，原来是720*480
		cvtColor(temp, temp, CV_RGB2GRAY);//转为灰度图
		absdiff(background, temp, result);//和背景作差,输出result
		addWeighted(background, 0.95, temp, 1-0.95, 0, background);//将两幅图片叠加
		int PixelCount = 0;//像素数
		//遍历图像，二值化，阈值为50
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				if (result.at<uchar>(i, j)<50) {
					result.at<uchar>(i, j) = 0;
				}
				else {
					PixelCount++;
					result.at<uchar>(i, j) = 255;
				}
			}
		}
		*iter = PixelCount;//将像素数放到ivec中
		++iter;//指针后移
		cout << "整个视频共" << totalFrameNumber << "帧" << endl;
		cout <<"当前是第"<<FrameCount<<"帧"<<endl;
		cout << "当前背景有" << PixelCount << "个前景像素" << endl;
		imshow("当前视频",result);
		imshow("背景图片",background);
	}
	//for循环输出ivec里储存的像素数，并写入excel表格中
	for (vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter)
	{
		File << *iter << "\n";
	}
	File.close();//关闭文件
	return 0;
}
