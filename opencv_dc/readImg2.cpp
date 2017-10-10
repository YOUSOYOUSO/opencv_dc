#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
const int gray_level = 16;
void getglcm_horison(Mat& input, Mat& dst)//0度灰度共生矩阵
{
	Mat src = input;
	CV_Assert(1 == src.channels());
	src.convertTo(src, CV_32S);
	int height = src.rows;
	int width = src.cols;
	int max_gray_level = 0;
	for (int j = 0; j < height; j++)//寻找像素灰度最大值
	{
		int* srcdata = src.ptr<int>(j);
		for (int i = 0; i < width; i++)
		{
			if (srcdata[i] > max_gray_level)
			{
				max_gray_level = srcdata[i];
			}
		}
	}
	max_gray_level++;//像素灰度最大值加1即为该矩阵所拥有的灰度级数
	if (max_gray_level > 16)//若灰度级数大于16，则将图像的灰度级缩小至16级，减小灰度共生矩阵的大小。
	{
		for (int i = 0; i < height; i++)
		{
			int*srcdata = src.ptr<int>(i);
			for (int j = 0; j < width; j++)
			{
				srcdata[j] = (int)srcdata[j] / gray_level;
			}
		}

		dst.create(gray_level, gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height; i++)
		{
			int*srcdata = src.ptr<int>(i);
			for (int j = 0; j < width - 1; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata[j + 1];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
	else//若灰度级数小于16，则生成相应的灰度共生矩阵
	{
		dst.create(max_gray_level, max_gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height; i++)
		{
			int*srcdata = src.ptr<int>(i);
			for (int j = 0; j < width - 1; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata[j + 1];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
}


void getglcm_vertical(Mat& input, Mat& dst)//90度灰度共生矩阵
{
	Mat src = input;
	CV_Assert(1 == src.channels());
	src.convertTo(src, CV_32S);
	int height = src.rows;
	int width = src.cols;
	int max_gray_level = 0;
	for (int j = 0; j < height; j++)
	{
		int* srcdata = src.ptr<int>(j);
		for (int i = 0; i < width; i++)
		{
			if (srcdata[i] > max_gray_level)
			{
				max_gray_level = srcdata[i];
			}
		}
	}
	max_gray_level++;
	if (max_gray_level > 16)
	{
		for (int i = 0; i < height; i++)//将图像的灰度级缩小至16级，减小灰度共生矩阵的大小。
		{
			int*srcdata = src.ptr<int>(i);
			for (int j = 0; j < width; j++)
			{
				srcdata[j] = (int)srcdata[j] / gray_level;
			}
		}

		dst.create(gray_level, gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height - 1; i++)
		{
			int*srcdata = src.ptr<int>(i);
			int*srcdata1 = src.ptr<int>(i + 1);
			for (int j = 0; j < width; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata1[j];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
	else
	{
		dst.create(max_gray_level, max_gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height - 1; i++)
		{
			int*srcdata = src.ptr<int>(i);
			int*srcdata1 = src.ptr<int>(i + 1);
			for (int j = 0; j < width; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata1[j];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
}


void getglcm_45(Mat& input, Mat& dst)//45度灰度共生矩阵
{
	Mat src = input;
	CV_Assert(1 == src.channels());
	src.convertTo(src, CV_32S);
	int height = src.rows;
	int width = src.cols;
	int max_gray_level = 0;
	for (int j = 0; j < height; j++)
	{
		int* srcdata = src.ptr<int>(j);
		for (int i = 0; i < width; i++)
		{
			if (srcdata[i] > max_gray_level)
			{
				max_gray_level = srcdata[i];
			}
		}
	}
	max_gray_level++;
	if (max_gray_level > 16)
	{
		for (int i = 0; i < height; i++)//将图像的灰度级缩小至16级，减小灰度共生矩阵的大小。
		{
			int*srcdata = src.ptr<int>(i);
			for (int j = 0; j < width; j++)
			{
				srcdata[j] = (int)srcdata[j] / gray_level;
			}
		}

		dst.create(gray_level, gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height - 1; i++)
		{
			int*srcdata = src.ptr<int>(i);
			int*srcdata1 = src.ptr<int>(i + 1);
			for (int j = 0; j < width - 1; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata1[j + 1];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
	else
	{
		dst.create(max_gray_level, max_gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height - 1; i++)
		{
			int*srcdata = src.ptr<int>(i);
			int*srcdata1 = src.ptr<int>(i + 1);
			for (int j = 0; j < width - 1; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata1[j + 1];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
}


void getglcm_135(Mat& input, Mat& dst)//135度灰度共生矩阵
{
	Mat src = input;
	CV_Assert(1 == src.channels());
	src.convertTo(src, CV_32S);
	int height = src.rows;
	int width = src.cols;
	int max_gray_level = 0;
	for (int j = 0; j < height; j++)
	{
		int* srcdata = src.ptr<int>(j);
		for (int i = 0; i < width; i++)
		{
			if (srcdata[i] > max_gray_level)
			{
				max_gray_level = srcdata[i];
			}
		}
	}
	max_gray_level++;
	if (max_gray_level > 16)
	{
		for (int i = 0; i < height; i++)//将图像的灰度级缩小至16级，减小灰度共生矩阵的大小。
		{
			int*srcdata = src.ptr<int>(i);
			for (int j = 0; j < width; j++)
			{
				srcdata[j] = (int)srcdata[j] / gray_level;
			}
		}

		dst.create(gray_level, gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height - 1; i++)
		{
			int*srcdata = src.ptr<int>(i);
			int*srcdata1 = src.ptr<int>(i + 1);
			for (int j = 1; j < width; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata1[j - 1];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
	else
	{
		dst.create(max_gray_level, max_gray_level, CV_32SC1);
		dst = Scalar::all(0);
		for (int i = 0; i < height - 1; i++)
		{
			int*srcdata = src.ptr<int>(i);
			int*srcdata1 = src.ptr<int>(i + 1);
			for (int j = 1; j < width; j++)
			{
				int rows = srcdata[j];
				int cols = srcdata1[j - 1];
				dst.ptr<int>(rows)[cols]++;
			}
		}
	}
}

void feature_computer(Mat&src, double& Asm, double& Eng, double& Con, double& Idm)//计算特征值
{
	int height = src.rows;
	int width = src.cols;
	int total = 0;
	for (int i = 0; i < height; i++)
	{
		int*srcdata = src.ptr<int>(i);
		for (int j = 0; j < width; j++)
		{
			total += srcdata[j];//求图像所有像素的灰度值的和
		}
	}

	Mat copy;
	copy.create(height, width, CV_64FC1);
	for (int i = 0; i < height; i++)
	{
		int*srcdata = src.ptr<int>(i);
		double*copydata = copy.ptr<double>(i);
		for (int j = 0; j < width; j++)
		{
			copydata[j] = (double)srcdata[j] / (double)total;//图像每一个像素的的值除以像素总和
		}
	}


	for (int i = 0; i < height; i++)
	{
		double*srcdata = copy.ptr<double>(i);
		for (int j = 0; j < width; j++)
		{
			Asm += srcdata[j] * srcdata[j];//能量
			if (srcdata[j] > 0)
				Eng -= srcdata[j] * log(srcdata[j]);//熵             
			Con += (double)(i - j)*(double)(i - j)*srcdata[j];//对比度
			Idm += srcdata[j] / (1 + (double)(i - j)*(double)(i - j));//逆差矩
		}
	}
}

int readImg1()
{
	//读入图像，并将之转为单通道图像 
	Mat im = imread("1.png");
	Mat im1;
	if (im.empty())
	{
		cout << "Can not load image." << endl;
		return -1;
	}
	//显示图片
	namedWindow("1");
	imshow("1", im);
	cvtColor(im, im1, CV_BGR2GRAY);
	namedWindow("2");
	imshow("2", im1);
	//设置阈值
	threshold(im1, im1, 255 * (0.5), 255, THRESH_BINARY);
	// 形态学操作
	// 如果把结构元素设置为Mat()，则将用默认的3*3的矩形结构元素
	Mat eroded;
	erode(im1, eroded, Mat());
	Mat dilated;
	dilate(im1, dilated, Mat());
	// 定义结构元素
	Mat closed, opened;
	Mat se(5, 5, CV_8U, Scalar(1));
	morphologyEx(im1, closed, MORPH_CLOSE, se);
	morphologyEx(im1, opened, MORPH_OPEN, se);
	namedWindow("xintaixue");
	imshow("xintaixue", im1);
	//等待两秒
	waitKey(5000);
	return 0;
}

int readImg2()
{
	readImg1();
	Mat dst_horison, dst_vertical, dst_45, dst_135;

	Mat src = imread("1.png");
	if (src.empty())
	{
		return -1;
	}
	Mat src_gray;
	//src.create(src.size(), CV_8UC1);
	//src_gray = Scalar::all(0);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	//src =( Mat_<int>(6, 6) << 0, 1, 2, 3, 0, 1, 1, 2, 3, 0, 1, 2, 2, 3, 0, 1, 2, 3, 3, 0, 1, 2, 3, 0, 0, 1, 2, 3, 0, 1, 1, 2, 3, 0, 1, 2 );
	//src = (Mat_<int>(4, 4) << 1, 17, 0, 3,3,2,20,5,26,50,1,2,81,9,25,1);
	getglcm_horison(src_gray, dst_horison);
	getglcm_vertical(src_gray, dst_vertical);
	getglcm_45(src_gray, dst_45);
	getglcm_135(src_gray, dst_135);

	double eng_horison = 0, con_horison = 0, idm_horison = 0, asm_horison = 0;
	feature_computer(dst_horison, asm_horison, eng_horison, con_horison, idm_horison);

	cout << "entropy:" << asm_horison << endl;
	cout << "energy:" << eng_horison << endl;
	cout << "contrast:" << con_horison << endl;
	cout << "idMoment:" << idm_horison << endl;
	system("pause");
	return 0;
}

