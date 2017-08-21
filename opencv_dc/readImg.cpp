#include <iostream> 
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std; using namespace cv;

int readImg()
{
	//读入图像，并将之转为单通道图像 
	Mat im = imread("1.png", 0);
	if (im.empty())
	{
		cout << "Can not load image." << endl;
		return -1;
	}
	//显示图片
	namedWindow("1");		
	imshow("1", im);
	//等待两秒
	waitKey(2000);


	Mat result;
	//进行Canny操作，并将结果存于result 
	Canny(im, result, 50, 150);
	//显示图片
	namedWindow("2");
	imshow("2", result);
	// 等待两秒后窗口自动关闭    
	waitKey(2000);
	//写入图片
	imwrite("2.png", result);
	return 0;
}
