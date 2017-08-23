#include <iostream> 
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std; using namespace cv;

int readImg()
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
	waitKey(2000);

	Mat result;
	//进行Canny操作，并将结果存于result 
	Canny(im1, result, 50, 150);
	//显示图片
	namedWindow("3");
	imshow("3", result);
	// 等待两秒后窗口自动关闭    
	waitKey(5000);
	//写入图片
	imwrite("2.png", result);
	return 0;
}
